//---create a stack with the simple Type float and test the stack---//

#include "genstacklib.h"
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{

	float val = 0;
	genStack FloatStack;

	GenStackNew (&FloatStack, sizeof (float), NULL);
	printf ("New Floatstack created\n");

	printf ("Push 6 Values on the stack.\n");
	while (val != 3)
	{
		val += 0.5;
		GenStackPush (&FloatStack, &val);
		printf ("Value pushed: %f\n", val);
	}

	printf ("Pulled the 6 Values: \n");
	while (!GenStackEmpty (&FloatStack))
	{
		GenStackPop (&FloatStack, &val);
		printf ("%f\n", val);
	}

	GenStackDispose (&FloatStack);
	printf ("Stack disposed\n");


	GenStackNew (&FloatStack, sizeof (int), NULL);
	printf ("Second Integerstack created\n");

	for (val = 0; val < 2; val += 0.5)
	{
		GenStackPush (&FloatStack, &val);
		printf ("Value pushed: %f\n", val);
	}
	printf ("Pushed 5 Elements on the Stack\n");

	GenStackDispose (&FloatStack);
	printf ("Second Integerstack disposed\n");

	return 0;
}
