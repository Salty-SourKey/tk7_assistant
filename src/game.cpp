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
    cout << "��� �̸�: " << moveName << endl;
    cout << "�Է� ��� �ֱ�: " << frameUnit << endl;
}

void Game::drawGrid(){
    system("cls");

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 181; j++){
            printColor(0x17, j, i * 2 + 1, "��");
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 181; j <= 220; j++){
            printColor(0x17, j, i * 4 + 1, "��");
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

    printColor(0x17, 0, 0, "��� �̸�: " + this->moveName);
    printColor(0x0f, 195, 3, "���� �Է�");
    printColor(0x0f, 195, 7, "���� �Է�");
    printColor(0x2f, 176, 11, " ");
    printColor(0x0f, 178, 11, "�ٽ� �����Ͻ÷��� v�� sŰ�� ���ÿ� ��������");
    printColor(0x2f, 176, 12, " ");
    printColor(0x0f, 179, 12, "��� ������� ���ư����� 0Ű�� ��������");

    for(int i = 0; i < 60; i++){
        if(dirs[i] != "N")
            printColor(0x0f, i * 3 + 1, 6, dirs[i]);
        if(moves[i] != "N")
            printColor(0x0f, i * 3 + 1, 8, moves[i]);
    }

    printColor(0x0f, 1, 11, "TIPS: 3 �Է°� RP �Է��� ���ÿ� �̷������ �մϴ�");
}

void Game::play(){
    drawGrid();
}