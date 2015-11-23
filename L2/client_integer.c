#include "genstacklib.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

int val; 
genStack IntegerStack;

GenStackNew(&IntegerStack, sizeof(int), NULL); 
for (val = 0; val < 6; val++)
  GenStackPush(&IntegerStack, &val);

while(!GenStackEmpty(&IntegerStack)){ 
  GenStackPop(&IntegerStack, &val); 
  printf("Popped: %d\n",val);
}

GenStackDispose(&IntegerStack); }