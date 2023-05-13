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
    frameUnit = 1.0;
    int frameNum = 0;

    while(!moveData.eof()){
        std::string dir, move;
        moveData >> dir >> move;
        dirs.push_back(dir);
        moves.push_back(move);
        frameNum++;
    }
    this->frameNum = frameNum;
    moveData.close();
}

void Game::printInfo(){
    if(moveName == "") return;
    cout << "기술 이름: " << moveName << endl;
    cout << "입력 출력 주기: " << frameUnit << endl;
    cout << "출력 개수: " << frameNum << endl;

    for(int i = 0; i < frameNum; i++){
        cout << dirs[i] << " " << moves[i] << endl;
    }
}

void Game::drawGrid(){
    system("cls");



}