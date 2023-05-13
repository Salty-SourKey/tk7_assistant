#ifndef GAME_H
#define GAME_H

#include <vector>

class Game
{
    public:
        Game();
        ~Game();
        void parse(std::string dataPath);
        void play();
        void printInfo();

    private:
        void drawGrid();
        void clearGrid();

        int frameUnit;                      // �Է� ��� �ֱ�
        int frameNum;                       // ��� ����
        std::string moveName;               // ��� �̸�
        std::vector<std::string> dirs;      // ���� �Է�
        std::vector<std::string> moves;     // Ű �Է�

};

#endif // GAME_H
