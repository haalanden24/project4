/*
Project 4 ~ Caleb Schwartz ~ Evan Haaland
10/16/2021
C:\Users\caleb\Documents\GitHub\project4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <stdbool.h>
#include <errno.h> // may be different for each operating system.


#define MAX_STRING 80
#define MAX_RUNWAYS 8
#define INPUT_SENTINEL -1
FILE *errorCheck(char *fileName);

struct ptype {
int id;
//char *name;
char name[MAX_STRING];
int landTime;
int toLand;
int people;
int timeSpent;
int status;
};

typedef struct ptype *planes; //we use planes as the name for variable.


typedef struct rtype runways; //we will create an array of runways in main

struct rtype{
	int numRunways;
	int currentRunway;
	//runways *next; don't want a list
	planes currentPlane; //we store what plane is currently at that runway
	bool isNotBusy;
	int timeLeft;
};



 
planes moveInto(planes,FILE*);
runways* landing(runways*,planes,int);

void printStats(int,int,int,int,float,int,int);
void freeWaiting(planes);
bool isEmpty(runways*,int);
planes setEmpty (planes);
int amountBusy(runways*,int);
void decrementTimes(runways*,int);
int timeIsUp(runways*, int);

int main (int x, char *input[]){



if (input[1] == NULL) {
	printf("[ERROR] no input file on command line.\n");
	return 0;
	} 
	FILE *fileName = errorCheck(input[1]);	
	//printf("%s", input[1]);
	
	planes waiting = malloc(sizeof(struct ptype));
	// waiting->status = malloc(sizeof(int)); //the waiting area - we store planes in this one at a time.
	
	int  clockDuration = 0;
	int numRunways = 0;
	
	fscanf(fileName, "%d\n", &clockDuration);                            //inputs clock duration 
	if (clockDuration == -1) return 0;                                   //checks if very first input is -1 only
	fscanf(fileName, "%d\n", &numRunways);                               //inputs number of runways
	runways *r = malloc(sizeof(struct rtype)*MAX_RUNWAYS);               //**CHANGE to numRunways?**//
	//r->currentPlane = malloc(sizeof(struct ptype));
	
	
	for(int i = 0; i < numRunways; i++){
	                                                 //mallocs memory for plane WITHIN a runway
		r[i].currentPlane = malloc(sizeof(struct ptype));
	}


	//r->currentPlane-> = malloc(sizeof(struct ptype));
	//waiting = moveInto(waiting, fileName);
		
	
	printf("clockDuration: %d\n", clockDuration); //move to print function
	printf("numRunways: %d\n", numRunways); // move to print function
	
	//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );
	//r = landing(r,waiting,numRunways);
	//printf("name of plane is %d\n" , isEmpty(r));
	//waiting=setEmpty(waiting);//set waiting room to zero (create a function for this)
		

	waiting = setEmpty(waiting);
	int busy = 0;
	//
	//
	// ********START WHILE LOOP********
	//
	//
	while (clockDuration != 0) {
		printf("****t = %d****", clockDuration);
		if(waiting->status == 0) { //get this conditional working
			printf("\n	first if\n");
			//I was thinking of checking if their is a name assigned to the waiting room to check if it is empty
		waiting = moveInto(waiting, fileName);
		printf("	moved plane into waiting room\n");
		decrementTimes(r, numRunways);
		printf("	decremented time for runway\n");
		if (timeIsUp(r, numRunways));
			//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );

		}
		else if (waiting->status != 0) {
			printf("\n	else if\n");
			if (waiting->landTime <=clockDuration){
				
				for(int i = 0; i < numRunways; i++){
					if(!r[i].currentPlane->status){
						printf("		is the runway busy (0=no, 1=yes) at runway #%d :%d\n", i,r[i].currentPlane->status);
						printf("		landing plane on runway\n");
						r[i].currentPlane = waiting;
						r[i].currentPlane->status = 1;
						printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );
						decrementTimes(r, numRunways);
						printf("		decremented time for runway(s)\n");
						break;
					}
					//printf("		is the runway busy (0=yes, 1=no) at runway #%d :%d\n", i,r[i].currentPlane->status);
				}
				
				
				waiting = setEmpty(waiting);//set waiting room to zero (create a function for this)
				
				//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );

			}
			printf("		land time longer than sim time\n");
			decrementTimes(r, numRunways);
			printf("		decremented time for runway(s)\n");
		}
		 
		
		clockDuration--;
	}
	
	//waiting = moveInto(waiting, fileName); //assign waiting room to new value in waiting room
	//r[] = landing(r,waiting,numRunways);
	//printStats(clockDuration,numRunways);
	//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );
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
	room->status = 1;
	//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting.landTime,waiting.name,waiting.people,waiting.timeSpent );
	//read into file to find what needs to be added for the plane.
	//assign these values to what is in waiting room.
	//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",room->landTime,room->name,room->people,room->timeSpent );

return room;
}







// runways* landing(runways* track,planes toLand,int amountRunways) {

// for (int i = 0; i < amountRunways; i++){
	
	// //track[i].isNotBusy = isEmpty(track,i);

		

		
		
		// track[i].currentPlane->status = 1;
		// printf("		is the runway busy (0=yes, 1=no) at runway #%d :%d\n", i,track[i].currentPlane->status);
		
		// return track;
		// }
	// printf("		is the runway busy (0=yes, 1=no) at runway #%d :%d\n", i,track[i].currentPlane->status);
	// }
	
	// printf("		Runway 0 NOT busy: %d\n" ,track[0].isNotBusy);
	// printf("		Plane  0 check     %d\n\n" ,track[0].currentPlane->status);
	// printf("		Runway 1 NOT busy: %d\n" ,track[1].isNotBusy);
	// printf("		Plane  1 check     %d\n\n" ,track[1].currentPlane->status);
	// printf("		Runway 2 NOT busy: %d\n" ,track[2].isNotBusy);
	// printf("		Plane  2 check     %d\n\n" ,track[2].currentPlane->status);
	// return track;
// }

void freeWaiting(planes waitingRoom) {

	free(waitingRoom);
}

void decrementTimes(runways * r, int numRunways){
	for (int i = 0; i < numRunways; i++){
		if (r[i].currentPlane->status == 1){                  //if the runway has a plane, decrement the time remaining
			r[i].timeLeft--;                                   //to move it off of the runway
		}
	}
}

planes setEmpty (planes toEmpty) {

toEmpty->id = 0;
toEmpty->landTime = 0;
toEmpty->toLand = 0;
toEmpty->people = 0;
toEmpty->timeSpent = 0;
toEmpty->name[0] = '0';
toEmpty->status = 0;

return toEmpty;

}

int timeIsUp(runways* r, int numRunways){                           
	for (int i = 0; i < numRunways; i++){
		if (r[i].currentPlane->status && r[i].timeLeft == 0);
		return 1;
	}
	return 0;
}

// bool isEmpty(runways* current,int z) {
// //printf("DEBUG\n");

	// if (current[z].currentPlane->status == 0){
	// //printf("DEBUG\n");

		// return true; //true if empty - returns 1
	// }
	// else {

		// return false;
	// }

// }

int amountBusy(runways* listRunways,int totalRunways) {
	int counter = 0;
	for(int i = 0; i < totalRunways; i++) {
		if (listRunways[i].isNotBusy == 0) {
			counter++;
		}
	}

	return counter;
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