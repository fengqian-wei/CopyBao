#include <stdio.h>
#include <string.h>
#include <assert.h>

struct Desc
{
	int code;
	int shift;
	Desc() : code(0), shift(0) { }
};

Desc table[256];

int main(void)
{
	FILE *fp = fopen("src.txt", "r");
	if (!fp) {
		puts("failed to open");
		return 0;
	}

	char buf[256];
	while (fgets(buf, 256, fp) != NULL) {
		int len = strlen(buf);
		if (buf[len - 1] == '\n') buf[len - 1] = 0;
		if (buf[0] == '#') continue;
		
		int code;
		unsigned char c1, c2;
		assert(sscanf(buf, "%02x %c%c", &code, &c1, &c2) == 3);
		table[c1].code = code;
		table[c1].shift = 0;
		table[c2].code = code;
		table[c2].shift = 1;
	}
	fclose(fp);

	table['\n'].code = 0x1C;
	table['\n'].shift = 0;
	table['\t'].code = 0x0F;
	table['\t'].shift = 0;
	table[' '].code = 0x39;
	table[' '].shift = 0;

#define STRUCT_NAME "Finger"
	fp = fopen("finger.h", "w");
	fprintf(fp,
		"typedef struct {\n"
		"    guint code;\n"
		"    int shift;\n"
		"} " STRUCT_NAME ";\n"
		"\n"
		STRUCT_NAME " char_map[256] =\n"
		"{");
	for (int i = 0; i < 256; i++) {
		if (i % 4 == 0) fprintf(fp, "\n    ");
		fprintf(fp, "{ 0x%02X, %d }%s", table[i].code, table[i].shift,
			(i < 255) ? ", " : "");
	}
	fprintf(fp, "\n};\n");
	fclose(fp);

	puts("ok");
	return 0;
}
