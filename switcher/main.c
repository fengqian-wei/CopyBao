#ifdef UNICODE
#undef UNICODE
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shlwapi.h>
#include <direct.h> // for chdir()
#pragma comment(lib, "shlwapi.lib")

int is_space(char c)
{
	return c == ' ' || c == '\t';
}

char item[256];
int item_len;
int get_item(const char **pp)
{
	const char *p = *pp;
	char *q;
	int quote = 0;

	while(is_space(*p)) p++;
	if(*p == '\0') return 0;
	if(*p == '"') { quote = 1; p++; }
	
	q = item;
	for(;;) {
		*q++ = *p++;
		if(quote) { if(*p == '"') { p++; break; } }
		else { if(is_space(*p) || *p == '\0') { break; } }
	}
	*q = '\0';
	item_len = q - item;
	*pp = p;	
	return 1;
}

char arg_buf[1024], *wp = arg_buf;
void append_arg()
{
	*wp++ = ' ';
	memcpy(wp, item, item_len);
	wp += item_len;
}
void append_str(const char *str)
{
	strcpy(wp, str);
	wp += strlen(str);
}
char *finish_args()
{
	*wp = '\0';
	return arg_buf;
}

int main(void)
{
	char *cmdline = GetCommandLine();
	char *new_cmdline;

	{
		char full_path[256];
		GetModuleFileName(NULL, full_path, sizeof(full_path));
		PathRemoveFileSpec(full_path);
		append_str(full_path);
		append_str("\\");
	}

	if(MessageBox(0, "Enable COPY?", "Switcher", MB_YESNO | MB_ICONQUESTION) == IDYES) {
		int kv = 0;
		const char *my_client = "..\\spicy\\spicy.exe";
		const char *required_args[] = { "-h", "-p", "-s", "-w", NULL };

		{
			char path[256];
			GetModuleFileName(NULL, path, sizeof(path));
			PathRemoveFileSpec(path);
			strcat(path, "\\..\\spicy");
			SetCurrentDirectory(path);
		}

		get_item(&cmdline); // skip program path
		append_str(my_client);

		while(get_item(&cmdline)) {
			int required = 0;
			const char **p = required_args;
			for(; *p; p++) if(strcmp(item, *p) == 0) { required = 1; break; }

			if(required) { append_arg(); get_item(&cmdline); append_arg(); }
			else { get_item(&cmdline); }
		}
	} else {
		const char *orig_client = "_spicec.exe";
		get_item(&cmdline); // skip program path
		append_str(orig_client);
		append_str(cmdline);
	}

	new_cmdline = finish_args();

	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		DWORD flags = 0;

		memset(&si, 0, sizeof(si));
		si.cb = sizeof(STARTUPINFO);

/* want to show the console of spicy for debug? */
#if 0
		flags = CREATE_NEW_CONSOLE;
#endif
		CreateProcessA(NULL, new_cmdline, NULL, NULL, FALSE, flags, NULL, NULL, &si, &pi);
	}
	return 0;
}
