
#include "Nsnake.h"
#include <unistd.h>
#include <string>
#define MaxWidth 51
#define MaxHeight 25

using namespace std;

CharPosition::CharPosition(int col, int row){
	x = col;
	y = row;
}

CharPosition::CharPosition(){
	x = 0;
	y = 0;
}

Nsnake::Nsnake(){
	// variables initialisation:
	headchar = 'H';
	partchar = 'o'; // character to represent the snake
	edgechar = (char)219; // full rectangle on the key table
	fruitchar = 'f';
	poisonchar = 'p';
    gatechar = '#';
	fruit.x = 0;
	fruit.y = 0;
	poison.x = 0;
	poison.y = 0;
	growth_item = 0;
	poison_item = 0;
	m_B = 0;
	m_F = 0;
	m_P = 0;
	m_G = 0;
	gate = 0;
	del = 150000;
	checkTime = true;
	bEatsGrowth = 0;
	bEatsPoison = 0;
	gateTo = 0;
	direction = 'l';
	gatestate = false;
    stage = 0;
	changestage = false;
    map[4][MaxHeight-2][MaxWidth/2-1];
	score_growth = 0;
	score_poison = 0;
	score_gate = 0;

	srand(time(NULL));

	start_color();
	use_default_colors();
	init_pair(COLOR_FRUIT, COLOR_GREEN,-1);
	init_pair(COLOR_POISON, COLOR_RED,-1);
	init_pair(COLOR_GATE, COLOR_BLUE,COLOR_BLUE);
	InitGameWindow();
	DrawWindow();
	DrawSnake();
	PositionGrowth();
	PositionPoison();
	//PositionGate();
	PrintScore();

	refresh();
}

Nsnake::~Nsnake(){
	nodelay(stdscr, false);
	getch();
	endwin();
}

// initialise the game window
void Nsnake::InitGameWindow(){
	initscr(); // initialise the screen
	nodelay(stdscr,TRUE);
	keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
	noecho(); // user input is not displayed on the screen
	curs_set(0); // cursor symbol is not not displayed on the screen (Linux)
	return;
}

// draw the game window
void Nsnake::DrawWindow(){
    int map[4][MaxHeight-2][MaxWidth/2-1] =
{{{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}},

 {{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}},

 {{2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {2,1,0,0,0,0,0,1,2,1,0,0,0,0,1,2,1,0,0,0,0,0,1,2},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {2,1,0,0,0,0,0,1,2,1,0,0,0,0,1,2,1,0,0,0,0,0,1,2},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2}},

 {{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}}};

    for (int i=0;i<MaxHeight-2;i++){
		for (int j=0;j<MaxWidth/2-1;j++){
			CharPosition p;
			if (map[stage][i][j] == 1 || map[stage][i][j] == 2){
				move(i,j);
				addch(edgechar);
				p.x = j, p.y = i;
				if (map[stage][i][j] == 1) gateArray.push_back(p);
			}
			else if(map[stage][i][j] == 0) {
				p.x = j; p.y = i;
				gameArray.push_back(p);
			}
		}
	}
	return;
}

// draw snake's body
void Nsnake::DrawSnake(){
	for (int i = 0; i < 5; i++) {
		snake.push_back(CharPosition(10+i, 9));
	}

	move(snake[0].y,snake[0].x);
	addch(headchar);
	for (int i = 1; i < snake.size(); i++) {
		move(snake[i].y, snake[i].x);
		addch(partchar);
	}
	return;
}

// print score at bottom of window
void Nsnake::PrintScore() {
	move(MaxHeight/2-7, MaxWidth/2+5);
	printw("---------------------------");
	move(MaxHeight/2-6, MaxWidth/2+5);
	printw("|Score Board              |");
	move(MaxHeight/2-5, MaxWidth/2+5);
	printw("| B:  %d                  |", snake.size());
	move(MaxHeight/2-4, MaxWidth/2+5);
	printw("| +:  %d                   |", growth_item);
	move(MaxHeight/2-3, MaxWidth/2+5);
	printw("| -:  %d                   |", poison_item);
	move(MaxHeight/2-2, MaxWidth/2+5);
	printw("| G:  %d                   |", gate);
	move(MaxHeight/2-1, MaxWidth/2+5);
	printw("---------------------------");
	return;
}

void Nsnake::PrintMission(int arr[4][4]){
	move(MaxHeight/2+1, MaxWidth/2+5);
	printw("---------------------------");
	move(MaxHeight/2+2, MaxWidth/2+5);
	printw("|Mission                   |");
	move(MaxHeight/2+3, MaxWidth/2+5);
	printw("| B:  %d   (%d)             |",arr[stage][0], m_B);
	move(MaxHeight/2+4, MaxWidth/2+5);
	printw("| +:  %d   (%d)             |",arr[stage][1], m_F);
	move(MaxHeight/2+5, MaxWidth/2+5);
	printw("| -:  %d   (%d)             |",arr[stage][2], m_P);
	move(MaxHeight/2+6, MaxWidth/2+5);
	printw("| G:  %d   (%d)             |",arr[stage][3], m_G);
	move(MaxHeight/2+7, MaxWidth/2+5);
	printw("---------------------------");
	return;
}

// position a new fruit in the game window
void Nsnake::PositionGrowth() {
	while(1) {
		int idx=random()%gameArray.size();
		fruit=gameArray[idx];

		for (int i = 0; i < snake.size(); i++) {
			if (snake[i].x == fruit.x && snake[i].y == fruit.y) {
				continue;
			}
		}

		if (fruit.x >= (MaxWidth/2)-2 || fruit.y >= MaxHeight-3) {
			continue; 
		}
		break;
	}
	attron(COLOR_PAIR(COLOR_FRUIT));
	move(fruit.y, fruit.x);
	addch(fruitchar);
	attroff(COLOR_PAIR(COLOR_FRUIT));
	refresh();
}

void Nsnake::PositionPoison() {
	while(1) {

		int idx=random()%gameArray.size();
		poison=gameArray[idx];

		// check that the fruit is not positioned on the snake
		for (int i = 0; i < snake.size(); i++) {
			if (snake[i].x == poison.x && snake[i].y == poison.y) {
				continue; // if true, ignore the following and go back to the beginning of function
			}
		}

		// check that the fruit is positioned within the game window
		if (poison.x >= (MaxWidth/2)-2 || poison.y >= MaxHeight-3) {
			continue; // if true, ignore the following and go back to the beginning of function
		}
		// if the coordinates are valid, add fruit in the window
		break;
	}
	attron(COLOR_PAIR(COLOR_POISON));
	move(poison.y, poison.x);
	addch(poisonchar);
	attroff(COLOR_PAIR(COLOR_POISON));
	refresh();
}

void Nsnake::PositionGate(){
    gate1.x=0;	gate1.y=0;
	gate2.x=0;	gate2.y=0; 

	while(1){
		int idx1=random()%gateArray.size();
		int idx2=random()%gateArray.size();

		if(idx1==idx2) continue;

		gate1=gateArray[idx1];
		gate2=gateArray[idx2];

		break;
	}

	attron(COLOR_PAIR(COLOR_GATE));
    move(gate1.y, gate1.x);
	addch(gatechar);
	attroff(COLOR_PAIR(COLOR_GATE));
	refresh();

	attron(COLOR_PAIR(COLOR_GATE));
	move(gate2.y, gate2.x);
    addch(gatechar);
	attroff(COLOR_PAIR(COLOR_GATE));
    refresh();
}

// set game over situations
bool Nsnake::FatalCollision() {
	// if the snake hits the edge of the window
	for(int i=0; i<MaxHeight; i++)

	if((snake[0].x == gate1.x && snake[0].y == gate1.y) || (snake[0].x == gate2.x && snake[0].y == gate2.y)){
        return false;
    }

	for(int i=0; i<gateArray.size(); i++){
		if(snake[0].x==gateArray[i].x && snake[0].y==gateArray[i].y){
			return true;
		}
	}

	// if the snake collides into himself
	for (int i = 2; i < snake.size(); i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			return true;
		}
	}
	return false;
}

// define behaviour when snake eats the fruit
bool Nsnake::GetsGrowth(bool checkTime) {
	if(!checkTime) {
		move(fruit.y, fruit.x);
		printw(" ");
		PositionGrowth();
	}

	if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
		PositionGrowth();
		growth_item += 1;
		PrintScore();

		return bEatsGrowth = true;
	}
	else{
		return bEatsGrowth = false;
	}
	return bEatsGrowth;
}

bool Nsnake::GetsPoison(bool checkTime) {
	if(!checkTime){
		move(poison.y, poison.x);
		printw(" ");
		PositionPoison();
	}

	if (snake[0].x == poison.x && snake[0].y == poison.y) {
		PositionPoison();
		poison_item += 1;
		PrintScore();
		return bEatsPoison = true;
	}
	else {
		return bEatsPoison = false;
	}
	return bEatsPoison;
}

bool Nsnake::GetGate(){
    deque <CharPosition>::iterator it;
    if(snake[0].x == gate1.x && snake[0].y == gate1.y){
        for(it=snake.begin(); it!=snake.end(); ++it){
            for(int i=0; i<snake.size(); i++){
                mvprintw(snake[i].y, snake[i].x, " ");
            }
			refresh();

			it->x = gate2.x; it->y = gate2.y;
			if(gate2.y == 0){ // 위(가장자리)
				direction = 'd';
			}
			else if(gate2.y == MaxHeight-3){ // 아래(가장자리)
				direction = 'u';
			}
			else if(gate2.x == 0){ // 좌(가장자리)
				direction = 'r';
			}
			else if(gate2.x == MaxWidth/2-2){ // 우(가장자리)
				direction = 'l';
			}
			// 중간벽
			else if(direction == 'u'){
				if(map[stage][gate2.y-1][gate2.x] != 0){
					if(map[stage][gate2.y][gate2.x+1] != 0){
						if(map[stage][gate2.y+1][gate2.x] != 0){
							direction = 'l';
						}
						else direction = 'd';
					}
					else direction = 'r';
				}
				else direction = 'u';
			}
			else if(direction == 'r'){
				if(map[stage][gate2.y][gate2.x+1] != 0) {
					if(map[stage][gate2.y+1][gate2.x] != 0){
						if(map[stage][gate2.y][gate2.x-1] != 0){
							direction = 'u';
						}
						else direction = 'l';
					}
					else direction = 'd';
				}
				else direction = 'r';
			}
			else if(direction == 'd'){
				if(map[stage][gate2.y+1][gate2.x] != 0) {
					if(map[stage][gate2.y][gate2.x-1] != 0){
						if(map[stage][gate2.y-1][gate2.x] != 0) {
							direction = 'r';
						}
						else direction = 'u';
					} 
					else direction = 'l';
				}
				else direction = 'd';
			}
			else if(direction == 'l'){
				if(map[stage][gate2.y][gate2.x-1] != 0) {
					if(map[stage][gate2.y-1][gate2.x] != 0){
						if(map[stage][gate2.y][gate2.x+1] != 0){
							direction = 'd';
						}
						else direction = 'r';
					}
					else direction = 'u';
				}
				else direction = 'l';
			}
            mvprintw(it->y, it->x, "o", snake);
            refresh();
        }       
		gate+=1;
		PositionGate();
        return gateTo = true;
    }
    else if(snake[0].x == gate2.x && snake[0].y == gate2.y){
        for(it=snake.begin(); it!=snake.end(); ++it){
            for(int i=0; i<snake.size(); i++){
                mvprintw(snake[i].y, snake[i].x, " ");
            }
			refresh();

            it->x = gate1.x; it->y = gate1.y;
			if(gate1.y == 0){ // 위
				direction = 'd';
			}
			else if(gate1.y == MaxHeight-3){ // 아래
				direction = 'u';
			}
			else if(gate1.x == 0){ // 좌
				direction = 'r';
			}
			else if(gate1.x == MaxWidth/2-2){ // 우
				direction = 'l';
			}
			// 중간벽
			else if(direction == 'u'){
				if(map[stage][gate1.y-1][gate1.x] != 0){
					if(map[stage][gate1.y][gate1.x+1] != 0){
						if(map[stage][gate1.y+1][gate1.x] != 0){
							direction = 'l';
						}
						else direction = 'd';
					}
					else direction = 'r';
				}
				else direction = 'u';
			}
			else if(direction == 'r'){
				if(map[stage][gate1.y][gate1.x+1] != 0) {
					if(map[stage][gate1.y+1][gate1.x] != 0){
						if(map[stage][gate1.y][gate1.x-1] != 0){
							direction = 'u';
						}
						else direction = 'l';
					}
					else direction = 'd';
				}
				else direction = 'r';
			}
			else if(direction == 'd'){
				if(map[stage][gate1.y+1][gate1.x] != 0) {
					if(map[stage][gate1.y][gate1.x-1] != 0){
						if(map[stage][gate1.y-1][gate1.x] != 0) {
							direction = 'r';
						}
						else direction = 'u';
					} 
					else direction = 'l';
				}
				else direction = 'd';
			}
			else if(direction == 'l'){
				if(map[stage][gate1.y][gate1.x-1] != 0) {
					if(map[stage][gate1.y-1][gate1.x] != 0){
						if(map[stage][gate1.y][gate1.x+1] != 0){
							direction = 'd';
						}
						else direction = 'r';
					}
					else direction = 'u';
				}
				else direction = 'l';
			}
            mvprintw(it->y, it->x, "o", snake);
            refresh();
        }
		gate+=1;
		PositionGate();
        return gateTo = true;
    }
	else{
		return gateTo = false;
	}
	return gateTo;
}

void Nsnake::FullWall(){
	for(int i=0; i<gateArray.size(); i++){
		if(!(gateArray[i].x == gate1.x && gateArray[i].y == gate1.y) && !(gateArray[i].x == gate2.x && gateArray[i].y == gate2.y)){
			move(gateArray[i].y, gateArray[i].x);
			addch(edgechar);
		}
		refresh();
	}
}

void Nsnake::MissionSuccess(int arr[4][4]){
	if(snake.size() >= arr[stage][0]) m_B = 1;
	if(growth_item >= arr[stage][1]) m_F = 1;
	if(poison_item >= arr[stage][2]) m_P = 1;
	if(gate >= arr[stage][3]) m_G = 1;
	
	if (m_B+m_F+m_P+m_G == 4) {
		stage+=1;
		changestage = true;
		clear();
		move((MaxHeight-2)/2,(MaxWidth-5)/2+5);
		printw("stage %d",stage+1);
		refresh();
	}
	PrintMission(arr);
	refresh();
}

// define snake's movements
void Nsnake::MoveSnake() {
	int KeyPressed = getch();
	switch(KeyPressed) {
		case KEY_LEFT:
			direction = 'l';
			break;
		case KEY_RIGHT:
			direction = 'r';
			break;
		case KEY_UP:
			direction = 'u';
			break;
		case KEY_DOWN:
			direction = 'd';
			break;
		case KEY_BACKSPACE:
			direction = 'q'; // key to quit the game
			break;
	}

	// the snake doesn't eat fruit, remains same size
	if (!bEatsGrowth) {
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // moves at the end of the tail
		printw(" "); // add empty ch to remove last character
		refresh();
		snake.pop_back(); // removes the last element in the vector, reducing the container size by one
	}
	if (bEatsPoison) {
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // moves at the end of the tail
		printw(" "); // add empty ch to remove last character
		refresh();
		snake.pop_back(); // removes the last element in the vector, reducing the container size by one
	}

	// the snake moves and we add an extra character at the beginning of the vector
	// add a head and initialise new coordinates for CharPosition according to the direction input
	if (direction == 'l') snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y));
	else if (direction == 'r') snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y));
	else if (direction == 'u') snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1));
	else if (direction == 'd') snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1));

	// move to the new CharPosition coordinates
	move(snake[0].y, snake[0].x);
	addch(headchar); // add a new head
    move(snake[1].y, snake[1].x);
    addch(partchar);
	refresh();

	return;
}

void Nsnake::PlayGame() {
	int seconds = 49;
	int mission[4][4] = {{7,2,0,0},{8,2,0,0},{9,2,0,0},{10,2,0,0}};
	initscr();
    while(stage < 4) {
		mvprintw(MaxHeight/2-9, MaxWidth/2+5, "Timer | %i", seconds/10);
		mvprintw(MaxHeight/2-10,MaxWidth/2+5, "stage | %d", stage+1);
		refresh();
		seconds--;
		napms(100);
		if(seconds == 0){
			checkTime = false;
			GetsGrowth(checkTime);
			GetsPoison(checkTime);
			seconds = 49;
		}
		else{
			GetsGrowth(true);
			GetsPoison(true);
		}
		FullWall();
		GetGate();
		if (snake.size() >=6 && gatestate == false){
			PositionGate();
			gatestate = true;
		}
		MissionSuccess(mission);
		PrintScore();
        MoveSnake();

		if (FatalCollision() || snake.size() < 3) {
            break;
        }

		if (changestage){
			clear();
			score_growth += growth_item;
			score_poison += poison_item;
			score_gate += gate;
			gateArray.clear();
    		gameArray.clear();
   		 	wallArray.clear();
			growth_item = 0;
			poison_item = 0;
			m_B = 0;
			m_F = 0;
			m_P = 0;
			m_G = 0;
			gate = 0;
			del += stage*10000;
			checkTime = true;
			bEatsGrowth = 0;
			bEatsPoison = 0;
			gateTo = 0;
			direction = 'l';
			gatestate = false;
			changestage = false;
			DrawWindow();
			//DrawSnake(); //snake가 두개 생김
			snake[0].x = 10;
			snake[0].y = 10;
			PositionGrowth();
			PositionPoison();
			PlayGame();
		}
        if (direction=='q') { //exit
        	break;
        }
        usleep(del); // delay
    }
	clear();
	move((MaxHeight-2)/2-6,(MaxWidth-5)/2);
	if (stage<4) printw("Game Over");
	else printw("Congratulation~!~! Game Clear");
	mvprintw((MaxHeight-2)/2-5,(MaxWidth-5)/2,"<<Your Total Score>>");
	mvprintw((MaxHeight-2)/2-4,(MaxWidth-5)/2,"Snake   |    %d",snake.size());
	mvprintw((MaxHeight-2)/2-3,(MaxWidth-5)/2,"Growth  |    %d",score_growth);
	mvprintw((MaxHeight-2)/2-2,(MaxWidth-5)/2,"Poison  |    %d",score_poison);
	mvprintw((MaxHeight-2)/2-1,(MaxWidth-5)/2,"Gate    |    %d",score_gate);
	mvprintw((MaxHeight-2)/2+1,(MaxWidth-5)/2,"C++ Programming_Project_Team 1");
	mvprintw((MaxHeight-2)/2+2,(MaxWidth-5)/2,"with");
	mvprintw((MaxHeight-2)/2+3,(MaxWidth-5)/2,"Kim Ji-hong");
	mvprintw((MaxHeight-2)/2+4,(MaxWidth-5)/2,"Baek Yeon-sun");
	mvprintw((MaxHeight-2)/2+5,(MaxWidth-5)/2,"Choi Hye-won");
}
