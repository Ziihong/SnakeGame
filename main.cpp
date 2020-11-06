
#include "Nsnake.h"

int Maxheight, Maxwidth;
void PlayGame();
int IsReady();
int tryAgain();
void setScreen(float x, float y);
int keyInput();

int main (){
	if (IsReady() == 'Y') // wait for confirmation of the user
	do {
		{
			Nsnake NewSnake;
			NewSnake.PlayGame();
		}
	}
	while (tryAgain() == 'Y');
	return 0;
}

// print start menu
int IsReady(){
	setScreen(3, 2.5);
	printw("Do you want to play game? (Y/N)");
	return keyInput();
}

// print end of the game menu and ask user to play again
int tryAgain(){
	setScreen(2.5, 2.5);
	printw("Do you want to try again? (Y/N)");
	return keyInput();
}

// clear the screen and centre the cursor
void setScreen(float x, float y){
	clear(); // clear the screen if the game is played for the 2nd time
	initscr();
	noecho();
	getmaxyx(stdscr, Maxheight, Maxwidth);
	move((Maxheight/y), (Maxwidth/x));
}

// receive user confirmation
int keyInput(){
	int userAnswer = getch();
	refresh();
	endwin();
	clear();

	return userAnswer;
}

