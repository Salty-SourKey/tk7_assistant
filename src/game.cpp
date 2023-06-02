#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <set>

#include "game.h"
#include "utils.h"

#define AP 91
#define AK 92

// a: 65
// s: 83
// z: 90
// x: 88

// u: 85
// i: 73
// j: 74
// k: 75  

// a: 65 
// d: 68 
// w: 87 
// s: 83  
// VK_LEFT 37
// VK_RIGHT 39
// VK_UP 38
// VK_DOWN 40

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
    cout << "��� �̸�: " << moveName << endl;
    cout << "�Է� ��� �ֱ�: " << frameUnit << endl;
}

void Game::drawGrid(){
    system("cls");

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 181; j++){
            if(i == 2)
                printColor(0xf7, j, i * 2 + 1, " ");
            else
                printColor(0x17, j, i * 2 + 1, "��");
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 181; j <= 220; j++){
            if(i == 1)
                printColor(0xf7, j, i * 4 + 1, " ");
            else
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

    printColor(0x07, 0, 0, "��� �̸�: " + this->moveName);
    printColor(0x0f, 182, 0, "Ŀ�ǵ�: " + this->command);
    printColor(0x0f, 195, 3, "���� �Է�");
    printColor(0x0f, 195, 7, "���� �Է�");
    printColor(0x2f, 176, 10, " ");
    printColor(0x0f, 178, 10, "�ٽ� �����Ͻ÷��� �����̽��ٸ� ��������");
    printColor(0x2f, 176, 11, " ");
    printColor(0x0f, 179, 11, "��� ������� ���ư����� 0Ű�� ��������");

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
    string line;
    vector<int> inputTime;
    set<int> moveRecord[60];
    set<int> dirRecord[60];

    int LP, RP, LK, RK, LEFT, RIGHT, UP, DOWN;
    ifstream configFile("config.txt");
    while (getline(configFile, line)){
        string variable, value;
        size_t equalsPos = line.find('=');

        if (equalsPos != std::string::npos) {
            variable = line.substr(0, equalsPos);
            value = line.substr(equalsPos + 1);

            if(variable == "LP") LP = stoi(value);
            else if(variable == "RP") RP = stoi(value);
            else if(variable == "LK") LK = stoi(value);
            else if(variable == "RK") RK = stoi(value);
            else if(variable == "LEFT") LEFT = stoi(value);
            else if(variable == "RIGHT") RIGHT = stoi(value);
            else if(variable == "UP") UP = stoi(value);
            else if(variable == "DOWN") DOWN = stoi(value);
        }
    }

    while(_kbhit()) _getch();
    drawGrid();



    while(true){
        // wait until z and v are pressed together
        if(GetAsyncKeyState(VK_SPACE)){
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
            inputTime.clear();

            // �߻�+���� ����ó��
            if(this->moveName == "�߻�+����")
                this->important_input_2 = "*";
            printColor(0x0f, 30, 0, "                                                                                                                                         ");
            printColor(0x0f, 30, 0, "�Է��� ���۵˴ϴ�.");
            Sleep(100);
            printColor(0x0f, 30, 0, "                           ");

            // Scan input for 2 seconds
            for(int i = 0; i < 60; i++){
                // Scan keyboard input for 1/60 seconds
                auto start_time = chrono::high_resolution_clock::now();
                // loop this scanning process until 1/60 seconds has passed
                while(true){

                    // ���� ������ ǥ�� ����
                    if(i > 0){
                        printColor(0xff, (i - 1) * 3 + 1, 5, " ");
                        printColor(0xff, (i - 1) * 3 + 2, 5, " ");
                    }
                    
                    // ���� ������ ǥ��
                    printColor(0xaf, i * 3 + 1, 5, " ");
                    printColor(0xaf, i * 3 + 2, 5, " ");

                    // 1 ������ ���� ���� Ű�� ����
                    if (GetAsyncKeyState(DOWN) & 0x8000) {
                        dirRecord[i].insert(2);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(LEFT) & 0x8000) {
                        dirRecord[i].insert(4);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(RIGHT) & 0x8000) {
                        dirRecord[i].insert(6);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(UP) & 0x8000) {
                        dirRecord[i].insert(8);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(LP) & 0x8000) {
                        moveRecord[i].insert(LP);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(RP) & 0x8000) {
                        moveRecord[i].insert(RP);
                    }
                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(LK) & 0x8000) {
                        moveRecord[i].insert(LK);
                    }

                    if (chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start_time).count() >= this->frameUnit / 60.0) {
                        break;
                    }
                    if (GetAsyncKeyState(RK) & 0x8000) {
                        moveRecord[i].insert(RK);
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
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else if(dirRecord[i].find(2) != dirRecord[i].end() && dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2   == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end() && dirRecord[i].find(4) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end() && dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }

                else if(dirRecord[i].find(2) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else if(dirRecord[i].find(4) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else if(dirRecord[i].find(6) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        
                        last_dir = "��";

                        //�߻�+���� ����ó��
                        if(this->moveName == "�߻�+����")
                            this->important_input_2 = "��";
                    }
                }
                else if(dirRecord[i].find(8) != dirRecord[i].end()){
                    if(last_dir == "��"){
                        goto printMove;
                    }
                    else{
                        printColor(0x0f, i * 3 + 1, 4, "��");
                        if(frame_record_1 == 0 && this->important_input_1 == "��")
                            frame_record_1 = i;
                        else if(frame_record_2 == 0 && this->important_input_2 == "��")
                            frame_record_2 = i;
                        last_dir = "��";
                    }
                }
                else{
                    empty_dir_cnt++;
                }

                printMove:
                if(moveRecord[i].find(LP) != moveRecord[i].end() && moveRecord[i].find(RP) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }

                    
                }
                else if(moveRecord[i].find(LK) != moveRecord[i].end() && moveRecord[i].find(RK) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }
                }
                else if(moveRecord[i].find(LK) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }
                }
                else if(moveRecord[i].find(RK) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }
                }
                else if(moveRecord[i].find(LP) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }
                }
                else if(moveRecord[i].find(RP) != moveRecord[i].end()){
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
                        inputTime.push_back(i);
                    }
                }
                else{
                    empty_move_cnt++;
                }

                printEnd:
                    continue;
                
            }
            if(this->moveName == "���ֽõ�"){
                vector<int> timeDiff(3, 0);
                if(inputTime.size( ) > 3){
                    for(int i = 0; i < inputTime.size() - 1; i++){
                        timeDiff[i] = inputTime[i + 1] - inputTime[i];
                    }
                }
               
                printColor(0x0e, 30, 0, "���ֽõ� Ŀ�ǵ� �� �Է� ������ " + to_string(timeDiff[0]) + " " + to_string(timeDiff[1]) + " " + to_string(timeDiff[2]));
            }
            else if(frame_record_2 - frame_record_1 < this->correctDiff){
                printColor(0x0e, 30, 0, this->important_input_1 + " �Է� ���� " + this->important_input_2 + "�Է��� �����ϴ�. �� �Է� �� �䱸�Ǵ� ���̴� " + to_string(this->correctDiff) + "ĭ�̸�, ���� �� �Է��� ���̴� " + to_string(frame_record_2 - frame_record_1) + "ĭ�Դϴ�." );
            }
            else if(frame_record_2 - frame_record_1 > this->correctDiff){
                printColor(0x0e, 30, 0, this->important_input_1 + " �Է� ���� " + this->important_input_2 + "�Է��� �����ϴ�. �� �Է� �� �䱸�Ǵ� ���̴� " + to_string(this->correctDiff) + "ĭ�̸�, ���� �� �Է��� ���̴� " + to_string(frame_record_2 - frame_record_1) + "ĭ�Դϴ�.");
            }
            else{
                printColor(0x0e, 30, 0, " �߿� �Է��� Ÿ�̹��� �½��ϴ�.");
            }

        }
        // if 0 is pressed, return to the move list
        else if(GetAsyncKeyState(0x30)){
            break;
        }
    }

}