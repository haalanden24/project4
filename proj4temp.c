/*
Project 4 ~ Caleb Schwartz ~ Evan Haaland
10/16/2021
C:\Users\caleb\Documents\GitHub\project4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <errno.h> // may be different for each operating system.


#define MAX_STRING 80
#define MAX_RUNWAYS 8
#define INPUT_SENTINEL -1
FILE *errorCheck(char *fileName);

struct ptype {
int id;
char name[MAX_STRING];
int landTime;
int toLand;
int people;
int timeSpent;

};

typedef struct ptype *planes; //we use planes as the name for variable.


typedef struct rtype *runways; //we will create an array of runways in main

struct rtype{
	int numRunways;
	int currentRunway;
	//runways *next; don't want a list
	planes currentPlane; //we store what plane is currently at that runway
	int isBusy;
	int timeLeft;
};



 
planes moveInto(planes,FILE*);
runways landing(runways,planes,int);

void printStats(int,int,int,int,float,int,int);
void freeWaiting(planes);

int main (int x, char *input[]){



if (input[1] == NULL) {
	printf("[ERROR] no input file on command line.\n");
	return 0;
	} 
	FILE *fileName = errorCheck(input[1]);	
	//printf("%s", input[1]);
	
	planes waiting = malloc(sizeof(struct ptype)); //the waiting area - we store planes in this one at a time.
	int  clockDuration = 0;
	int numRunways = 0;
	
	fscanf(fileName, "%d\n", &clockDuration);
	if (clockDuration == -1) return 0;
	fscanf(fileName, "%d\n", &numRunways);
	runways r = malloc(sizeof(struct rtype)*MAX_RUNWAYS);
	waiting = moveInto(waiting, fileName);
		
	
	printf("clockDuration: %d\n", clockDuration); //move to print function
	printf("numRunways: %d\n", numRunways); // move to print function
	/*
	while ( clockDuration != 0) {
		if(input[1] != NULL && waiting->name == NULL) {
			//I was thinking of checking if their is a name assigned to the waiting room to check if it is empty
		waiting = moveInto(waiting, fileName);
		}
		else if (waiting->name != NULL) {
			if (waiting->landTime <=clockDuration){
				//land plane on runway
				 freeWaiting(waiting); //set waiting room to zero (create a function for this)
			}
		}
		clockDuration--;
	}
	*/
	//waiting = moveInto(waiting, fileName); //assign waiting room to new value in waiting room
	//r[] = landing(r,waiting,numRunways);
	//printStats(clockDuration,numRunways);
	printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );
	return 0;
}

FILE *errorCheck(char *fileName){
	FILE *ptr = fopen(fileName, "r");
	if (errno) {
		printf("[ERROR] file '%s' not found.\n", fileName);
		exit(0);
	}
		
	return ptr;
}


void input2(){
	int g;
	scanf("%d", &g);
	printf("%d", g);
}

planes moveInto(planes room, FILE* fileName) { //almost works need to figure out how to copy string into


//fscanf(fileName, "%d %s %d %d\n ", &room->landTime,room->name,&room->people,&room->timeSpent);


fscanf(fileName, "%d ", &room->landTime);
fscanf(fileName, "%s", room->name);
fscanf(fileName, "%d", &room->people);
fscanf(fileName, "%d\n", &room->timeSpent);
//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting.landTime,waiting.name,waiting.people,waiting.timeSpent );
//read into file to find what needs to be added for the plane.
//assign these values to what is in waiting room.

return room;
}

runways landing(runways track,planes toLand,int amountRunways) {


	return track;
}

void freeWaiting(planes waitingRoom) {

	//free(waitingRoom);
}
/*
void printStats(int simLength, int numLanded, int passengers, int runways, float usage, int delayed, int timeDelay){
printf("Project 4 --Caleb Schwartz & Evan Haaland \n");
printf("Simulation length : &d \n" , simLength);
printf("Planes landed: %d\n" , numLanded);
printf("Total passengers: %d\n" , passengers);
printf("Runway usage: %.1f%%\n",usage);
printf("Planes delayed: %d\n", delayed);
printf("Total time delayed: %d \n", timeDelay);
}
*/