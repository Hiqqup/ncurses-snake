#include<stdio.h>
#include <unistd.h>

#define LENGTH 40
#define HEIGHT 20
void printField(int snakeX, int snakeY){
	for(int j = 0; j < LENGTH+2; j++){
		printf("#");
	}
	printf("\n");
	for(int i = 0; i < HEIGHT; i++){
		printf("#");
		for(int j = 0; j < LENGTH; j++){
			if(i == snakeY && j == snakeX){
			printf("*");
			}else{
			printf(" ");
			}
		}
		printf("#");
	printf("\n");
	}
	for(int j = 0; j < LENGTH+2; j++){
		printf("#");
	}
	printf("\n");
	
}
char getInput(){

}
int main (){
	
	int i = 0;
	int snakeX = LENGTH/2;
	int snakeY = HEIGHT/2;
	while(1){
		printField(snakeX, snakeY);
		snakeY--;
		sleep(1);
	}
	return 0;
}
