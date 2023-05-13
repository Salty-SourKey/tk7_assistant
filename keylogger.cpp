#include <iostream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <conio.h> // for _kbhit() and _getch()

#define LK 90
#define RK 88
#define LP 65
#define RP 83

#define KEY_DOWN 80
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int main()
{
    char input;
    // [LP, RP, LK, RK, DOWN, LEFT, RIGHT, UP]
    bool is_down[8] = {false, false, false, false, false, false, false, false};

    // Open txt file to write inputs
    ofstream myfile;
    myfile.open ("inputs.txt");
    
    
    cout << "Press any key to start" << '\n';
    while(!_kbhit()){}

    cout << "Start scanning after 2 seconds" << '\n';
    Sleep(2000);
    cout << "Start scanning!!!!!!" << '\n';

    
    // Scan input for 2 seconds
    for(int i = 0; i < 60; i++){
        // Scan keyboard input for 1/60 seconds
        auto start_time = chrono::high_resolution_clock::now();
        // loop this scanning process until 1/60 seconds has passed
        while(true){
            if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= 2.0/60.0) {
                break;
            }

            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                is_down[4] = true;
            }
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                is_down[5] = true;
            }
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                is_down[6] = true;
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                is_down[7] = true;
            }
            
            if (GetAsyncKeyState(LP) & 0x8000) {
                is_down[0] = true;
            }
            if (GetAsyncKeyState(RP) & 0x8000) {
                is_down[1] = true;
            }
            if (GetAsyncKeyState(LK) & 0x8000) {
                is_down[2] = true;
            }
            if (GetAsyncKeyState(RK) & 0x8000) {
                is_down[3] = true;
            }
        }
        
        if (is_down[0] && is_down[1]){
            myfile << "<AP> ";            
        }
        else if(is_down[2] && is_down[3]){
            myfile << "<AK> ";
        }
        else if(is_down[0]){
            myfile << "<LP> ";
        }
        else if(is_down[1]){
            myfile << "<RP> ";
        }
        else if(is_down[2]){
            myfile << "<LK> ";
        }
        else if(is_down[3]){
            myfile << "<RK> ";
        }
        else{
            myfile << "<  > ";
        }
        
        if(is_down[4] && is_down[5]){
            myfile << "<1>" << '\n';
        }
        else if(is_down[4] && is_down[6]){
            myfile << "<3>" << '\n';
        }
        else if(is_down[7] && is_down[5]){
            myfile << "<7>" << '\n';
        }
        else if(is_down[7] && is_down[6]){
            myfile << "<9>" << '\n';
        }
        else if(is_down[4]){
            myfile << "<2>" << '\n';
        }
        else if(is_down[5]){
            myfile << "<4>" << '\n';
        }
        else if(is_down[6]){
            myfile << "<6>" << '\n';
        }
        else if(is_down[7]){
            myfile << "<8>" << '\n';
        }
        else{
            myfile << "< >" << '\n';
        }


        for(int i = 0; i < 8; i++)  is_down[i] = false;
    }

    cout << "Done!" << '\n';
    myfile.close();
    return 0;
}