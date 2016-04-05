#ifdef UNICODE
#undef UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Commctrl.h>
#include "resource.h"

typedef unsigned char u8;
u8 dec[256];

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static int data_len;
	static int data_len2;
	static int last_length;
	int new_length;
	static int idle_ticks;

	switch(message) {
	case WM_INITDIALOG:
		return FALSE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;

	case WM_COMMAND:
		if(HIWORD(wparam) == BN_CLICKED) {
			switch(LOWORD(wparam)) {
			case IDC_RECV:
				EnableWindow(GetDlgItem(hwnd, IDC_DATA), TRUE);
				SetFocus(GetDlgItem(hwnd, IDC_DATA));
				EnableWindow(GetDlgItem(hwnd, IDC_RECV), FALSE);
				ShowWindow(GetDlgItem(hwnd, IDC_RESET), SW_SHOW);
				SetTimer(hwnd, 1, 500, NULL);
				break;

			case IDC_RESET:
				SetDlgItemText(hwnd, IDC_DATA, "");
				EnableWindow(GetDlgItem(hwnd, IDC_DATA), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_RECV), TRUE);
				ShowWindow(GetDlgItem(hwnd, IDC_RESET), SW_HIDE);
				EnableWindow(GetDlgItem(hwnd, IDC_SAVE), FALSE);
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 2);
				break;

			case IDC_SAVE:
			{
				OPENFILENAME ofn;
				char path[MAX_PATH] = "";
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = path;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_OVERWRITEPROMPT;
				ofn.lpstrFilter = "All Files(*.*)\0*.*\0";
				ofn.nFilterIndex = 1;

				if(GetSaveFileName(&ofn)) {
					int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA)) + 1;
					FILE *fp = fopen(path, "w");
					u8 *buf = (u8 *)malloc(len);
					u8 *p = buf + 8;
					int i;
					GetDlgItemText(hwnd, IDC_DATA, (char *)buf, len);
					for(i = data_len; i > 0;) {
						fputc((dec[p[0]] << 2) | (dec[p[1]] >> 4), fp); i--;
						if(i) { fputc(((dec[p[1]] & 15) << 4) | (dec[p[2]] >> 2), fp); i--; }
						if(i) { fputc(((dec[p[2]] & 3) << 6) | dec[p[3]], fp); i--; }
						if(i) {
							p += 4;
							if(*p == '\r') p += 2;
						}
					}
					free(buf);
					fclose(fp);
				}
				break;
			}
				
			}
		}

		return TRUE;

	case WM_TIMER:
		switch(wparam) {
		case 1:
			if(GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA)) > 6) {
				char buf[10];
				int len;

				GetWindowText(GetDlgItem(hwnd, IDC_DATA), buf, 10);
				sscanf(buf, "%x", &len);
				data_len = len;
				data_len2 = (len + 2) / 3 * 4;
				KillTimer(hwnd, 1);
				
				last_length = 0;
				idle_ticks = 0;
				SetTimer(hwnd, 2, 100, NULL);
				EnableWindow(GetDlgItem(hwnd, IDC_RESET), FALSE);
			}
			return TRUE;
		case 2:
			new_length = GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA));
			if(new_length == last_length) {
				if(++idle_ticks > 5) {
					EnableWindow(GetDlgItem(hwnd, IDC_RESET), TRUE);
					return FALSE;
				}
			} else {
				int len, len2;
				char buf[10];
				EnableWindow(GetDlgItem(hwnd, IDC_RESET), FALSE);

				last_length = new_length;
				len = (new_length - 8) - (new_length - 8) / 82 * 2;
				len2 = len > data_len2 ? data_len2 : len;

				SendDlgItemMessage(hwnd, IDC_PBAR, PBM_SETPOS, len2 * 100 / data_len2, 0);
				sprintf(buf, "%.1f%%", len2 * 100.0f / data_len2);
				SetDlgItemText(hwnd, IDC_PERCENT, buf);

				if(new_length - 8 == data_len2 + (data_len2 + 79) / 80 * 2) {
					KillTimer(hwnd, 2);
					EnableWindow(GetDlgItem(hwnd, IDC_DATA), FALSE);
					EnableWindow(GetDlgItem(hwnd, IDC_RESET), TRUE);
					EnableWindow(GetDlgItem(hwnd, IDC_SAVE), TRUE);
				}
			}
		}
	default:
		return FALSE;
	}
}

int __stdcall WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpcmdline, int ncmdshow)
{
	char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", *p;
	ZeroMemory(dec, sizeof(dec));
	for(p = s; *p; p++) {
		dec[*p] = p - s;
	}
	DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	return 0;
}
