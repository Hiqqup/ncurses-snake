#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define LEFTKEY 68
#define RIGHTKEY 67
#define DOWNKEY 66
#define UPKEY 65
#define LENGTH 60
#define HEIGHT 30
void printField(){
	for(int j = 0; j < LENGTH+2; j++){
		printw("#");
	}
	printw("\n");
	for(int i = 0; i < HEIGHT; i++){
		printw("#");
		for(int j = 0; j < LENGTH; j++){
			printw(" ");
		}
		printw("#");
	printw("\n");
	}
	for(int j = 0; j < LENGTH+2; j++){
		printw("#");
	}
	printw("\n");
	
}
int getInput(int ch, int*dir){
		ch = getch();
		if(ch == LEFTKEY){
		}
		else if ( ch==RIGHTKEY){
		}
		else if ( ch==DOWNKEY){
		}
		else if( ch==UPKEY){
		}
}
void updateSnake(int* snake){
	mvaddch(snake[0], snake[1],'0');

}
int main()
{	
	initscr();			/* Start curses mode 		  */
	noecho();
	curs_set(0);
	printField();
	int ch;
	int* dir = malloc(2*sizeof(int));
	dir[0] = 1;
	dir[1] = 0;
	int* snake = malloc(2*sizeof(int));
	snake[0] = HEIGHT/2;
	snake[1] = LENGTH/2;
	while(1) {
		updateSnake(snake);
		snake[0] += dir[0];
		snake[1] += dir[1];
		move(HEIGHT+2,0);
		printw("%i", snake[0]);
	       	getInput(ch,dir);
		usleep(70000);
		
	}
	endwin();			/* End curses mode		  */

	return 0;
}
