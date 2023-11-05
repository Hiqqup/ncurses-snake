//compile with this command:$ gcc thread-cur.c -lncurses -lpthread -o run

#include <ncurses.h>
#include <pthread.h>
#include <unistd.h> 
#include<stdlib.h>
#include <stdlib.h>
#include <time.h>


#define GRIDWIDTH 60
#define GRIDHEIGHT 30

#define LEFTKEY 68
#define RIGHTKEY 67
#define DOWNKEY 66
#define UPKEY 65

#define DELAY 100000


int** snake ;
int snakeLen = 1;
int* dir ;
int* apple;
int clearCounter = 0;

pthread_mutex_t mv_mutex;


void reallocApple(){

reallocAppleAgain:
	apple[0] = rand() % GRIDWIDTH;
	apple[1] = rand() % GRIDHEIGHT;
	for(int i  = 0 ; i< snakeLen; i++) {
		if(snake[i][0] == apple[0] &&snake[i][1] == apple[1] ){
			goto reallocAppleAgain;
		}
	}
}
void snakeGrow(){
	int * snakePart = malloc(2*sizeof(int));
	snakePart[0] = snake[snakeLen-1][0];
	snakePart[1] = snake[snakeLen-1][1];
	snakeLen++;
	snake = realloc(snake, snakeLen * sizeof(int*));
	snake[snakeLen-1] = snakePart;
	reallocApple();

}
void snakeFollow(){
	for(int i = snakeLen-1; i >= 1 ; i--){
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
	}
	
}
void gameOver(){
	mvprintw(GRIDHEIGHT/2, GRIDWIDTH/2-5, "GAME OVER");
	dir[0] = 0;
	dir[1] = 0;
}
void checkGameOver(){
	if(snake[0][0] < 0||snake[0][1] < 0 || snake[0][0]>GRIDWIDTH || snake[0][1] > GRIDHEIGHT){
		gameOver();
		return;
	}
	for(int i = 0; i < snakeLen; i++){
		for(int j = 0; j < snakeLen; j++){
			if(i != j && snake[i][0] == snake[j][0] &&snake[i][1] == snake[j][1]){
				gameOver();
				return;
			}

		}
		
	}
}
void *mvSnake(void* ptr) {
	while(1) {
		pthread_mutex_lock(&mv_mutex);
		mvprintw(snake[snakeLen-1][1], snake[snakeLen-1][0], " ");
		if((snake[0][1]-dir[1]) == apple[1] &&
		   (snake[0][0]+dir[0]) == apple[0]){
			snakeGrow();
		}
		snakeFollow();
		snake[0][0]+=dir[0];
		snake[0][1]-=dir[1];
		checkGameOver();
		pthread_mutex_unlock(&mv_mutex);
		usleep(DELAY);
	}
}

void drawBorders(){
	for(int i = 0; i < GRIDWIDTH+2; i++){
		mvprintw(GRIDHEIGHT+1, i, "#");
	}
	for(int i = 0; i < GRIDHEIGHT+2; i++){
		mvprintw(i , GRIDWIDTH+1, "#");
	}
}
void *draw(void* ptr) {
	initscr();
	noecho();
	timeout(1);
	curs_set(0);
	drawBorders();
	for (;;) {
		int ch = getch();
		if(ch == LEFTKEY 
				&& dir[0] != 1 && dir[1] !=0
				){
			dir[0] = -1;
			dir[1] = 0;
		}
		else if ( ch==RIGHTKEY
				&& dir[0] != -1 && dir[1] !=0
				){
			dir[0] = 1;
			dir[1] = 0;
		}
		else if ( ch==DOWNKEY
				&& dir[0] != 0 && dir[1] !=1
				){
			dir[0] = 0;
			dir[1] = -1;
		}
		else if( ch==UPKEY
				&& dir[0] != 0 && dir[1] !=-1
				){
			dir[0] = 0;
			dir[1] = 1;
		}


		clearCounter++;
		if(clearCounter == 1000) {
			clearCounter = 0;
			clear();
			drawBorders();
		}
		mvprintw(snake[0][1], snake[0][0], "0");
		mvprintw(apple[1], apple[0], "A");
		for(int i = 1; i < snakeLen; i++){
			mvprintw(snake[i][1], snake[i][0], "o");

		}
	}
}
void initSnake(){
	snake = malloc(sizeof(int*));
	dir = malloc(2*sizeof(int));
	apple = malloc(2*sizeof(int));

	int * snakeHead  =malloc(2*sizeof(int));
	snakeHead[0] = GRIDWIDTH/2;
	snakeHead[1] = GRIDHEIGHT/2;
	snake[0] = snakeHead;
	dir[0] = 0;
	dir[1] = 1;
	apple[0] = GRIDWIDTH/2;
	apple[1] = GRIDHEIGHT/3;
}

int main() {

	srand(time(NULL));
	initSnake();
	pthread_mutex_init(&mv_mutex, NULL);

	pthread_t mv_thread, draw_thread;
	pthread_create(&mv_thread, NULL, mvSnake, NULL);
	pthread_create(&draw_thread, NULL, draw, NULL);
	pthread_join(mv_thread, NULL);
	pthread_join(draw_thread, NULL);

	pthread_mutex_destroy(&mv_mutex);

	return 0;
}
