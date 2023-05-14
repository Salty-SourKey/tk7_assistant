#include <iostream>
#include <windows.h>
#include <dirent.h>

#include "utils.h"

void setWindowPosition()
{
    // Get the handle to the console window
    HWND consoleWindow = GetConsoleWindow();

    // Get the dimensions of the monitor screen
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Get the dimensions of the console window
    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    int consoleWidth = consoleRect.right - consoleRect.left;
    int consoleHeight = consoleRect.bottom - consoleRect.top;

    // Calculate the position to center the console horizontally and position it at the bottom of the screen
    int consoleX = 0;
    int consoleY = screenHeight - 270;

    // Move the console window to the desired position
    SetWindowPos(consoleWindow, NULL, consoleX, consoleY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
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