#include <iostream>
#include <windows.h>
#include <tchar.h>

#define LK 90
#define RK 88
#define LP 65
#define RP 83




using namespace std;


LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);
	bool g_1_pressed = false;
    bool g_2_pressed = false;
    bool g_3_pressed = false;
    bool g_4_pressed = false;
    bool g_5_pressed = false;
    bool g_6_pressed = false;
    bool g_7_pressed = false;
    bool g_8_pressed = false;
    bool g_9_pressed = false;


	// If key is being pressed
	if (wParam == WM_KEYDOWN) {
		switch (p->vkCode) {

			//  Move keys
			case VK_LEFT:
                if (g_2_pressed)
                    g_1_pressed = true;
                else if (g_8_pressed)
                    g_7_pressed = true;
                else
                    g_4_pressed = true;
                break;

			case VK_RIGHT:
                if (g_2_pressed)
                    g_3_pressed = true;
                else if (g_8_pressed)
                    g_9_pressed = true;
                else
                    g_6_pressed = true;
                break;

			case VK_UP:
                if (g_4_pressed)
                    g_7_pressed = true;
                else if (g_6_pressed)
                    g_9_pressed = true;
                else
                    g_8_pressed = true;
                break;

			case VK_DOWN:
                if (g_4_pressed)
                    g_1_pressed = true;
                else if (g_6_pressed)
                    g_3_pressed = true;
                else
                    g_2_pressed = true;
                break;

			//  Attack keys
			case LK:
                if(GetAsyncKeyState(RK) & 0x8000)
                    cout << "<AK>" << '\n';
                else
                    cout << "<LK>" << '\n';
                break;

			case RK:
                if(GetAsyncKeyState(LK) & 0x8000)
                    cout << "<AK>" << '\n';
                else
                    cout << "<RK>" << '\n';
                break;

            case LP:
                if(GetAsyncKeyState(RP) & 0x8000)
                    cout << "<AP>" << '\n';
                else
                    cout << "<LP>" << '\n';
                break;

            case RP:
                if(GetAsyncKeyState(LP) & 0x8000)
                    cout << "<AP>" << '\n';
                else
                    cout << "<RP>" << '\n';
                break;
		}
	}

    else if (wParam == WM_KEYUP) {
        switch (p->vkCode) {
            case VK_DOWN:
                g_1_pressed = false;
                g_2_pressed = false;
                g_3_pressed = false;
                break;

            case VK_UP:
                g_7_pressed = false;
                g_8_pressed = false;
                g_9_pressed = false;
                break;

            case VK_RIGHT:
                g_3_pressed = false;
                g_6_pressed = false;
                g_9_pressed = false;
                break;
            
            case VK_LEFT:
                g_1_pressed = false;
                g_4_pressed = false;
                g_7_pressed = false;
                break;
        }

        if(g_1_pressed) cout << 1 << '\n';
        else if(g_2_pressed) cout << 2 << '\n';
        else if(g_3_pressed) cout << 3 << '\n';
        else if(g_4_pressed) cout << 4 << '\n';
        else if(g_5_pressed) cout << 5 << '\n';
        else if(g_6_pressed) cout << 6 << '\n';
        else if(g_7_pressed) cout << 7 << '\n';
        else if(g_8_pressed) cout << 8 << '\n';
        else if(g_9_pressed) cout << 9 << '\n';
    }

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// Set windows hook
	HHOOK keyboardHook = SetWindowsHookEx(
		WH_KEYBOARD_LL,
		keyboardHookProc,
		hInstance,
		0);

	MessageBox(NULL, _T("Press OK to stop logging."), _T("Information"), MB_OK);
	return 0;
}