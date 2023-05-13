#include <iostream>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <conio.h> // for _kbhit() and _getch()

#define LK 90
#define RK 88
#define LP 65
#define RP 83
#define AP 91
#define AK 92

using namespace std;

int main()
{
    char input;
    int last_action = 0;
    int last_direction = 0;
    // [LP, RP, LK, RK, DOWN, LEFT, RIGHT, UP]
    bool is_down[8] = {false};

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
            if(last_action != AP){
                myfile << "<AP> ";
                last_action = AP;
            }
            else {
                myfile << "<  > ";
            }          
        }
        else if(is_down[2] && is_down[3]){
            if(last_action != AK){
                myfile << "<AK> ";
                last_action = AK;
            }
            else {
                myfile << "<  > ";
            }
        }
        else if(is_down[0]){
            if(last_action != LP){
                myfile << "<LP> ";
                last_action = LP;
            }
            else {
                myfile << "<  > ";
            }
        }
        else if(is_down[1]){
            if(last_action != RP){
                myfile << "<RP> ";
                last_action = RP;
            }
            else {
                myfile << "<  > ";
            }
        }
        else if(is_down[2]){
            if(last_action != LK){
                myfile << "<LK> ";
                last_action = LK;
            }
            else {
                myfile << "<  > ";
            }
        }
        else if(is_down[3]){
            if(last_action != RK){
                myfile << "<RK> ";
                last_action = RK;
            }
            else {
                myfile << "<  > ";
            }
        }
        else{
            myfile << "<  > ";
            last_action = 0;
        }
        
        if(is_down[4] && is_down[5]){
            if(last_direction != 1){
                myfile << "<1>" << '\n';
                last_direction = 1;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[4] && is_down[6]){
            if(last_direction != 3){
                myfile << "<3>" << '\n';
                last_direction = 3;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[7] && is_down[5]){
            if(last_direction != 7){
                myfile << "<7>" << '\n';
                last_direction = 7;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[7] && is_down[6]){
            if(last_direction != 9){
                myfile << "<9>" << '\n';
                last_direction = 9;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[4]){
            if(last_direction != 2){
                myfile << "<2>" << '\n';
                last_direction = 2;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[5]){
            if(last_direction != 4){
                myfile << "<4>" << '\n';
                last_direction = 4;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[6]){
            if(last_direction != 6){
                myfile << "<6>" << '\n';
                last_direction = 6;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else if(is_down[7]){
            if(last_direction != 8){
                myfile << "<8>" << '\n';
                last_direction = 8;
            }
            else {
                myfile << "< >" << '\n';
            }
        }
        else{
            myfile << "< >" << '\n';
            last_direction = 0;
        }


        for(int i = 0; i < 8; i++)  is_down[i] = false;
    }

    cout << "Done!" << '\n';
    myfile.close();
    return 0;
}