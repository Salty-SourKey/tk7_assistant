#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <conio.h>

#include "game.h"
#include "utils.h"

#define LK 90
#define RK 88
#define LP 65
#define RP 83
#define AP 91
#define AK 92

using namespace std;

Game::Game(){

}

Game::~Game(){

}

void Game::parse(string dataPath){
    ifstream moveData(dataPath);
    if(!moveData.good())
    {
        cout << "Error: Could not open data file: " + dataPath << '\n';
        return;
    }

    getline(moveData, this->moveName);
    getline(moveData, this->tips);
    moveData >> this->frameUnit;

    while(!moveData.eof()){
        std::string dir, move;
        moveData >> dir >> move;
        dirs.push_back(dir);
        moves.push_back(move);
    }
    moveData.close();
}

void Game::printInfo(){
    if(moveName == "") return;
    cout << "기술 이름: " << moveName << endl;
    cout << "입력 출력 주기: " << frameUnit << endl;
}

void Game::drawGrid(){
    system("cls");

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 181; j++){
            if(i == 2)
                printColor(0xf7, j, i * 2 + 1, " ");
            else
                printColor(0x17, j, i * 2 + 1, "─");
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 181; j <= 220; j++){
            if(i == 1)
                printColor(0xf7, j, i * 4 + 1, " ");
            else
                printColor(0x17, j, i * 4 + 1, "─");
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j <= 60; j++){
            printColor(0x17, j * 3, i * 2 + 2, "|");
        }
    }

    printColor(0x17, 220, 2, "|");
    printColor(0x17, 220, 3, "|");
    printColor(0x17, 220, 4, "|");
    printColor(0x17, 220, 6, "|");
    printColor(0x17, 220, 7, "|");
    printColor(0x17, 220, 8, "|");

    printColor(0x07, 0, 0, "기술 이름: " + this->moveName);
    printColor(0x0f, 195, 3, "유저 입력");
    printColor(0x0f, 195, 7, "정답 입력");
    printColor(0x2f, 176, 10, " ");
    printColor(0x0f, 178, 10, "다시 시작하시려면 v와 s키를 동시에 누르세요");
    printColor(0x2f, 176, 11, " ");
    printColor(0x0f, 179, 11, "기술 목록으로 돌아가려면 0키를 누르세요");

    for(int i = 0; i < 60; i++){
        if(dirs[i] != "N")
            printColor(0x0f, i * 3 + 1, 6, dirs[i]);
        if(moves[i] != "N")
            printColor(0x0f, i * 3 + 1, 8, moves[i]);
    }

    printColor(0x0f, 1, 11, "TIPS: " + this->tips);
}

void Game::play(){
    int last_action = 0;
    int last_direction = 0;
    // [LP, RP, LK, RK, DOWN, LEFT, RIGHT, UP]
    bool is_down[8] = {false};
    while(_kbhit()) _getch();
    drawGrid();

    while(true){
        // wait until z and v are pressed together
        if(GetAsyncKeyState(0x5A) && GetAsyncKeyState(0x56)){
            for(int i = 0; i < 60; i++){
                printColor(0x0f, i * 3 + 1, 2, " ");
                printColor(0x0f, i * 3 + 2, 2, " ");
                printColor(0x0f, i * 3 + 1, 4, " ");
                printColor(0x0f, i * 3 + 2, 4, " ");
            }
            printColor(0x0f, 30, 0, "2초 뒤에 입력이 시작됩니다.");
            Sleep(1000);
            printColor(0x0f, 30, 0, "1초 뒤에 입력이 시작됩니다.");
            Sleep(1000);
            printColor(0x0f, 30, 0, "                           ");

            // Scan input for 2 seconds
            for(int i = 0; i < 60; i++){
                // Scan keyboard input for 1/60 seconds
                auto start_time = chrono::high_resolution_clock::now();
                // loop this scanning process until 1/60 seconds has passed
                while(true){
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit /60.0) {
                        break;
                    }

                    // 1 프레임 동안 눌린 키를 저장
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

                // 이전 프레임 표시 지움
                if(i > 0){
                    printColor(0xff, (i - 1) * 3 + 1, 5, " ");
                    printColor(0xff, (i - 1) * 3 + 2, 5, " ");
                }
                
                // 현재 프레임 표시
                printColor(0xaf, i * 3 + 1, 5, " ");
                printColor(0xaf, i * 3 + 2, 5, " ");


                // 키 입력에 따라 표시
                if (is_down[0] && is_down[1]){
                    if(last_action != AP){
                        printColor(0x0f, i * 3 + 1, 2, "AP");
                        last_action = AP;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }          
                }
                else if(is_down[2] && is_down[3]){
                    if(last_action != AK){
                        printColor(0x0f, i * 3 + 1, 2, "AK");
                        last_action = AK;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }
                }
                else if(is_down[0]){
                    if(last_action != LP){
                        printColor(0x0f, i * 3 + 1, 2, "LP");
                        last_action = LP;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }
                }
                else if(is_down[1]){
                    if(last_action != RP){
                        printColor(0x0f, i * 3 + 1, 2, "RP");
                        last_action = RP;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }
                }
                else if(is_down[2]){
                    if(last_action != LK){
                        printColor(0x0f, i * 3 + 1, 2, "LK");
                        last_action = LK;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }
                }
                else if(is_down[3]){
                    if(last_action != RK){
                        printColor(0x0f, i * 3 + 1, 2, "RK");
                        last_action = RK;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 2, " ");
                    }
                }
                else{
                    printColor(0x0f, i * 3 + 1, 2, " ");
                    last_action = 0;
                }
                
                if(is_down[4] && is_down[5]){
                    if(last_direction != 1){
                        printColor(0x0f, i * 3 + 1, 4, "1");
                        last_direction = 1;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[4] && is_down[6]){
                    if(last_direction != 3){
                        printColor(0x0f, i * 3 + 1, 4, "3");
                        last_direction = 3;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[7] && is_down[5]){
                    if(last_direction != 7){
                        printColor(0x0f, i * 3 + 1, 4, "7");
                        last_direction = 7;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[7] && is_down[6]){
                    if(last_direction != 9){
                        printColor(0x0f, i * 3 + 1, 4, "9");
                        last_direction = 9;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[4]){
                    if(last_direction != 2){
                        printColor(0x0f, i * 3 + 1, 4, "2");
                        last_direction = 2;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[5]){
                    if(last_direction != 4){
                        printColor(0x0f, i * 3 + 1, 4, "4");
                        last_direction = 4;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[6]){
                    if(last_direction != 6){
                        printColor(0x0f, i * 3 + 1, 4, "6");
                        last_direction = 6;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else if(is_down[7]){
                    if(last_direction != 8){
                        printColor(0x0f, i * 3 + 1, 4, "8");
                        last_direction = 8;
                    }
                    else {
                        printColor(0x0f, i * 3 + 1, 4, " ");
                    }
                }
                else{
                    printColor(0x0f, i * 3 + 1, 4, " ");
                    last_direction = 0;
                }


                for(int i = 0; i < 8; i++)  is_down[i] = false;
            }
        }
        // if 0 is pressed, return to the move list
        else if(GetAsyncKeyState(0x30)){
            break;
        }
    }

}