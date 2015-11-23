#include "ulstack.h"
#include <stdio.h>
#include <stdlib.h>

//check if the input is one number and nothing else
int falseNumber (int check);

int
main ()
{
	ulstack *stack = NULL;
	stack = (ulstack *) malloc (sizeof (ulstack));

	//circle for the menu
	while (0 == 0)
	{

		printf ("\nEnter your choice:\n");
		printf ("1) Create Stack\n");
		printf ("2) Push Value\n");
		printf ("3) Pop Value\n");
		printf ("4) Print Number of Elements on Stack\n");
		printf ("5) Remove Stack\n");
		printf ("6) Exit\n");
		printf (">> ");

		int input, check;
		check = scanf ("%d", &input);

		if (falseNumber (check) == 1)
		{
			continue;
		}

		getchar ();
		if (check == 1)
		{

			switch (input)
			{
			case 1:
				if (stack->elems != NULL)
				{
					printf ("You have already a stack, please dispose the first before you make another!\n");
				}
				else
				{
					ULStackNew (stack);
					printf ("Stack created\n\n");
				}
				break;

			case 2:
				if (stack->elems == NULL)
				{
					printf ("Please create a new stack first!\n");
				}
				else
				{
					printf ("Enter value: ");
					unsigned long value;
					check = scanf ("%lu", &value);
					if (falseNumber (check) == 1)
					{
						continue;
					}
					ULStackPush (stack, value);
					printf ("Value pushed.\n");
				}
				break;

			case 3:
				if (stack->elems == NULL)
				{
					printf ("Please create a new stack first!\n");
				}
				else if (stack->logLength == 0)
				{
					printf ("Please push first min. one element!\n");
				}
				else
				{
					unsigned long value =	ULStackPop (stack);
					printf ("Pop from Stack: %lu\n", value);
				}
				break;

			case 4:
				if (stack->elems == NULL)
				{
					printf ("Please create a stack first!\n");
				}
				else
				{
					printf ("Elements from Stack: %d\n",
						stack->logLength);
				}
				break;

			case 5:
				if (stack->elems == NULL)
				{
					printf ("Please create a stack first!\n");
				}
				else
				{
					ULStackDispose (stack);
					printf ("Stack disposed!\n");
				}
				break;

			case 6:
				if (stack->elems != NULL)
				{
					printf ("Please dispose the stack first\n");
				}
				else
				{
					exit (0);
				}
				break;

			default:
				printf ("False Number, please try again!");
			}

		}

	}
	return 0;
}

//The Method to check if the input is on Number
int
falseNumber (int check)
{
	char fail;

	if (check != 1)
	{
		printf ("Please dont enter a char or more than one number!\n");

		while ((fail = getchar ()) != '\n' && fail != EOF);
		return 1;
	}
	return 0;
}
