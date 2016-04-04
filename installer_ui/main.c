#ifdef UNICODE
#undef UNICODE
#endif

#include <stdlib.h>
#include <Windows.h>
#include <Shlobj.h>
#include "resource.h"

int _validate_directory(const char *dir, const char *file)
{
	char buf[MAX_PATH + 30];
	DWORD attr;
	
	wsprintf(buf, "%s\\%s", dir, file);
	attr = GetFileAttributes(buf);
	
	return attr != INVALID_FILE_ATTRIBUTES;
}

int validate_directory(const char *path)
{
	return _validate_directory(path, "VSoftClient.exe");
}

int check_installed(const char *path)
{
	return _validate_directory(path, "spice\\_spicec.exe");
}

typedef enum _Action
{
	doNothing,
	doInstall,
	doReinstall,
	doUninstall
} Action;

static char path[MAX_PATH];
static char cmdline[1000];

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static BROWSEINFO brow;
	static LPITEMIDLIST pidl;

	switch(message) {
	case WM_INITDIALOG:
		// don't set input focus for me
		return FALSE;

	case WM_CLOSE:
		EndDialog(hwnd, doNothing);

		// message processed
		return TRUE;

	case WM_COMMAND:
		if(HIWORD(wparam) == BN_CLICKED) {
			switch(LOWORD(wparam)) {
			case IDC_BROWSE:
			{
				brow.hwndOwner = hwnd;
				brow.pidlRoot = NULL;
				brow.pszDisplayName = NULL;
				brow.lpszTitle = "";
				brow.ulFlags = BIF_RETURNONLYFSDIRS;
				brow.lpfn = NULL;
				brow.lParam = 0;
				brow.iImage = 0;

				pidl = SHBrowseForFolder(&brow);
				if(pidl) {
					SHGetPathFromIDList(pidl, path);
					CoTaskMemFree(pidl);
					SetDlgItemText(hwnd, IDC_PATH, path);
				}
				break;
			}

			case IDC_INSTALL:
			case IDC_UNINSTALL:
			{
				int is_install = (LOWORD(wparam) == IDC_INSTALL);

				GetDlgItemText(hwnd, IDC_PATH, path, sizeof(path));
				if(!validate_directory(path)) {
					MessageBox(hwnd, "No XueBao found in this directory.", "Error", MB_ICONSTOP);
					break;
				}
				if(check_installed(path)) {
					if(is_install) {
						if(MessageBox(hwnd, "Already installed, re-install?",
					              "Confirm", MB_YESNO | MB_ICONQUESTION) == IDYES)
						{
							EndDialog(hwnd, doReinstall);
						}
						break;
					}
				} else {
					if(LOWORD(wparam) == IDC_UNINSTALL) {
						MessageBox(hwnd, "Not installed yet.", "Error", MB_ICONSTOP);
						break;
					}
				}
				EndDialog(hwnd, is_install ? doInstall : doUninstall);
			}

			}
		}

		return TRUE;

	default:
		return FALSE;
	}
}

void fill_cmdline(const char *exe)
{
	wsprintf(cmdline, "%s%s \"%s\"", "cmd.exe /c", exe, path);
}

int __stdcall WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpcmdline, int ncmdshow)
{
	Action action;

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	
	action = (Action) DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	switch(action) {
	case doInstall: fill_cmdline("do.bat"); break;
	case doUninstall: fill_cmdline("undo.bat"); break;
	case doReinstall: fill_cmdline("redo.bat"); break;
	}
	
	if(action != doNothing) {
		system(cmdline);
	}

	CoUninitialize();
	return 0;
}
