#include <iostream>
#include <windows.h>
#include <dirent.h>

#include "utils.h"

void setWindowPosition(int x, int y)
{
    HWND console = GetConsoleWindow();
    SetWindowPos(console, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void setWindowSize(int width, int height)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1)};
    SetConsoleWindowInfo(console, TRUE, &rect);
}

void setCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printColor(int color, int x, int y, std::string text)
{
    setCursor(x, y);
    setColor(color);
    std::cout << text;
    setColor(7);
}

void printCenter(int color, int width, std::string text)
{
    int len = text.length();
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);
    printColor(color, (width-len)/2, SBInfo.dwCursorPosition.Y, text+"\n");
}