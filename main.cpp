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
    
    cout << " /$$$$$$$$ /$$   /$$              /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$  /$$$$$$  /$$$$$$$$ /$$$$$$  /$$   /$$ /$$$$$$$$" << '\n';
    cout << "|__  $$__/| $$  /$$/             /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/ /$$__  $$|__  $$__//$$__  $$| $$$ | $$|__  $$__/" << '\n';
    cout << "   | $$   | $$ /$$/             | $$  \\ $$| $$  \\__/| $$  \\__/  | $$  | $$  \\__/   | $$  | $$  \\ $$| $$$$| $$   | $$" << '\n';  
    cout << "   | $$   | $$$$$/              | $$$$$$$$|  $$$$$$ |  $$$$$$   | $$  |  $$$$$$    | $$  | $$$$$$$$| $$ $$ $$   | $$" << '\n';  
    cout << "   | $$   | $$  $$              | $$__  $$ \\____  $$ \\____  $$  | $$   \\____  $$   | $$  | $$__  $$| $$  $$$$   | $$" << '\n';  
    cout << "   | $$   | $$\\  $$             | $$  | $$ /$$  \\ $$ /$$  \\ $$  | $$   /$$  \\ $$   | $$  | $$  | $$| $$\\  $$$   | $$" << '\n';  
    cout << "   | $$   | $$ \\  $$            | $$  | $$|  $$$$$$/|  $$$$$$/ /$$$$$$|  $$$$$$/   | $$  | $$  | $$| $$ \\  $$   | $$" << '\n';  
    cout << "   |__/   |__/  \\__/            |__/  |__/ \\______/  \\______/ |______/ \\______/    |__/  |__/  |__/|__/  \\__/   |__/" << '\n';  
                                                                                                                       
                                                                                                                       
                                                                                                                       

    cout << "\n";
    printCenter(0x1b, 45, "Main Menu");
    printCenter(0x1d, 45, "1. 기술 선택");
    printCenter(0x1d, 45, "0. 종료");
}

void moveMenu(){
    char menu;

    do{
        system("Color 0f");
        system("cls");
        while(_kbhit()) _getch();
        printCenter(0x1b, 45, "연습 가능 기술 목록");
        printCenter(0x0f, 45, "1: 벽력장");
        printCenter(0x0f, 45, "2: 초속풍신권");
        printCenter(0x0f, 45, "3: 발산 용포");
        printCenter(0x0f, 45, "4: 기상왼손 후 청뇌");
        printCenter(0x0f, 45, "5: 원애시드");
        printCenter(0x0f, 45, "6: 미스트트랩");
        printCenter(0x0f, 45, "0: 뒤로가기");
        menu = getch();
        if(menu == '1'){            
            Game game;
            game.parse("moves/벽력장.txt");
            game.play();
        }
        else if(menu == '2'){
            Game game;
            game.parse("moves/초속풍신권.txt");
            game.play();
        }
        else if(menu == '3'){
            Game game;
            game.parse("moves/발산용포.txt");
            game.play();
            
        }
        else if(menu == '4'){
            Game game;
            game.parse("moves/기상왼손 후 청뇌.txt");
            game.play();
        }
        else if(menu == '5'){
            Game game;
            game.parse("moves/원애시드.txt");
            game.play();
        }
        else if(menu == '6'){
            Game game;
            game.parse("moves/미스트트랩.txt");
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