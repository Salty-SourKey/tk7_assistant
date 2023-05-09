#include <iostream>
#include <windows.h>
#include <tchar.h>

#define LK 90
#define RK 88
#define LP 65
#define RP 83

using namespace std;

bool is_down_2 = false;
bool is_down_4 = false;
bool is_down_6 = false;
bool is_down_8 = false;
bool is_down_LK = false;
bool is_down_RK = false;
bool is_down_LP = false;
bool is_down_RP = false;

bool is_key_printed[9] = {false, false, false, false, false, false, false, false, false};
bool is_attack_printed[6] = {false, false, false, false, false, false};

void init_key_printed(){
    for (int i = 0; i < 9; i++){
        is_key_printed[i] = false;
    }
}

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) (lParam);
	


	// If key is being pressed
	if (wParam == WM_KEYDOWN) {
		switch (p->vkCode) {

			//  Move keys
			case VK_LEFT:
                is_down_4 = true;
                break;

			case VK_RIGHT:
                is_down_6 = true;
                break;

			case VK_UP:
                is_down_8 = true;
                break;

			case VK_DOWN:
                is_down_2 = true;
                break;

			//  Attack keys
			case LK:
                is_down_LK = true;
                break;

			case RK:
                is_down_RK = true;
                break;

            case LP:
                is_down_LP = true;
                break;

            case RP:
                is_down_RP = true;
                break;
		}
	}

    if (wParam == WM_KEYUP) {
        switch (p->vkCode) {

            //  Move keys
            case VK_DOWN:
                is_down_2 = false;
                init_key_printed();
                break;

            case VK_UP:
                is_down_8 = false;
                init_key_printed();
                break;

            case VK_RIGHT:
                is_down_6 = false;
                init_key_printed();
                break;
            
            case VK_LEFT:
                is_down_4 = false;
                init_key_printed();

            //  Attack keys
            case LK:
                is_down_LK = false;
                is_attack_printed[0] = false;
                is_attack_printed[2] = false;
                break;

			case RK:
                is_down_RK = false;
                is_attack_printed[0] = false;
                is_attack_printed[3] = false;
                break;

            case LP:
                is_down_LP = false;
                is_attack_printed[1] = false;
                is_attack_printed[4] = false;
                break;

            case RP:
                is_down_RP = false;
                is_attack_printed[1] = false;
                is_attack_printed[5] = false;
                break;
        }
    }

    if (is_down_2 && is_down_4 && !is_key_printed[0]){
        cout << "\r" << "<1> ";
        is_key_printed[0] = true;
    }
    else if (is_down_2 && is_down_6 && !is_key_printed[2]){
        cout << "\r" << "<3> ";
        is_key_printed[2] = true;
    }
    else if (is_down_8 && is_down_4 && !is_key_printed[6]){
        cout << "\r" << "<7> ";
        is_key_printed[6] = true;
    }
    else if (is_down_8 && is_down_6 && !is_key_printed[8]){
        cout << "\r" << "<9> ";
        is_key_printed[8] = true;
    }
    else if (is_down_2 && !is_key_printed[1]){
        cout << "\r" << "<2> ";
        is_key_printed[1] = true;
    }
    else if (is_down_4 && !is_key_printed[3]){
        cout << "\r" << "<4> ";
        is_key_printed[3] = true;
    }
    else if (is_down_6 && !is_key_printed[5]){
        cout << "\r" << "<6> ";
        is_key_printed[5] = true;
    }
    else if (is_down_8 && !is_key_printed[7]){
        cout << "\r" << "<8> ";
        is_key_printed[7] = true;
    }

    
    if (is_down_LK && is_down_RK && !is_attack_printed[0]){
        cout << "\r\n" << "<AK> ";
        is_attack_printed[0] = true;
    }
    else if (is_down_LP && is_down_RP && !is_attack_printed[1]){
        cout << "\r\n" << "<AP> ";
        is_attack_printed[1] = true;
    }
    else if (is_down_LK && !is_attack_printed[2]){
        cout << "\r\n" << "<LK> ";
        is_attack_printed[2] = true;
    }
    else if (is_down_RK && !is_attack_printed[3]){
        cout << "\r\n" << "<RK> ";
        is_attack_printed[3] = true;
    }
    else if (is_down_LP && !is_attack_printed[4]){
        cout << "\r\n" << "<LP> ";
        is_attack_printed[4] = true;
    }
    else if (is_down_RP && !is_attack_printed[5]){
        cout << "\r\n" << "<RP> ";
        is_attack_printed[5] = true;
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