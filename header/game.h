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

        float frameUnit;                    // �Է� ��� �ֱ�
        std::string moveName;               // ��� �̸�
        std::string tips;                   // ��� ��
        int important_input_1;              // �߿� ��� 1
        int important_input_2;              // �߿� ��� 2
        std::string important_input_1_name; // �߿� ��� 1 �̸�
        std::string important_input_2_name; // �߿� ��� 2 �̸�
        int correctDiff;                    // ���� �Է�
        std::vector<std::string> dirs;      // ���� �Է�
        std::vector<std::string> moves;     // Ű �Է�

};

#endif // GAME_H
