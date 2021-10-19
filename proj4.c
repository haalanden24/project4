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
void inputData(char *fileName);
int main (int x, char *input[]){
if (input[1] == NULL) {
	printf("[ERROR] no input file on command line.");
	return 0;
	} 
	inputData(input[1]);	
	//printf("%s", input[1]);
		
	
	
	
	
	return 0;
}

void inputData(char *fileName){
	FILE *ptr = fopen(fileName, "r");
	if (errno) {
		printf("[ERROR] file '%s' not found.", fileName);
	}
	
	
	int  c = 0;
	while(!errno) {
	
	scanf("%d", &c);
	printf("%d", c);
      // c = fgetc(ptr);
	  // if (c == '-') break;
	  // // if (c == 45){
		  // // c = fgetc(ptr);
		  // // if (c == 49){
			  // // break;
		  // // }
	  // // }
      // printf("%c", c);
   }
}


void input2(){
	int g;
	scanf("%d", &g);
	printf("%d", g);
}
