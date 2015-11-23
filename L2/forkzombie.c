#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	int input;
	pid_t pid = fork();

	if(pid == (-1)){
		perror("fork failed!");
		return -1;

	} else if(pid == 0){
		/*Child*/
		printf("Created Childprocess\n");
		printf("Child in Zombiemode\n");
		exit(0);

	} else if(pid > 0){
		/*Parent*/
		system("ps");

		fflush(stdin);

		printf("Press a number to end\n");
		while(!scanf("%d", &input)){
			clearerr (stdin);
            while (getc (stdin) != '\n');
		}

	}

	return 0;
}

