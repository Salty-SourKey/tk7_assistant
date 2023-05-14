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

        float frameUnit;                    // 입력 출력 주기
        std::string moveName;               // 기술 이름
        std::string tips;                   // 기술 팁
        std::vector<std::string> dirs;      // 방향 입력
        std::vector<std::string> moves;     // 키 입력

};

#endif // GAME_H
