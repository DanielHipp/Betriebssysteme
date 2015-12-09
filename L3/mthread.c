#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>

#define randMax 10
#define randMin 1

extern const char *gitversion;

int verbose = 0;
int timeval = 0;
int randomMin = randMin;
int randomMax = randMax;

void *PrintHello(void *threadarg)
{
        clock_t secsNew = 0;
        clock_t secsOld = 0;

        if(timeval == 1){
            secsOld = clock();
        }
        int number = (intptr_t) threadarg;
        printf("Thread with Number %d says \"Hallo Welt\"\n", (number+1));

        long sleeptime = labs ((lrand48 () % (randomMax + 1 - randomMin)) + randomMin);
        sleep(sleeptime);

        /* say goodbye */ 
        printf("Thread %d is done after sleeping %ld[s]\n",(number+1), sleeptime); /* replace '0's with Thread Number and sleeping Time! */

        if(timeval == 1){
            secsNew = clock();
            long secs = secsNew - secsOld;
            printf("Needed %ld Microseconds for Working! (Without the Time of sleeping)\n", secs);
        }

        int status;
        pthread_exit(&status);

        return(NULL); /* Dummy to make -Wall happy ... */
}


void printHelper(){
    printf("\n>>>Helper<<< \n");
    printf("-v: \'verbose\', activates extra Output (prefered to use it as the first argument)\n");
    printf("-t Number: the amount of threads, the programm should create\n");
    printf("-r Number: lower Border of the random waittime of the threads\n");
    printf("-R Number: upper Border of the random waittime of the threads\n");
    printf("   (All Numbers must be positiv!)\n");
    printf("-c: shows the Microseconds needed for the different actions\n");
    printf("-j: going throught the programm without joining\n");
    printf("-h: activates this Helper\n");
    printf("Programm ends now\n\n");
    exit(0);
}

void checkBorder(){
    if(randomMin > randomMax){
        printf("Upper Border must be greater than the lower Border!\n");
        printf("Upper Border(-R): %d Lower Border(-r): %d\n", randomMax, randomMin);
        printHelper();
    } else {
        if(verbose == 1){
            printf("Border checked!\n");
        }
    }
}

int main(int argc, char *argv[])
{
        void* status;
        long t;
        char tmp;
        int check;
        int join = 0;
        clock_t secsOld = 0;

        long NumberOfThreads = 4;  /* Dummy Value, set it by parsing argument */

        /*read the arguments*/
        while((tmp = getopt (argc, argv, "t:r:R:vhcj")) != -1){
            switch (tmp){
                case 'h':
                    printf("Git Version: %s\n", gitversion);
                    printHelper();
                    break;
                case 'v':
                    verbose = 1;
                    break;
                case 'r':
                    randomMin = atoi(optarg);
                    checkBorder();
                    if(randomMin <= 0){
                        printf("\nFalse Value for the lower Random-Border!\n");
                        printHelper();
                    }
                    break;
                case 'R':
                    randomMax = atoi(optarg);
                    checkBorder();
                    if(randomMax <= 0){
                        printf("\nFalse Value for the upper Random-Border!\n");
                        printHelper();
                    }
                    break;
                case 't':
                    NumberOfThreads = atoi(optarg);
                    if(NumberOfThreads <= 0){
                      printf("\nFalse Value for the account of threads!\n");
                      printHelper();
                    }
                    break;
                case 'c':
                    timeval = 1;
                    if(verbose == 1){
                        printf("Programm shows the different timer\n");
                    }
                    break;
                case 'j':
                    join = 1;
                    if(verbose == 1){
                        printf("Programm runs without the joining!\n");
                    }
                    break;
            }
        }

        if(timeval == 1){
            secsOld = clock();
        }

        pthread_t threadArray[NumberOfThreads];
        long threatcounter = NumberOfThreads;
        long thread = 0;

        /*create all threads*/
        for (t = 0; t < NumberOfThreads; t++) {
            thread = t + 1;
            printf("Creating thread %ld\n", thread);

            check = pthread_create(&threadArray[t], NULL, PrintHello, (void *)(intptr_t)t);
            if(check == 0){
                threatcounter--;
                if(verbose == 1){
                    printf("Created Thread %ld successful.\n", thread);
                }
            } else {
                printf("To create thread %ld failed! Checknumber: %d\n", thread, check);
            }

        }

        if(verbose == 1){
            if(threatcounter == 0){
                printf("All Threads Created\n");
            } else {
                printf("%ld Thread(s) are missing!\n", threatcounter);
            }
        }

        if(timeval == 1){
            clock_t secsNew = clock();
            long secs = secsNew - secsOld;
            printf("Microseconds needed for creating of the stacks: %ld\n", secs);
            secsOld = secsNew;
        }

        /*if join allowed*/
        if(join == 0){
            threatcounter = NumberOfThreads;
            for (t = 0; t < NumberOfThreads; t++) {
                thread = t + 1;
                printf("Main joining with thread %ld\n", t);

                check = pthread_join(threadArray[t], &status);
                if(check == 0){
                    threatcounter--;
                    if(verbose == 1){
                    printf("Joined Thread %ld successful.\n", thread);
                    }
                } else {
                    printf("To join thread %ld failed! Checknumber: %d\n", thread, check);
                }

                printf("Completed joining with thread %ld status = %d\n", thread,
                       (int) status);
            }

            if(verbose == 1){
                if(threatcounter == 0){
                    printf("All Joins Succeed\n");
                } else {
                    printf("%ld Threads missing!\n", threatcounter);
                }
            }

            if(timeval == 1){
                clock_t secsNew = clock();
                long secs = secsNew - secsOld;
                printf("Microseconds needed for joining of the stacks: %ld\n", secs);
            }
        }

    return (0);
}
