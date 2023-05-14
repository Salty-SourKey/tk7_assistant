#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>

#include "utils.h"
#include "game.h"


using namespace std;

void displayMenu(){
    SetConsoleTitle("TK Assistant");
    setWindowPosition();
    system("cls");
    system("Color 0f");
    system("mode con: cols=230 lines=13");
    cout << "_______________  __.    _____                .__          __                 __   \n";
    cout << "\\__    ___/    |/ _|   /  _  \\   ______ _____|__| _______/  |______    _____/  |_ \n";
    cout << "  |    |  |      <    /  /_\\  \\ /  ___//  ___/  |/  ___/\\   __\\__  \\  /    \\   __\\\n";
    cout << "  |    |  |    |  \\  /    |    \\\\___ \\ \\___ \\|  |\\___ \\  |  |  / __ \\|   |  \\  |  \n";
    cout << "  |____|  |____|__ \\ \\____|__  /____  >____  >__/____  > |__| (____  /___|  /__|  \n";
    cout << "\n";
    printCenter(0x1b, 45, "Main Menu");
    printCenter(0x1d, 45, "1. ��� ����");
    printCenter(0x1d, 45, "0. ����");
}

void moveMenu(){
    char menu;

    do{
        system("Color 0f");
        system("cls");
        while(_kbhit()) _getch();
        printCenter(0x1b, 45, "���� ���� ��� ���");
        printCenter(0x0f, 45, "1: �ر�");
        printCenter(0x0f, 45, "2: �ʼ�ǳ�ű�");
        printCenter(0x0f, 45, "3: �߻�+����");
        printCenter(0x0f, 45, "0: �ڷΰ���");
        menu = getch();
        if(menu == '1'){            
            Game game;
            game.parse("moves/�ر�.txt");
            game.play();
        }
        else if(menu == '2'){
            Game game;
            game.parse("moves/�ʼ�ǳ�ű�.txt");
            game.play();
        }
        else if(menu == '3'){
            Game game;
            game.parse("moves/�߻����.txt");
            game.play();
            
        }
    } while(menu != '0');

    displayMenu();
}

int main(){

    char menu;

    do{
        displayMenu();
        menu = _getch();
        system("cls");

        if(menu == '1'){
            moveMenu();
        }
    } while(menu != '0');
    return 0;
}