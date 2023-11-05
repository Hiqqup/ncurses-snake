#include<stdlib.h>
#include<stdio.h>

int main(){
	int *arr = malloc(5*sizeof(int));
	arr[0] = 55;
	printf("%i", arr[0]);

	return 0;
}

