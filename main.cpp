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
    setWindowSize(500, 10);
    cout << "_______________  __.    _____                .__          __                 __   \n";
    cout << "\\__    ___/    |/ _|   /  _  \\   ______ _____|__| _______/  |______    _____/  |_ \n";
    cout << "  |    |  |      <    /  /_\\  \\ /  ___//  ___/  |/  ___/\\   __\\__  \\  /    \\   __\\\n";
    cout << "  |    |  |    |  \\  /    |    \\\\___ \\ \\___ \\|  |\\___ \\  |  |  / __ \\|   |  \\  |  \n";
    cout << "  |____|  |____|__ \\ \\____|__  /____  >____  >__/____  > |__| (____  /___|  /__|  \n";
    cout << "\n";
    printCenter(0x1b, 45, "Main Menu");
    printCenter(0x1d, 45, "1. 기술 선택");
    printCenter(0x1d, 45, "0. 종료");
}

void moveMenu(){
    system("Color 0f");
    printCenter(0x1b, 45, "연습 가능 기술 목록");
    printCenter(0x0f, 45, "1: 붕권");
    printCenter(0x0f, 45, "2: 초속풍신권");
    printCenter(0x0f, 45, "3: 발산+용포");
    printCenter(0x0f, 45, "0: 뒤로가기");

    int moveChoice = 0;
    char menu;

    do{
        menu = getch();
        if(menu == '1'){
            cout << "1 is pressed\n";
            
            Game game;
            game.parse("moves/붕권.txt");
            game.printInfo();
            // game.play();
            
        }
        else if(menu == '2'){
            cout << "2 is pressed\n";
            /*
            Game game;
            game.parse("../moves/초속풍신권.txt");
            game.play();
            */
        }
        else if(menu == '3'){
            cout << "3 is pressed\n";
            /*
            Game game;
            game.parse("../moves/발산용포.txt");
            game.play();
            */

        }
    } while(menu != '0');

    if(menu == '0')
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