//---create a stack with the simple Type int and test the stack---//

#include "genstacklib.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	int val; 
	genStack IntegerStack;

	GenStackNew(&IntegerStack, sizeof(int), NULL); 
	printf("Integerstack created\n");

  	printf("Push 6 Values on the stack\n");
	for (val = 0; val < 6; val++){
  		GenStackPush(&IntegerStack, &val);
  		printf("Pushed Value: %d\n", val);
  	}

  	printf("Pulled the 6 Values: \n");
	while(!GenStackEmpty(&IntegerStack)){ 
 		GenStackPop(&IntegerStack, &val); 
 		printf("%d\n",val);
	}

	GenStackDispose(&IntegerStack); 
	printf("Stack disposed!\n");

	GenStackNew(&IntegerStack, sizeof(int), NULL);
	printf("Second Integerstack created\n");

	printf("Push 3 Elements on the Stack\n");
	for(val = 0; val <= 3; val++){
		GenStackPush(&IntegerStack, &val);
		printf("Pushed Values: %d\n", val);
	}

	GenStackDispose(&IntegerStack);
	printf("Second Integerstack disposed\n");
	
	return 0;
}
