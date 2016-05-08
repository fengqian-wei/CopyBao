#include <stdio.h>
#include <Windows.h>

int main(void)
{
	LPSTR cmdline = GetCommandLine();
	FILE *fp = fopen("D:\\args.txt", "w");
	fputs(cmdline, fp);
	fclose(fp);
	MessageBox(0, cmdline, "cmdline", 0);
	return EXIT_SUCCESS;
}
