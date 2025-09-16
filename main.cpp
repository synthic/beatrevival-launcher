#include <wx/wx.h>

#include "ui/ui.h"
#include "ui/res/black.png.h"
#include "ui/res/red.png.h"

class App : public wxApp { public: virtual bool OnInit(); };

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	wxImage::AddHandler(new wxPNGHandler);

	MainWindow* w = new MainWindow(NULL);
	w->Show();
	w->SetFocus();
	w->SetStatusText("Ready.");

	return true;
}

void MainWindow::ApplyPatches(wxCommandEvent& event) {
	HWND win = FindWindowW(NULL, L"Mirror's Edge™ Catalyst");

	bool patchFailed = false;

	if (win) {
		DWORD pid;
		GetWindowThreadProcessId(win, &pid);
		HANDLE hProc = OpenProcess(PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, pid);

		if (hProc) {
			BYTE newData1[29] = "localhost";
			BYTE newData2[] = { 0x31 };
			BYTE newData3[] = { 0xE9, 0xC7, 0x00 };

			// Update redirector hostname
			if (WriteProcessMemory(hProc, (LPVOID)0x141D80890, &newData1, (DWORD)sizeof(newData1), NULL)) {
				SetStatusText("Success!");
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
				connectButton->SetBitmap(black_png_to_wx_bitmap());
				patchFailed = true;
			}

			// Disable TLS in Connect function
			if (WriteProcessMemory(hProc, (LPVOID)0x142DBE9B0, &newData2, (DWORD)sizeof(newData2), NULL) && !patchFailed) {
				SetStatusText("Success!");
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
				connectButton->SetBitmap(black_png_to_wx_bitmap());
				patchFailed = true;
			}

			// Bypass encryption of authenticated requests
			if (WriteProcessMemory(hProc, (LPVOID)0x1439C0D81, &newData3, (DWORD)sizeof(newData3), NULL) && !patchFailed) {
				SetStatusText("Success!");
				connectButton->SetBitmap(red_png_to_wx_bitmap());
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
				connectButton->SetBitmap(black_png_to_wx_bitmap());
				patchFailed = true;
			}

			CloseHandle(hProc);
		} else {
			SetStatusText("ERROR: Unable to open process.");
			connectButton->SetBitmap(black_png_to_wx_bitmap());
		}
	} else {
		SetStatusText("ERROR: Window not found.");
		connectButton->SetBitmap(black_png_to_wx_bitmap());
	}
}
