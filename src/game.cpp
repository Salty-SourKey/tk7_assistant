#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <set>

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
    getline(moveData, this->command);
    getline(moveData, this->tips);
    moveData >> this->frameUnit;
    moveData >> this->important_input_1 >> this->important_input_2;
    moveData >> this->correctDiff;

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
    printColor(0x0f, 182, 0, "커맨드: " + this->command);
    printColor(0x0f, 195, 3, "유저 입력");
    printColor(0x0f, 195, 7, "정답 입력");
    printColor(0x2f, 176, 10, " ");
    printColor(0x0f, 178, 10, "다시 시작하시려면 v와 z키를 동시에 누르세요");
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

    // Save the input timing of important move
    int frame_record_1;
    int frame_record_2;
    int empty_move_cnt = 0;
    int empty_dir_cnt = 0;
    string last_move;
    string last_dir;
    set<int> moveRecord[60];
    set<int> dirRecord[60];

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
                moveRecord[i].clear();
                dirRecord[i].clear();
            }

            last_dir = "";
            last_move = "";
            frame_record_1 = 0;
            frame_record_2 = 0;

            // 발산+용포 예외처리
            if(this->moveName == "발산+용포")
                this->important_input_2 = "*";
            printColor(0x0f, 30, 0, "                                                                                                                                         ");
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

                    // 이전 프레임 표시 지움
                    if(i > 0){
                        printColor(0xff, (i - 1) * 3 + 1, 5, " ");
                        printColor(0xff, (i - 1) * 3 + 2, 5, " ");
                    }
                    
                    // 현재 프레임 표시
                    printColor(0xaf, i * 3 + 1, 5, " ");
                    printColor(0xaf, i * 3 + 2, 5, " ");

                    // 1 프레임 동안 눌린 키를 저장
                    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                        dirRecord[i].insert(2);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                        dirRecord[i].insert(4);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                        dirRecord[i].insert(6);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(VK_UP) & 0x8000) {
                        dirRecord[i].insert(8);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(LP) & 0x8000) {
                        moveRecord[i].insert(65);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(RP) & 0x8000) {
                        moveRecord[i].insert(83);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(LK) & 0x8000) {
                        moveRecord[i].insert(90);
                    }

                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(RK) & 0x8000) {
                        moveRecord[i].insert(88);
                    }

                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                }
            }
            

            // print result
            for(int i = 0; i < 60; i++){
                if(empty_dir_cnt >= 2){
                    last_dir = "";
                    empty_dir_cnt = 0;
                }

                if(empty_move_cnt >= 2){
                    last_move = "";
                    empty_move_cnt = 0;
                }
                if(dirRecord[i].find(2) != dirRecord[i].end() && dirRecord[i].find(4) != dirRecord[i].end()){
                    if(last_dir == "↙"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↙");
                        if(frame_record_1 == 0 && this->important_input_1 == "↙")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "↙")
                            frame_record_2 = i;
                        last_dir = "↙";
                    }
                }
                else if(dirRecord[i].find(2) != dirRecord[i].end() && dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "↘"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↘");
                        if(frame_record_1 == 0 && this->important_input_1 == "↘")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2   == "↘")
                            frame_record_2 = i;
                        last_dir = "↘";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end() && dirRecord[i].find(4) != dirRecord[i].end()){
                    if(last_dir == "↖"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↖");
                        if(frame_record_1 == 0 && this->important_input_1 == "↖")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "↖")
                            frame_record_2 = i;
                        last_dir = "↖";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end() && dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "↗"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↗");
                        if(frame_record_1 == 0 && this->important_input_1 == "↗")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "↗")
                            frame_record_2 = i;
                        last_dir = "↗";
                    }
                }

                else if(dirRecord[i].find(2) != dirRecord[i].end()){
                    if(last_dir == "↓"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↓");
                        if(frame_record_1 == 0 && this->important_input_1 == "↓")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "↓")
                            frame_record_2 = i;
                        last_dir = "↓";
                    }
                }
                else if(dirRecord[i].find(4) != dirRecord[i].end()){
                    if(last_dir == "←"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "←");
                        if(frame_record_1 == 0 && this->important_input_1 == "←")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "←")
                            frame_record_2 = i;
                        last_dir = "←";
                    }
                }
                else if(dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "→"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "→");
                        if(frame_record_1 == 0 && this->important_input_1 == "→")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "→")
                            frame_record_2 = i;
                        
                        last_dir = "→";

                        //발산+용포 예외처리
                        if(this->moveName == "발산+용포")
                            this->important_input_2 = "→";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end()){
                    if(last_dir == "↑"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "↑");
                        if(frame_record_1 == 0 && this->important_input_1 == "↑")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "↑")
                            frame_record_2 = i;
                        last_dir = "↑";
                    }
                }
                else{
                    empty_dir_cnt++;
                }

                printMove:
                if(moveRecord[i].find(65) != moveRecord[i].end() && moveRecord[i].find(83) != moveRecord[i].end()){
                    if(last_move == "AP"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "AP");
                        if(frame_record_1 == 0 && this->important_input_1 == "AP")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "AP")
                            frame_record_2 = i;
                        last_move = "AP";
                    }

                    
                }
                else if(moveRecord[i].find(90) != moveRecord[i].end() && moveRecord[i].find(88) != moveRecord[i].end()){
                    if(last_move == "AK"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "AK");
                        if(frame_record_1 == 0 && this->important_input_1 == "AK")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "AK")
                            frame_record_2 = i;
                        last_move = "AK";
                    }
                }
                else if(moveRecord[i].find(90) != moveRecord[i].end()){
                    if(last_move == "LK"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "LK");
                        if(frame_record_1 == 0 && this->important_input_1 == "LK")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "LK")
                            frame_record_2 = i;
                        last_move = "LK";
                    }
                }
                else if(moveRecord[i].find(88) != moveRecord[i].end()){
                    if(last_move == "RK"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "RK");
                        if(frame_record_1 == 0 && this->important_input_1 == "RK")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "RK")
                            frame_record_2 = i;
                        last_move = "RK";
                    }
                }
                else if(moveRecord[i].find(65) != moveRecord[i].end()){
                    if(last_move == "LP"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "LP");
                        if(frame_record_1 == 0 && this->important_input_1 == "LP")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "LP")
                            frame_record_2 = i;
                        last_move = "LP";
                    }
                }
                else if(moveRecord[i].find(83) != moveRecord[i].end()){
                    if(last_move == "RP"){
                        goto printEnd;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 2, "RP");
                        if(frame_record_1 == 0 && this->important_input_1 == "RP")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "RP")
                            frame_record_2 = i;
                        last_move = "RP";
                    }
                }
                else{
                    empty_move_cnt++;
                }

                printEnd:
                    continue;
                
            }
            if(frame_record_2 - frame_record_1 < this->correctDiff){
                printColor(0x0e, 30, 0, this->important_input_1 + " 입력 이후 " + this->important_input_2 + "입력이 빠릅니다. 두 입력 간 요구되는 차이는 " + to_string(this->correctDiff) + "칸이며, 현재 두 입력의 차이는 " + to_string(frame_record_2 - frame_record_1) + "칸입니다." );
            }
            else if(frame_record_2 - frame_record_1 > this->correctDiff){
                printColor(0x0e, 30, 0, this->important_input_1 + " 입력 이후 " + this->important_input_2 + "입력이 느립니다. 두 입력 간 요구되는 차이는 " + to_string(this->correctDiff) + "칸이며, 현재 두 입력의 차이는 " + to_string(frame_record_2 - frame_record_1) + "칸입니다.");
            }
            else{
                printColor(0x0e, 30, 0, " 중요 입력의 타이밍은 맞습니다.");
            }

        }
        // if 0 is pressed, return to the move list
        else if(GetAsyncKeyState(0x30)){
            break;
        }
    }

}