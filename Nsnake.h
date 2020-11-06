#include <iostream>
#include <deque>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#ifndef Nsnake_H
#define Nsnake_H
#define MaxWidth 51
#define MaxHeight 25

#define COLOR_FRUIT 3
#define COLOR_POISON 4
#define COLOR_GATE 5

using namespace std;

struct CharPosition{
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

class Nsnake{
private:
	int del, growth_item, poison_item, gate, m_B, m_F, m_P, m_G, stage;
	int score_growth, score_poison, score_gate;
	bool checkTime;
	char direction, headchar, partchar, edgechar, fruitchar, poisonchar, gatechar;
    int map[4][MaxHeight-2][MaxWidth/2-1];
	// partchar is the character representing the snake's body
	// edgechar is the character representing the edge of the game window
	// fruitchar is the character representing the fruit
	// del stands for delay
	bool bEatsGrowth,bEatsPoison, gateTo, gatestate, changestage;
	CharPosition fruit, poison, gate1, gate2; // need to clarify this combination
	deque<CharPosition> snake; // represent the snake's body
	deque<CharPosition> gateArray; //************************
    deque<CharPosition> gameArray;
    deque<CharPosition> wallArray;

	void InitGameWindow();
	void DrawWindow();
	void DrawSnake();
	void PrintScore();
	void PrintMission(int arr[4][4]);
	void PositionGrowth();
	void PositionPoison();
	void PositionGate();
	void FullWall();
	bool FatalCollision();
	void MoveSnake();
	bool GetsGrowth(bool checkTime);
	bool GetsPoison(bool checkTime);
	bool GetGate();
	void MissionSuccess(int arr[4][4]);

public:
	Nsnake();
	~Nsnake(); // destructor for cleanup and memory deallocation
	void PlayGame();
};

#endif
