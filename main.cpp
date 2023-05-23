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
        printCenter(0x0f, 45, "1: ������");
        printCenter(0x0f, 45, "2: �ʼ�ǳ�ű�");
        printCenter(0x0f, 45, "3: �߻� ����");
        printCenter(0x0f, 45, "4: ���޼� �� û��");
        printCenter(0x0f, 45, "5: ���ֽõ�");
        printCenter(0x0f, 45, "6: �̽�ƮƮ��");
        printCenter(0x0f, 45, "0: �ڷΰ���");
        menu = getch();
        if(menu == '1'){            
            Game game;
            game.parse("moves/������.txt");
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
        else if(menu == '4'){
            Game game;
            game.parse("moves/���޼� �� û��.txt");
            game.play();
        }
        else if(menu == '5'){
            Game game;
            game.parse("moves/���ֽõ�.txt");
            game.play();
        }
        else if(menu == '6'){
            Game game;
            game.parse("moves/�̽�ƮƮ��.txt");
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