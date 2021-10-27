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
#define al 0
#define debug 0
#define ECHO 1
FILE *errorCheck(char *fileName);

struct ptype {
	int id;
	char name[MAX_STRING];
	int idealTime;
	int toLand;
	int people;
	int timeRequired;
	int circled;
	int status;
};

typedef struct ptype *planes; //we use planes as the name for variable.


typedef struct rtype runways; //we will create an array of runways in main

struct rtype{
	//int numRunways;
	//int currentRunway;
	//bool isNotBusy;
	
	planes currentPlane; //we store what plane is currently at that runway
	int isBusy;
	int timeLeft;
};



 
planes moveInto(planes,FILE*);
runways* landing(runways*,planes,int);

void printStats(int,int,int,int,float,int,int);
void freeWaiting(planes);
bool isEmpty(runways*,int);
planes setEmpty (planes, int);
int amountBusy(runways*,int);
void decrementTime(runways*,int);
int timeIsUp(runways*, int);
void moveOffRunway(runways*, int , int );
void setRunwayData(runways*, int, planes, int);
void printRunwaysBusy(runways*, int);

int main (int x, char *input[]){



if (input[1] == NULL) {
	printf("[ERROR] no input file on command line.\n");
	return 0;
	} 

	FILE *fileName = errorCheck(input[1]);	
	
	planes waiting = malloc(sizeof(struct ptype));

	int  clockDuration = 0;
	int numRunways = 0;
	int selectedRunway = -1;
	int idTracker = 0;
	int idFlag = 0;
	int timeCounter = 0;

	fscanf(fileName, "%d\n", &clockDuration);                            //inputs clock duration 
	if (clockDuration == -1) return 0;                                   //checks if very first input is -1 only
	fscanf(fileName, "%d\n", &numRunways);                               //inputs number of runways
	runways *r = malloc(sizeof(struct rtype)*MAX_RUNWAYS);               //**CHANGE to numRunways?**//
	
	
	for(int i = 0; i < numRunways; i++){
		r[i].currentPlane = malloc(sizeof(struct ptype));
		r[i].timeLeft = -1;
		r[i].isBusy = 0;
	}

	
	waiting = setEmpty(waiting, idTracker);
	waiting->id = 0;
	while (clockDuration != 0) {
		idFlag = 0;
		timeCounter++;
		printf("\n\n****t = %d****\n\n", timeCounter);
		if(waiting->status == 0) {
			printf("first if\n");
			waiting = moveInto(waiting, fileName);
			idFlag = 1;
			waiting->id = idTracker;	                                          
			
		}
		
		if(timeCounter > waiting->idealTime) waiting->circled = timeCounter - waiting->idealTime;
		
		#ifdef ECHO
		printf("  -- waiting to land: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]\n", waiting->id, waiting->name, waiting->idealTime, waiting->timeRequired, waiting->people, waiting->circled);
		#endif
			
		if (waiting->status != 0) {
			if (waiting->idealTime <= clockDuration){
				
				for(int i = 0; i < numRunways; i++){
					if(!r[i].isBusy){
						setRunwayData(r, i, waiting, idTracker);
						
						r[i].timeLeft = waiting->timeRequired;
						r[i].isBusy = 1;
						#ifdef ECHO
						printf("  -- landing runway %d: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]\n", i+1, r[i].currentPlane->id, r[i].currentPlane->name, r[i].currentPlane->idealTime,r[i].currentPlane->timeRequired, r[i].currentPlane->people, r[i].currentPlane->circled);
						#endif
						
						waiting = setEmpty(waiting, idTracker);
						break;
					}
					
				}							
						
			}		
			
		}
	

		

	for(int i = 0; i < numRunways; i++){
		decrementTime(r, i);						
		selectedRunway = timeIsUp(r, i);	
			if(selectedRunway >= 0){
				moveOffRunway(r, selectedRunway, numRunways);
				
			} 
			
		
	}
	printRunwaysBusy(r, numRunways);
	if(idFlag)idTracker++;
	clockDuration--;
	
	}
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


planes moveInto(planes room, FILE* fileName) {

	fscanf(fileName, "%d ", &room->idealTime);
	fscanf(fileName, "%s", room->name);
	fscanf(fileName, "%d", &room->people);
	fscanf(fileName, "%d\n", &room->timeRequired);
	room->status = 1;
	room->circled = 0;
	
return room;
}

void freeWaiting(planes waitingRoom) {

	free(waitingRoom);
}

void decrementTime(runways *r, int i){
	            
	if (r[i].isBusy){ 
	--r[i].timeLeft;
	}				
	
}



planes setEmpty (planes toEmpty, int idTracker) {

toEmpty->id = idTracker;
toEmpty->idealTime = 0;
toEmpty->toLand = 0;
toEmpty->people = 0;
toEmpty->timeRequired = 0;
toEmpty->name[0] = '0';
toEmpty->status = 0;
toEmpty->circled = 0;

return toEmpty;

}

int timeIsUp(runways* r, int i){                           
		if (r[i].timeLeft == 0 && r[i].isBusy ) return i;                      
	return -1;
}

int amountBusy(runways* r,int totalRunways) {
	int counter = 0;
	for(int i = 0; i < totalRunways; i++) {
		if (r[i].isBusy) {
			counter++;
		}
	}

	return counter;
}

void moveOffRunway(runways *r, int index, int numRunways){
	#ifdef ECHO
	printf("  -- moving off runway #%d: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]\n", index+1, r[index].currentPlane->id, r[index].currentPlane->name, r[index].currentPlane->idealTime,r[index].currentPlane->timeRequired, r[index].currentPlane->people, r[index].currentPlane->circled);
	#endif
	r[index].isBusy = 0;
	r[index].timeLeft = -1;
}

void setRunwayData(runways *r, int i, planes p,int idTracker){
	r[i].currentPlane->id = idTracker;
	int j = 0;
	while(p->name[j] != '\0'){
		r[i].currentPlane->name[j] = p->name[j];
		j++;
	}
	r[i].currentPlane->idealTime = p->idealTime;
	r[i].currentPlane->timeRequired = p->timeRequired;
	r[i].currentPlane->people = p->people;
	r[i].currentPlane->circled = p->circled;
	r[i].currentPlane->status = 1;
		
}

void printRunwaysBusy(runways *r, int numRunways){
	#ifdef ECHO
	int counter = amountBusy(r, numRunways);
	printf("  -- runways busy: ");
	for(int i = 0; i < numRunways; i++){
		if (r[i].isBusy && i < counter-1) printf("#%d,", i+1);
		else if(r[i].isBusy) printf("#%d", i+1);
	}
	
	printf(" of %d",numRunways);
	#endif
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
