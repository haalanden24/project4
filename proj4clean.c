/*
Project 4 ~ Caleb Schwartz ~ Evan Haaland
10/16/2021
C:\Users\caleb\Documents\GitHub\project4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <stdbool.h>


#define MAX_STRING 80
#define MAX_RUNWAYS 8
#define INPUT_SENTINEL -1
#define al 0
#define debug 0
//#define ECHO 0
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
bool isEmpty(runways*,int);
planes setEmpty (planes, int);
int amountBusy(runways*,int);
void decrementTime(runways*,int);
int timeIsUp(runways*, int);
void moveOffRunway(runways*, int , int );
void setRunwayData(runways*, int, planes, int);
void printRunwaysBusy(runways*, int);
void freeEverything(runways*, planes, int);

int main (int x, char *input[]){
printf("Project #4 - Caleb Schwartz & Evan Haaland");


if (input[1] == NULL) {
	printf("\n[ERROR] no input file on command line.\n");
	return 0;
	} 

	FILE *fileName = errorCheck(input[1]);	
	
	planes waiting = malloc(sizeof(struct ptype));

	int clockDuration = 0;
	int numRunways = 0;
	int selectedRunway = -1;
	int idTracker = -1;
	int timeCounter = 0;
	float numBusy = 0;
	
	int planesLanded = 0;
	int totalPeople = 0;
	float runwayUsage = 0;
	int planesDelayed = 0;
	int timeDelayed = 0;

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
	//waiting->id = 0;
	while (clockDuration != 0) {
		timeCounter++;
		#ifdef ECHO
		printf("\n**** time = %d ****", timeCounter);
		#endif
		if(waiting->status == 0) {
			fscanf(fileName, "%d ", &waiting->idealTime);
			if(waiting->idealTime != -1){
				idTracker++;
				waiting = moveInto(waiting, fileName);
				waiting->id = idTracker;
			}
		}
		
		if(timeCounter > waiting->idealTime) waiting->circled = timeCounter - waiting->idealTime;
		
		#ifdef ECHO
		if(waiting->status)printf("\n  -- waiting to land: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]", waiting->id, waiting->name, waiting->idealTime, waiting->timeRequired, waiting->people, waiting->circled);
		#endif
			
		if (waiting->status != 0) {
			if (waiting->idealTime <= timeCounter){
				
				for(int i = 0; i < numRunways; i++){
					if(!r[i].isBusy){
						setRunwayData(r, i, waiting, idTracker);
						
						r[i].timeLeft = waiting->timeRequired;
						r[i].isBusy = 1;
						#ifdef ECHO
						printf("\n  -- landing runway %d: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]", i+1, r[i].currentPlane->id, r[i].currentPlane->name, r[i].currentPlane->idealTime,r[i].currentPlane->timeRequired, r[i].currentPlane->people, r[i].currentPlane->circled);
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
				totalPeople += r[selectedRunway].currentPlane->people;
				moveOffRunway(r, selectedRunway, numRunways);
				if(r[selectedRunway].currentPlane->circled){
					 planesDelayed++;
					 timeDelayed += r[selectedRunway].currentPlane->circled;
				}
				
				planesLanded++;
			} 
			
		
	}
	printRunwaysBusy(r, numRunways);
	
	numBusy += amountBusy(r, numRunways);
	clockDuration--;
	
	}
	float numRunwaysFloat = (float) numRunways;
	runwayUsage = (numBusy/(numRunwaysFloat*timeCounter)*100);
	printf("\nSimulation length: %d", timeCounter);
	
	printf("\nPlanes landed: %d", planesLanded);
	printf("\nTotal passengers: %d", totalPeople);
	printf("\nTotal runways: %d", numRunways);
	printf("\nRunway usage: %.1f%%", runwayUsage);
	printf("\nPlanes delayed: %d", planesDelayed);
	printf("\nTotal time delayed: %d", timeDelayed);
	
	freeEverything(r, waiting, numRunways);
	return 0;
	}


FILE *errorCheck(char *fileName){
	FILE *ptr = fopen(fileName, "r");
		
		if (ptr == NULL) {
			printf("\n[ERROR] file '%s' not found.\n", fileName);
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

	//fscanf(fileName, "%d ", &room->idealTime);
	fscanf(fileName, "%s", room->name);
	fscanf(fileName, "%d", &room->people);
	fscanf(fileName, "%d\n", &room->timeRequired);
	room->status = 1;
	room->circled = 0;
	
return room;
}

void freeEverything(runways *r, planes waitingRoom, int numRunways) {
	for(int i = 0; i < numRunways; i++){
		free(r[i].currentPlane);
	}
	free(r);
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
sprintf(toEmpty->name, " ");
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
	printf("\n  -- moving off runway #%d: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]", index+1, r[index].currentPlane->id, r[index].currentPlane->name, r[index].currentPlane->idealTime,r[index].currentPlane->timeRequired, r[index].currentPlane->people, r[index].currentPlane->circled);
	#endif
	r[index].isBusy = 0;
	r[index].timeLeft = -1;
}

void setRunwayData(runways *r, int i, planes p,int idTracker){
	
	r[i].currentPlane->id = idTracker;
	sprintf(r[i].currentPlane->name, "%s", p->name);
	r[i].currentPlane->idealTime = p->idealTime;
	r[i].currentPlane->timeRequired = p->timeRequired;
	r[i].currentPlane->people = p->people;
	r[i].currentPlane->circled = p->circled;
	r[i].currentPlane->status = 1;
		
}

void printRunwaysBusy(runways *r, int numRunways){
	#ifdef ECHO
	int counter = amountBusy(r, numRunways);
	if (counter > 1) printf("\n  -- runways busy: ");
	else if (counter) printf("\n  -- runway busy: ");
	for(int i = 0; i < numRunways; i++){
		if (r[i].isBusy && i < counter-1) printf("#%d,", i+1);
		else if(r[i].isBusy){
			 printf("#%d", i+1);
			 printf(" of %d",numRunways);
		}
	}
	
	
	#endif
}

