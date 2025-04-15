#include <wx/wx.h>

#include "ui/ui.h"

class App : public wxApp { public: virtual bool OnInit(); };

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	wxImage::AddHandler(new wxPNGHandler);

	MainWindow* w = new MainWindow(NULL);
	w->Show();
	w->SetFocus();

	return true;
}

void MainWindow::ApplyPatches(wxCommandEvent& event) {
	HWND win = FindWindowW(NULL, L"Mirror's Edge™ Catalyst");

	if (win) {
		DWORD pid;
		GetWindowThreadProcessId(win, &pid);
		HANDLE hproc = OpenProcess(PROCESS_VM_WRITE|PROCESS_VM_OPERATION, FALSE, pid);

		if (hproc) {
			BYTE newData1[] = { 0x6C, 0x6F, 0x63, 0x61, 0x6C, 0x68, 0x6F, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Hostname of redirector with padding
			BYTE newData2[] = { 0x31 };
			BYTE newData3[] = { 0xE9, 0xC7, 0x00 };

			// Update redirector hostname
			if (WriteProcessMemory(hproc, (LPVOID)0x141D80890, &newData1, (DWORD)sizeof(newData1), NULL)) {
				SetStatusText("Success!");
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
			}

			// Disable TLS in connect function
			if (WriteProcessMemory(hproc, (LPVOID)0x142DBE9B0, &newData2, (DWORD)sizeof(newData2), NULL)) {
				SetStatusText("Success!");
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
			}

			// Bypass encryption of authenticated requests
			if (WriteProcessMemory(hproc, (LPVOID)0x1439C0D81, &newData3, (DWORD)sizeof(newData3), NULL)) {
				SetStatusText("Success!");
			} else {
				SetStatusText("ERROR: WriteProcessMemory failed.");
			}

			CloseHandle(hproc);
		} else {
			SetStatusText("ERROR: Unable to open process.");
		}
	} else {
		SetStatusText("ERROR: Window not found.");
	}
}
