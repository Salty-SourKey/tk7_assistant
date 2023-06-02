CXXFLAGS = -std=c++11

all: main

main: main.cpp header/utils.h src/utils.cpp header/game.h src/game.cpp
	$(CXX) $(CXXFLAGS) -Iheader main.cpp src/utils.cpp src/game.cpp -o TK_ASSISTANT

clean:
	rm -f main