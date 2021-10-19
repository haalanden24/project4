/*

Project 4 ~ Caleb Schwartz ~ Evan Haaland
10/16/2021

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	


#define MAX_STRING 80
#define MAX_RUNWAYS 8
#define INPUT_SENTINEL -1
FILE *errorCheck(char *fileName);

typedef struct rtype *runways;

struct rtype{
	int numRunways;
	int currentRunway;
	runways *next;
};


int main (int x, char *input[]){



if (input[1] == NULL) {
	printf("[ERROR] no input file on command line.");
	return 0;
	} 
	FILE *fileName = errorCheck(input[1]);	
	//printf("%s", input[1]);
	int  clockDuration = 0;
	runways r = malloc(sizeof(struct rtype));
	fscanf(fileName, "%d\n", &clockDuration);
	fscanf(fileName, "%d\n", &r->numRunways);
		
	
	printf("clockDuration: %d", clockDuration);
	printf("numRunways: %d\n", r->numRunways);
	
	
	return 0;
}

FILE *errorCheck(char *fileName){
	FILE *ptr = fopen(fileName, "r");
	if (errno) {
		printf("[ERROR] file '%s' not found.", fileName);
	}
		
	return ptr;
}


void input2(){
	int g;
	scanf("%d", &g);
	printf("%d", g);
}
