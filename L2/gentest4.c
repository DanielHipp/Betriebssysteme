//---create a stack with the struct pet and test the stack---//
//---this time freefn() is needed, and the struct has two structs in it---//

#include "genstacklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct
{
	char *studium;
	int semester;
} stat;

typedef struct
{
	char *street;
	char *land;
} adress;

typedef struct
{
	char *name;
	stat *stat;
	adress *adress;
} student;

stat *
make_stat (char *studium, int semester)
{
	stat *st = malloc (sizeof (stat));
	assert (st != NULL);
	st->studium = studium;
	st->semester = semester;
	return st;
}

adress *
make_adress (char *street, char *land)
{
	adress *adr = malloc (sizeof (adress));
	assert (adr != NULL);
	adr->street = street;
	adr->land = land;
	return adr;
}

student *
make_student (char *name, char *studium, int semester, char *street,
	      char *land)
{
	student *stud = malloc (sizeof (student));
	assert (stud != NULL);
	stud->name = name;
	stud->stat = make_stat (studium, semester);
	stud->adress = make_adress (street, land);
	return stud;
}

void
freefn (void *element)
{
	assert (element != NULL);
	student *stud;
	stud = element;
	free (stud->name);
	free (stud->stat->studium);
	free (stud->adress->street);
	free (stud->adress->land);
	free (stud->stat);
	free (stud->adress);
}

int
main (int argc, char *argv[])
{

	student *anton =
		make_student ("Anton", "AIN", 2, "Buchauerstrasse 3",
			      "Deutschland");
	student *lincoln =
		make_student ("Lincoln", "WIN", 5, "Freeroad 5", "USA");
	student *lena =
		make_student ("Lena", "GIB", 3, "St. Anna - Road 4a",
			      "England");
	student *lin =
		make_student ("Lin", "KD", 4, "S334, Shanghai", "China");
	student *karkov =
		make_student ("Karkov", "AR", 6, "nazvaniya ulits",
			      "Russland");

	genStack studentStack;
	GenStackNew (&studentStack, sizeof (student), freefn);
	printf ("Created Studentstack\n");

	GenStackPush (&studentStack, anton);
	GenStackPush (&studentStack, lincoln);
	GenStackPush (&studentStack, lena);
	GenStackPush (&studentStack, lin);
	GenStackPush (&studentStack, karkov);
	printf ("Pushed 5 Elements on the Stack\n");

	printf ("This 5 Elements: \n");
	student *tmp = (student *) malloc (sizeof (student));

	while (!GenStackEmpty (&studentStack))
	{
		GenStackPop (&studentStack, tmp);
		printf ("Student: %s\nWohnhaft in: %s, %s\nStudiert: %s im %d Semester.\n", tmp->name, tmp->adress->street, tmp->adress->land, tmp->stat->studium, tmp->stat->semester);
	}

	GenStackDispose (&studentStack);
	printf ("Stack disposed!\n");

	GenStackNew (&studentStack, sizeof (student), freefn);
	printf ("Created Second Studentstack\n");

	GenStackPush (&studentStack, anton);
	GenStackPush (&studentStack, lincoln);
	GenStackPush (&studentStack, lena);
	GenStackPush (&studentStack, lin);
	GenStackPush (&studentStack, karkov);
	printf ("Pushed 3 Objects on the Stack!\n");

	GenStackDispose (&studentStack);
	printf ("Stack disposed!\n");


	free (tmp);
	free (anton);
	free (lincoln);
	free (lena);
	free (lin);
	free (karkov);

	return 0;
}
