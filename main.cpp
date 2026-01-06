#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
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

std::string ReadJson() {
	using json = nlohmann::json;

	std::ifstream f("user.json");

	try {
		json data = json::parse(f);
		return data["authCode"];
	} catch (json::exception) {
		return std::string();
	}
}

void MainWindow::ApplyPatches(wxCommandEvent& event) {
	HWND win = FindWindowW(NULL, L"Mirror's Edge™ Catalyst");

	std::string newAuthCode = ReadJson();

	SetStatusText("", 1);
	connectButton->SetBitmap(black_png_to_wx_bitmap());

	if (win) {
		DWORD pid;
		GetWindowThreadProcessId(win, &pid);
		HANDLE hProc = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);

		if (hProc) {
			BYTE hostname[29] = "localhost";

			BYTE newData1[] = { 0x31 };
			BYTE newData2[] = { 0xE9, 0xC7, 0x00 };
			BYTE newData3[] = { 0x15, 0x28, 0x04, 0x3B, 0xFE };
			BYTE newData4[] = { 0x40, 0xB3, 0xC3, 0x41, 0x01 };

			try {
				// Update redirector hostname
				WriteProcessMemory(hProc, (LPVOID)0x141D80890, &hostname, (DWORD)sizeof(hostname), NULL);

				// Disable TLS in Connect function
				WriteProcessMemory(hProc, (LPVOID)0x142DBE9B0, &newData1, (DWORD)sizeof(newData1), NULL);

				// Bypass encryption of authenticated requests
				WriteProcessMemory(hProc, (LPVOID)0x1439C0D81, &newData2, (DWORD)sizeof(newData2), NULL);

				SetStatusText("Success!");
				connectButton->SetBitmap(red_png_to_wx_bitmap());
			} catch (...) {
				SetStatusText("Error: WriteProcessMemory failed.");
			}

			// Update authorization code
			if (!newAuthCode.empty()) {
				try {
					// Point to fixed memory address
					WriteProcessMemory(hProc, (LPVOID)0x14388AED3, &newData3, (DWORD)sizeof(newData3), NULL);

					// Write pointer
					WriteProcessMemory(hProc, (LPVOID)0x141C3B300, &newData4, (DWORD)sizeof(newData4), NULL);

					// Write new auth code
					WriteProcessMemory(hProc, (LPVOID)0x141C3B340, newAuthCode.c_str(), newAuthCode.length(), NULL);

					SetStatusText("AUTH", 1);
				} catch (...) {
					SetStatusText("FAIL", 1);
				}
			}

			CloseHandle(hProc);
		} else {
			SetStatusText("Error: Unable to open process.");
		}
	} else {
		SetStatusText("Error: Window not found.");
	}
}
