#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

volatile int something = 0;

void loops(int wait);
long testloop(int wait);

int main(int argc, char *argv[]){
	int seconds = 0;
	int milliseconds = 0;
	long timer = 0;
	int waitcounter = 0;

	//test the time given by argv
	if(argc == 1){
		printf("Correct Statement: ./work [Number of Seconds] [Number of Milliseconds] (-v [for extra output])\n");
		printf("The Programm ends, please insert the correct values next time!\n");
		exit(0);
	}
	if(argc == 2){
		seconds = strtol(argv[1], NULL, 10);
		timer = seconds * 1000;
		waitcounter = timer * 100;
		//printf("Programm will run for %d Seconds.\n", seconds);
		printf("%ld", timer);										//shorter version for the .sh - File

	} else if(argc == 3){
		seconds = strtol(argv[1], NULL, 10);
		milliseconds = strtol(argv[2], NULL, 10);
		timer = (seconds * 1000) + milliseconds;
		waitcounter = timer * 150;
		//printf("Programm will run for %d Seconds and %d Milliseconds.\n",seconds, milliseconds);
		printf("%ld ", timer);										//shorter version for the .sh - File
	}						
	long looptime = 0;
	/*test the loop-length*/
	looptime = testloop(waitcounter);

	long counter = timer / looptime;
	long timeWorked = counter * looptime;
	long difference = timer - timeWorked;
	
	while(counter != 0){
		loops(waitcounter);
		counter--;
	}
	if(difference >= 100){
		printf("Error! Programm runs to long! (%ld milliseconds)\n", difference);
	} else {
		//printf("execution time: %ld Milliseconds\n", timeWorked);
		printf(" %ld\n", timeWorked);								//shorter version for the .sh - File
	}

	return 0;
}

/*loop to execute the given time*/
void loops(int wait){
	for(int i = 0; i < wait; i++){
		something+=10;
		something-=10;
	}
}

/*testloop to get the time the loop needs*/
long testloop(int wait){
	clock_t timeOld = clock()/(CLOCKS_PER_SEC / 1000);
	for(int i = 0; i < wait; i++){
		something+=10;
		something-=10;
	}
	clock_t timeNew = clock()/(CLOCKS_PER_SEC / 1000);
	timeNew -= timeOld;
	if(timeNew == 0) timeNew = 1;
	return timeNew;
}
