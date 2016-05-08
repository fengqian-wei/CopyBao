## �ο�

### GTK
- ������Bootstrap
  - [GTK+ Download: Windows](http://www.gtk.org/download/windows.php)
  - [gtk+-bundle_2.24.10-20120208_win32.zip](http://z.download.csdn.net/detail/al80402/4516798)
  - [vs2010+gtk�����](http://twyok.blog.163.com/blog/static/81229303201231491744674/)
  - [GTK+��hello world����](http://www.cnblogs.com/sunt/articles/2090472.html)
  - [Hello world in GTK+](http://www.levien.com/gimp/hello.html)
- [GTK+ 2.0 Tutorial](https://developer.gnome.org/gtk-tutorial/stable/)
  - [Timeouts](https://developer.gnome.org/gtk-tutorial/stable/c1759.html)
  - [Progress Bars](https://developer.gnome.org/gtk-tutorial/stable/x829.html)
- [GTK+ 2 Reference Manual](https://developer.gnome.org/gtk2/2.24/)
  - [gtk_window_set_modal ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-modal)
- [Text Widget Overview](https://developer.gnome.org/gtk2/2.24/TextWidget.html)
- [GtkTextView](https://developer.gnome.org/gtk2/2.24/GtkTextView.html)
  - [gtk_text_view_set_wrap_mode ()](https://developer.gnome.org/gtk2/2.24/GtkTextView.html#gtk-text-view-set-wrap-mode)
  - gtk_widget_set_sensitive () for _enable/disable_
  - [gtk_text_view_get_buffer ()](https://developer.gnome.org/gtk2/2.24/GtkTextView.html#gtk-text-view-get-buffer)
  - GtkTextBuffer
    - [gtk_text_buffer_get_text ()](https://developer.gnome.org/gtk2/2.24/GtkTextBuffer.html#gtk-text-buffer-get-text)
    - [gtk_text_buffer_get_start_iter ()](https://developer.gnome.org/gtk2/2.24/GtkTextBuffer.html#gtk-text-buffer-get-start-iter)
      - __Hints:__ g_free()
    - [g_object_ref ()](https://developer.gnome.org/gobject/unstable/gobject-The-Base-Object-Type.html#g-object-ref)
  - [gtk_text_view_set_editable ()](man.chinaunix.net/develop/GTK+/2.6/gtk/GtkTextView.html#gtk-text-view-set-editable)
- [GtkScrolledWindow](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html)
  - [gtk_scrolled_window_set_policy ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-policy)
  - [gtk_scrolled_window_set_shadow_type ()](https://developer.gnome.org/gtk2/2.24/GtkScrolledWindow.html#gtk-scrolled-window-set-shadow-type)
- [How to set a fixed windows size for a GTK+ app in C?](http://stackoverflow.com/questions/4772804/how-to-set-a-fixed-windows-size-for-a-gtk-app-in-c)
- [GLib: Key-value file parser](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html)
  - [g_key_file_new ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-new)
  - [g_key_file_load_from_file ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-load-from-file)
  - [g_key_file_get_integer_list ()](https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html#g-key-file-get-integer-list)
- [GtkFileChooserDialog](https://developer.gnome.org/gtk2/2.24/GtkFileChooserDialog.html)
- [GtkMessageDialog](http://man.chinaunix.net/develop/GTK+/2.6/gtk/GtkMessageDialog.html)
- [gtk_widget_hide_on_delete ()](http://man.chinaunix.net/develop/GTK+/2.6/gtk/GtkWidget.html#gtk-widget-hide-on-delete)
- [g_locale_from_utf8 ()](https://developer.gnome.org/glib/unstable/glib-Character-Set-Conversion.html#g-locale-from-utf8)
- [spice_main_file_copy_async()](http://www.spice-space.org/api/spice-gtk/SpiceMainChannel.html#spice-main-file-copy-async)
  - [The ��new-file-transfer�� signal](http://www.spice-space.org/api/spice-gtk/SpiceMainChannel.html#SpiceMainChannel-new-file-transfer)
  - [GCancellable](https://developer.gnome.org/gio/unstable/GCancellable.html)
  - [GFile](https://developer.gnome.org/gio/stable/GFile.html#GFileCopyFlags)
  - [GAsyncResult](https://developer.gnome.org/gio/stable/GAsyncResult.html#GAsyncReadyCallback)
- [glib-genmarshal](https://developer.gnome.org/gobject/stable/glib-genmarshal.html)
  - ����ʵ��<code>spice-marshal.txt</code>��<code>spice-marshal{.h, .c}</code>��ת��
- [gtk_window_set_deletable ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-deletable)���������ùرհ�ť
- [gtk_window_set_type_hint ()](https://developer.gnome.org/gtk2/2.24/GtkWindow.html#gtk-window-set-type-hint)����Ϊ[GDK_WINDOW_TYPE_HINT_DIALOG](https://developer.gnome.org/gdk2/2.24/gdk2-Windows.html#GdkWindowTypeHint)���������������С����ť
- [g_message ()](https://developer.gnome.org/glib/unstable/glib-Message-Logging.html#g-message) ʹ��g_message�Ⱥ�����¼��־
- [g_path_get_basename ()](https://developer.gnome.org/glib/stable/glib-Miscellaneous-Utility-Functions.html#g-path-get-basename) ���·���е��ļ������֡�
- [The Alignment widget](https://developer.gnome.org/gtk-tutorial/stable/x1243.html) ������Alignmentʵ�ְ�ť��ԭ��С��ʾ+���С�

### Win32 API

- [How can we check if a file Exists or not using Win32 program?](http://stackoverflow.com/questions/3828835/how-can-we-check-if-a-file-exists-or-not-using-win32-program)
- [Win32 - Select Directory Dialog from C/C++](http://stackoverflow.com/questions/12034943/win32-select-directory-dialog-from-c-c)
- [CoTaskMemFree Function]() - ʹ���������IMalloc->Free()�ͷ�pidl
- [DialogBoxIndirectParam](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645461(v=vs.85).aspx) - �Ӷ����ƶԻ���ģ�塱�����Ի���
- [DialogProc callback function](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645469(v=vs.85).aspx)
- [Changing the Current Directory](https://msdn.microsoft.com/en-us/library/windows/desktop/aa363806(v=vs.85).aspx) - �ı䡰��ǰ��Ŀ¼
- [Creation of a Console (Windows)](https://msdn.microsoft.com/en-us/library/windows/desktop/ms682528(v=vs.85).aspx) A process can also create a console by specifying the **CREATE_NEW_CONSOLE** flag in a call to CreateProcess. �����������CreateProcess��������spicy.exe��ʾ�������д��ڡ�
  - �ο�[��ҳ��](http://stackoverflow.com/questions/780465/winapi-createprocess-but-hide-the-process-window)ѧϰCreateProcess���÷�

### Win32 Resource File
- [How can I read a compiled resource (.res) file in C#?](http://stackoverflow.com/questions/7982181/how-can-i-read-a-compiled-resource-res-file-in-c)

### base64
- [coreutils/base64.c](http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/base64.c)
- [gnulib/base64.c](http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob;f=lib/base64.c;h=1a8bfce7a534f83f19a093432bafe883f16de9b1;hb=HEAD)
- [g_base64_encode ()](https://developer.gnome.org/glib/unstable/glib-Base64-Encoding.html#g-base64-encode) GLib������ṩbase64���ܽ���֧�֡�
- [Base64���߱������](http://tools.jb51.net/tools/base64_decode-gb2312.php)

### C# ###
- [Control.InValidate vs. Control.Refresh()?](https://bytes.com/topic/c-sharp/answers/244445-control-invalidate-vs-control-refresh)
- [String.Format for Hex](http://stackoverflow.com/questions/11618387/string-format-for-hex)
- [Reference Source](http://referencesource.microsoft.com/)
- [How do I encode and decode a base64 string?](http://stackoverflow.com/questions/11743160/how-do-i-encode-and-decode-a-base64-string)
- [C#: Get complete desktop size?](http://stackoverflow.com/questions/1317235/c-get-complete-desktop-size)
- [C# - Reading from and Writing into Binary files](http://www.tutorialspoint.com/csharp/csharp_binary_files.htm)
- [/target (C# Compiler Options)](https://msdn.microsoft.com/zh-cn/library/6h25dztx.aspx)

### SPICE
- [spice �ͻ�������](http://www.spice-space.org/download.html)
- [SPICE/spice-gtk](https://github.com/SPICE/spice-gtk)
- [Spice-GTK Reference Manual](http://www.spice-space.org/api/spice-gtk/index.html)
- [����windows�µ�spice-gtk](http://blog.csdn.net/lichao201005/article/details/9618907)
- [Spice ����(4) �C spice �ͻ���ʵ��](http://mathslinux.org/?p=296)
- [spice_inputs_key_press](http://www.spice-space.org/api/spice-gtk/SpiceInputsChannel.html#spice-inputs-key-press)
- [spice_inputs_set_key_locks](http://www.spice-space.org/api/spice-gtk/SpiceInputsChannel.html#spice-inputs-set-key-locks)
- [DisplayChannel: The ��display-primary-create�� signal](http://www.spice-space.org/api/spice-gtk/SpiceDisplayChannel.html#SpiceDisplayChannel-display-primary-create) 
  - ������ź�ʱ�����Ա�����Ļ�������ĵ�ַ
  - �����<code>d_format</code>��32_xRGB������ɫ��32λ������ʾ��ֻ��24λ��Ч��little-endian��B�ǵ�һ���ֽڡ�
  - ����<code>d_stride</code>ָ��Ļ��pitch��һ�����<code>d_width*4</code>��
- [DisplayChannel: The ��display-invalidate�� signal](http://www.spice-space.org/api/spice-gtk/SpiceDisplayChannel.html#SpiceDisplayChannel-display-invalidate) ����һ���������ϵĸ��£��ͻᴥ�����ź�
- [spicy-screenshot.c](https://github.com/SPICE/spice-gtk/blob/master/src/spicy-screenshot.c)

### misc
- [�ж�ĳ������64λ����32λ](http://www.cnblogs.com/teamleader/archive/2012/01/10/2318310.html)
- [Linux�¿���Windowsƽ̨���еĳ���](http://www.linuxidc.com/Linux/2013-06/85217.htm)
- [Keyboard scancodes](http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html)
- [fstat](http://linux.die.net/man/2/fstat) - ����ļ�����
- [tmpfile](https://msdn.microsoft.com/zh-cn/library/x8x7sakw.aspx) - ����һ����ʱ�ļ���������FILEָ��
