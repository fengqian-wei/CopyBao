#include "spice-file-transfer-task.h"
#include <glib.h>
#include <gio/gio.h> // GFile, GFileInputStream, GFileCopyFlags, GCancellable, GFileProgressCallback, GAsyncReadyCallback
#include <spice-client.h> // SpiceMainChannel

// [CLIP-FROM spice-protocol] /spice/vd_agent.h
#define VD_AGENT_MAX_DATA_SIZE 2048

// [CLIP FROM spice-gtk] /src/channel-main.c

/**
 * SECTION:file-transfer-task
 * @short_description: Monitoring file transfers
 * @title: File Transfer Task
 * @section_id:
 * @see_also: #SpiceMainChannel
 * @stability: Stable
 * @include: spice-client.h
 *
 * SpiceFileTransferTask is an object that represents a particular file
 * transfer between the client and the guest. The properties and signals of the
 * object can be used to monitor the status and result of the transfer. The
 * Main Channel's #SpiceMainChannel::new-file-transfer signal will be emitted
 * whenever a new file transfer task is initiated.
 *
 * Since: 0.31
 */
G_DEFINE_TYPE(SpiceFileTransferTask, spice_file_transfer_task, G_TYPE_OBJECT)

#define FILE_TRANSFER_TASK_PRIVATE(o) \
        (G_TYPE_INSTANCE_GET_PRIVATE((o), SPICE_TYPE_FILE_TRANSFER_TASK, SpiceFileTransferTaskPrivate))

#define FILE_XFER_CHUNK_SIZE (VD_AGENT_MAX_DATA_SIZE * 32)
struct _SpiceFileTransferTaskPrivate

/* private */
{
    uint32_t                       id;
    gboolean                       pending;
    GFile                          *file;
    SpiceMainChannel               *channel;
    GFileInputStream               *file_stream;
    GFileCopyFlags                 flags;
    GCancellable                   *cancellable;
    GFileProgressCallback          progress_callback;
    gpointer                       progress_callback_data;
    GAsyncReadyCallback            callback;
    gpointer                       user_data;
    char                           *buffer;
    uint64_t                       read_bytes;
    uint64_t                       file_size;
    gint64                         start_time;
    gint64                         last_update;
    GError                         *error;
};

enum {
    PROP_TASK_ID = 1,
    PROP_TASK_CHANNEL,
    PROP_TASK_CANCELLABLE,
    PROP_TASK_FILE,
    PROP_TASK_PROGRESS,
};

enum {
    SIGNAL_FINISHED,
    LAST_TASK_SIGNAL
};

static guint task_signals[LAST_TASK_SIGNAL];

static void
spice_file_transfer_task_get_property(GObject *object,
                                      guint property_id,
                                      GValue *value,
                                      GParamSpec *pspec)
{
    SpiceFileTransferTask *self = SPICE_FILE_TRANSFER_TASK(object);

    switch (property_id)
    {
        case PROP_TASK_ID:
            g_value_set_uint(value, self->priv->id);
            break;
        case PROP_TASK_FILE:
            g_value_set_object(value, self->priv->file);
            break;
        case PROP_TASK_PROGRESS:
            g_value_set_double(value, spice_file_transfer_task_get_progress(self));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}

static void
spice_file_transfer_task_set_property(GObject *object,
                                      guint property_id,
                                      const GValue *value,
                                      GParamSpec *pspec)
{
    SpiceFileTransferTask *self = SPICE_FILE_TRANSFER_TASK(object);

    switch (property_id)
    {
        case PROP_TASK_ID:
            self->priv->id = g_value_get_uint(value);
            break;
        case PROP_TASK_FILE:
            self->priv->file = g_value_dup_object(value);
            break;
        case PROP_TASK_CHANNEL:
            self->priv->channel = g_value_dup_object(value);
            break;
        case PROP_TASK_CANCELLABLE:
            self->priv->cancellable = g_value_dup_object(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}

static void
spice_file_transfer_task_dispose(GObject *object)
{
    SpiceFileTransferTask *self = SPICE_FILE_TRANSFER_TASK(object);

    g_clear_object(&self->priv->file);

    G_OBJECT_CLASS(spice_file_transfer_task_parent_class)->dispose(object);
}

static void
spice_file_transfer_task_finalize(GObject *object)
{
    SpiceFileTransferTask *self = SPICE_FILE_TRANSFER_TASK(object);

    g_free(self->priv->buffer);

    G_OBJECT_CLASS(spice_file_transfer_task_parent_class)->finalize(object);
}

static void
spice_file_transfer_task_constructed(GObject *object)
{
    SpiceFileTransferTask *self = SPICE_FILE_TRANSFER_TASK(object);

    if (spice_util_get_debug()) {
        gchar *basename = g_file_get_basename(self->priv->file);
        self->priv->start_time = g_get_monotonic_time();
        self->priv->last_update = self->priv->start_time;

        SPICE_DEBUG("transfer of file %s has started", basename);
        g_free(basename);
    }
}

static void
spice_file_transfer_task_class_init(SpiceFileTransferTaskClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    g_type_class_add_private(klass, sizeof(SpiceFileTransferTaskPrivate));

    object_class->get_property = spice_file_transfer_task_get_property;
    object_class->set_property = spice_file_transfer_task_set_property;
    object_class->finalize = spice_file_transfer_task_finalize;
    object_class->dispose = spice_file_transfer_task_dispose;
    object_class->constructed = spice_file_transfer_task_constructed;

    /**
     * SpiceFileTransferTask:id:
     *
     * The ID of the file transfer task
     *
     * Since: 0.31
     **/
    g_object_class_install_property(object_class, PROP_TASK_ID,
                                    g_param_spec_uint("id",
                                                      "id",
                                                      "The id of the task",
                                                      0, G_MAXUINT, 0,
                                                      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE |
                                                      G_PARAM_STATIC_STRINGS));

    /**
     * SpiceFileTransferTask:channel:
     *
     * The main channel that owns the file transfer task
     *
     * Since: 0.31
     **/
    g_object_class_install_property(object_class, PROP_TASK_CHANNEL,
                                    g_param_spec_object("channel",
                                                        "channel",
                                                        "The channel transferring the file",
                                                        SPICE_TYPE_MAIN_CHANNEL,
                                                        G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE |
                                                        G_PARAM_STATIC_STRINGS));

    /**
     * SpiceFileTransferTask:cancellable:
     *
     * A cancellable object used to cancel the file transfer
     *
     * Since: 0.31
     **/
    g_object_class_install_property(object_class, PROP_TASK_CANCELLABLE,
                                    g_param_spec_object("cancellable",
                                                        "cancellable",
                                                        "The object used to cancel the task",
                                                        G_TYPE_CANCELLABLE,
                                                        G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE |
                                                        G_PARAM_STATIC_STRINGS));

    /**
     * SpiceFileTransferTask:file:
     *
     * The file that is being transferred in this file transfer task
     *
     * Since: 0.31
     **/
    g_object_class_install_property(object_class, PROP_TASK_FILE,
                                    g_param_spec_object("file",
                                                        "File",
                                                        "The file being transferred",
                                                        G_TYPE_FILE,
                                                        G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE |
                                                        G_PARAM_STATIC_STRINGS));

    /**
     * SpiceFileTransferTask:progress:
     *
     * The current state of the file transfer. This value indicates a
     * percentage, and ranges from 0 to 100. Listen for change notifications on
     * this property to be updated whenever the file transfer progress changes.
     *
     * Since: 0.31
     **/
    g_object_class_install_property(object_class, PROP_TASK_PROGRESS,
                                    g_param_spec_double("progress",
                                                        "Progress",
                                                        "The percentage of the file transferred",
                                                        0.0, 100.0, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_STATIC_STRINGS));

    /**
     * SpiceFileTransferTask::finished:
     * @task: the file transfer task that emitted the signal
     * @error: (transfer none): the error state of the transfer. Will be %NULL
     * if the file transfer was successful.
     *
     * The #SpiceFileTransferTask::finished signal is emitted when the file
     * transfer has completed transferring to the guest.
     *
     * Since: 0.31
     **/
    task_signals[SIGNAL_FINISHED] = g_signal_new("finished", SPICE_TYPE_FILE_TRANSFER_TASK,
                                            G_SIGNAL_RUN_FIRST,
                                            0, NULL, NULL,
                                            g_cclosure_marshal_VOID__BOXED,
                                            G_TYPE_NONE, 1,
                                            G_TYPE_ERROR);
}

static void
spice_file_transfer_task_init(SpiceFileTransferTask *self)
{
    self->priv = FILE_TRANSFER_TASK_PRIVATE(self);
    self->priv->buffer = g_malloc0(FILE_XFER_CHUNK_SIZE);
}

static SpiceFileTransferTask *
spice_file_transfer_task_new(SpiceMainChannel *channel, GFile *file, GCancellable *cancellable)
{
    static uint32_t xfer_id = 0;    /* Used to identify task id */

    return g_object_new(SPICE_TYPE_FILE_TRANSFER_TASK,
                        "id", xfer_id++,
                        "file", file,
                        "channel", channel,
                        "cancellable", cancellable,
                        NULL);
}

/**
 * spice_file_transfer_task_get_progress:
 * @self: a file transfer task
 *
 * Convenience function for retrieving the current progress of this file
 * transfer task.
 *
 * Returns: A percentage value between 0 and 100
 *
 * Since: 0.31
 **/
double spice_file_transfer_task_get_progress(SpiceFileTransferTask *self)
{
    if (self->priv->file_size == 0)
        return 0.0;

    return (double)self->priv->read_bytes / self->priv->file_size;
}

/**
 * spice_file_transfer_task_cancel:
 * @self: a file transfer task
 *
 * Cancels the file transfer task. Note that depending on how the file transfer
 * was initiated, multiple file transfer tasks may share a single
 * #SpiceFileTransferTask::cancellable object, so canceling one task may result
 * in the cancellation of other tasks.
 *
 * Since: 0.31
 **/
void spice_file_transfer_task_cancel(SpiceFileTransferTask *self)
{
    g_cancellable_cancel(self->priv->cancellable);
}


/**
 * spice_file_transfer_task_get_filename:
 * @self: a file transfer task
 *
 * Gets the name of the file being transferred in this task
 *
 * Returns: (transfer none): The basename of the file
 *
 * Since: 0.31
 **/
char* spice_file_transfer_task_get_filename(SpiceFileTransferTask *self)
{
    return g_file_get_basename(self->priv->file);
}
