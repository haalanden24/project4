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
	if (al) printf("open data file\n");
	FILE *fileName = errorCheck(input[1]);	
	//printf("%s", input[1]);
	
	planes waiting = malloc(sizeof(struct ptype));
	// waiting->status = malloc(sizeof(int)); //the waiting area - we store planes in this one at a time.
	
	if (al) printf("initialize all variables\n");
	int  clockDuration = 0;
	int numRunways = 0;
	int selectedRunway = -1;
	int idTracker = 0;
	int idFlag = 0;
	int timeCounter = 0;
	
	if (al) printf("input simulation duration & number of runways\n");
	if (al) printf("set clock to initial value\n");
	fscanf(fileName, "%d\n", &clockDuration);                            //inputs clock duration 
	if (clockDuration == -1) return 0;                                   //checks if very first input is -1 only
	fscanf(fileName, "%d\n", &numRunways);                               //inputs number of runways
	runways *r = malloc(sizeof(struct rtype)*MAX_RUNWAYS);               //**CHANGE to numRunways?**//
	//r->currentPlane = malloc(sizeof(struct ptype));
	
	
	for(int i = 0; i < numRunways; i++){
	                                                 //mallocs memory for plane WITHIN a runway
		r[i].currentPlane = malloc(sizeof(struct ptype));
		r[i].timeLeft = -1;
		r[i].isBusy = 0;
	}


	//r->currentPlane-> = malloc(sizeof(struct ptype));
	//waiting = moveInto(waiting, fileName);
		
	
	if (debug)printf("clockDuration: %d\n", clockDuration); //move to print function
	if (debug)printf("numRunways: %d\n", numRunways); // move to print function
	
	//printf("landTime: %d  Name: %s People: %d   Landing: %d\n",waiting->landTime,waiting->name,waiting->people,waiting->timeSpent );
	//r = landing(r,waiting,numRunways);
	//printf("name of plane is %d\n" , isEmpty(r));
	//waiting=setEmpty(waiting);//set waiting room to zero (create a function for this)
		
	if (al) printf("set plane waiting area to empty\n");
	waiting = setEmpty(waiting, idTracker);
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	// ********START WHILE LOOP********
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	waiting->id = 0;
	while (clockDuration != 0) {
		idFlag = 0;
		timeCounter++;
		printf("\n\n****t = %d****\n\n", timeCounter);
		if (al) printf("while there's still time left (loops once per clock tick) do\n");
		if(waiting->status == 0) { //get this conditional working
			printf("first if\n");
			if (al) printf("	if there's input & the plane waiting area is empty then\n");
			if(debug)printf("\n	first if\n");
			waiting = moveInto(waiting, fileName);
			if(al) printf("		load next plane into waiting area\n");
			if(debug)printf("	moved plane into waiting room\n");
			idFlag = 1;
			waiting->id = idTracker;
			
			//printf("id number: %d, idealTime: %d  Name: %s People: %d   Landing: %d\n",waiting->id, waiting->idealTime,waiting->name,waiting->people,waiting->timeRequired );
			if(al)printf("	endif\n");			
						
                                          
			
		}
		if(timeCounter > waiting->idealTime) waiting->circled = timeCounter - waiting->idealTime;
		
						#ifdef ECHO
						printf("  -- waiting to land: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]\n", waiting->id, waiting->name, waiting->idealTime, waiting->timeRequired, waiting->people, waiting->circled);
						#endif
		if (waiting->status != 0) {
			if(al)printf("	if waiting area is not empty then\n");
			if(debug)printf("\n	else if\n");
			if (waiting->idealTime <= clockDuration){                    //if the waiting plane's time to land <= the time remaining 
				if (al) printf("		if plane waiting's arrival time <= clock then\n");
				for(int i = 0; i < numRunways; i++){
					if(debug)printf("							is the runway busy (0=no, 1=yes) at runway #%d :%d\n", i+1,r[i].isBusy);
					if(!r[i].isBusy){
						if(debug)printf("		is the runway busy (0=no, 1=yes) at runway #%d :%d\n", i,r[i].isBusy);
						if(debug)printf("		landing plane on runway\n");
						if(al)printf("			land a plane onto a runway\n");
						setRunwayData(r, i, waiting, idTracker);
						
						r[i].timeLeft = waiting->timeRequired;
						r[i].isBusy = 1;
						#ifdef ECHO
						printf("  -- landing runway %d: [#%d: %s,schedule:%d,needed-to-land:%d,#onboard:%d,circled:%d]\n", i+1, r[i].currentPlane->id, r[i].currentPlane->name, r[i].currentPlane->idealTime,r[i].currentPlane->timeRequired, r[i].currentPlane->people, r[i].currentPlane->circled);
						#endif
						if(al)printf("			set waiting area to empty\n");
						waiting = setEmpty(waiting, idTracker);
						//printf("							is the runway busy (0=no, 1=yes) at runway #%d :%d\n", i+1,r[i].isBusy);
						//printf("id number: %d, idealTime: %d  Name: %s People: %d   time required: %d\n", r[i].currentPlane->id,r[i].currentPlane->idealTime, r[i].currentPlane->name,  r[i].currentPlane->people, r[i].currentPlane->timeRequired);
						
						break;
					}
					//printf("		is the runway busy (0=yes, 1=no) at runway #%d :%d\n", i,r[i].currentPlane->status);
				}
				
				
				//set waiting room to zero (create a function for this)
				
				
				if(al)printf("		endif\n");	
				
				
			}
			
		
			if(al)printf("	endif\n");	
		}
	

		
		if(al)printf("	for all the runways that are busy do\n");   //All functions within this should check for busy status
	for(int i = 0; i < numRunways; i++){
				decrementTime(r, i);
				if(al)printf("		decrement time left for landing by one\n");
				
				selectedRunway = timeIsUp(r, i);
				//printf("\n\nDEBUG:       selectedRunway = %d\n\n", selectedRunway+1);
				
				if(selectedRunway >= 0){
					if(al)printf("		if time left for landing = 0 then\n");
					moveOffRunway(r, selectedRunway, numRunways);
					if(al)printf("			move the plane off of this runway\n");
					if(al)printf("		endif\n");
					if(al)printf("	endfor\n");
				}          //printf("							is the runway busy (0=no, 1=yes) at runway #0 :%d\n",r[0].isBusy);				
				
			
		
	}
	printRunwaysBusy(r, numRunways);
	if(idFlag)idTracker++;
	clockDuration--;
	
	}
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	// ********END WHILE LOOP********
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	if(al)printf("endwhile\n");
	if(al)printf("ouput stats\n");
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


	fscanf(fileName, "%d ", &room->idealTime);
	fscanf(fileName, "%s", room->name);
	fscanf(fileName, "%d", &room->people);
	fscanf(fileName, "%d\n", &room->timeRequired);
	room->status = 1;
	room->circled = 0;
	//read into file to find what needs to be added for the plane.
	//assign these values to what is in waiting room.
	

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

void decrementTime(runways *r, int i){
	            
			if (r[i].isBusy){ 
			--r[i].timeLeft;
			//printf("time left for runway #%d after decrement  = %d\n", i+1, r[i].timeLeft);
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
	
	// for(int i = 0; i < counter; i++){
		// if (i < counter-1) printf("#%d,", i+1);
		// else printf("#%d", i+1);
	// }
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
