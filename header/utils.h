#ifndef UTILS_H
#define UTILS_H

void setWindowPosition();
void setWindowSize(int width, int height);
void setCursor(int x, int y);
void setColor(int color);
void printColor(int color, int x, int y, std::string text);
void printCenter(int color, int x, std::string text);

#endif // UTILS_H