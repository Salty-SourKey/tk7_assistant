#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <conio.h>


#include "game.h"
#include "utils.h"

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
    frameUnit = 2.0;

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
            printColor(0x17, j, i * 2 + 1, "─");
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 181; j <= 220; j++){
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

    printColor(0x17, 0, 0, "기술 이름: " + this->moveName);
    printColor(0x0f, 195, 3, "유저 입력");
    printColor(0x0f, 195, 7, "정답 입력");
    printColor(0x2f, 176, 11, " ");
    printColor(0x0f, 178, 11, "다시 시작하시려면 v와 s키를 동시에 누르세요");
    printColor(0x2f, 176, 12, " ");
    printColor(0x0f, 179, 12, "기술 목록으로 돌아가려면 0키를 누르세요");

    for(int i = 0; i < 60; i++){
        if(dirs[i] != "N")
            printColor(0x0f, i * 3 + 1, 6, dirs[i]);
        if(moves[i] != "N")
            printColor(0x0f, i * 3 + 1, 8, moves[i]);
    }

    printColor(0x0f, 1, 11, "TIPS: 3 입력과 RP 입력이 동시에 이루어져야 합니다");
}

void Game::play(){
    drawGrid();
}