#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <Windows.h>

int read_file(char *path, char **mem_ptr, int *len_ptr)
{
	int fd = _open(path, O_RDONLY | O_BINARY);
	if (fd == -1) {
		fprintf(stderr, "Warning: can't open file: %s", path);
		return 0;
	}

	struct stat st;
	if (fstat(fd, &st) == -1) {
		fprintf(stderr, "Warning: can't call fstat() on %s", path);
		return 0;
	}

	int len = st.st_size;
	char *mem = (char *) malloc(len);
	_read(fd, mem, len);

	_close(fd);

	*mem_ptr = mem;
	*len_ptr = len;

	return 1;
}

char *next_header(char *p)
{
	DWORD *pdw = reinterpret_cast<DWORD *>(p);
	DWORD data_size = pdw[0];
	DWORD header_size = pdw[1];

	return p + ((data_size + header_size + 3) & ~3);
}

int read_header(char *p, DWORD *type_ptr, DWORD *id_ptr)
{
	DWORD *pdw = reinterpret_cast<DWORD *>(p);
	
	DWORD header_size = pdw[1];
	if (header_size > 0x20) {
		fprintf(stderr, "Warning: unsupported header");
		return 0;
	}

	DWORD type, id;
	type = HIWORD(pdw[2]);
	id = HIWORD(pdw[3]);

	*type_ptr = type;
	*id_ptr = id;

	return 1;
}

DWORD get_data_size(char *p)
{
	DWORD *pdw = reinterpret_cast<DWORD *>(p);
	return pdw[0];
}

DWORD get_header_size(char *p)
{
	DWORD *pdw = reinterpret_cast<DWORD *>(p);
	return pdw[1];
}

char *seek_dialog(char *q, int len, DWORD dialog_id)
{
	char *r = NULL;
	for(char *p = q; p - q < len; p = next_header(p)) {
		DWORD type, id;
		if (!read_header(p, &type, &id))
			break;

		if (MAKEINTRESOURCE(type) == RT_DIALOG && id == dialog_id) {
			r = p;
			break;
		}
	}

	return r;
}

int write_dialog_data(FILE *fp, char *res_file_path, DWORD dialog_id)
{
	char *q;
	int len;
	if (!read_file(res_file_path, &q, &len))
		return 0;

	char *p_dialog = seek_dialog(q, len, dialog_id);
	if (!p_dialog)
		goto exit;

	DWORD data_len = get_data_size(p_dialog);
	char *data_mem = p_dialog + get_header_size(p_dialog);

	fprintf(fp, "%s\n", "static unsigned char dlg[] =");
	fprintf(fp, "{\n");
	for (unsigned i = 0; i < data_len; i++) {
		if (i && i % 12 == 0)
			fprintf(fp, "%s", "\n");
		
		fprintf(fp, "0x%02X%s ", (unsigned char)data_mem[i], i < data_len - 1 ? "," : "");
	}
	fprintf(fp, "\n};\n");

exit:
	free(q);

	return 1;
}

int main(void)
{
	write_dialog_data(stdout, "F:\\SpicyInstaller\\Paste-spicy\\receiver\\Debug\\main.res", 101);
	return 0;
}