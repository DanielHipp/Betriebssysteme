//---create a stack with the struct music and test the stack---//
//---this time freefn() is needed---//

#include "genstacklib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct
{
	char *musicname;
	int secondsToHear;
	char *artist;
} music;

music *
make (char *musicname, int secondsToHear, char *artist)
{
	music *mc = malloc (sizeof (music));
	assert (mc != NULL);
	mc->musicname = strdup (musicname);
	mc->secondsToHear = secondsToHear;
	mc->artist = strdup (artist);
	return mc;
}

void
freefn (void *element)
{
	music *mc;
	mc = element;
	free (mc->musicname);
	free (mc->artist);
}

int
main (int argc, char *argv[])
{

	music *whereAll = make ("Where All Things Go", 132, "Fladiux");
	music *toHot = make ("To Hot For Pants", 117, "MDK");
	music *monody = make ("Monody", 290, "TheFatRat");
	music *strength = make ("Strength", 225, "Define Light");
	music *onSun = make ("Lovers on the Sun", 172, "David Guetta");
	music *something = make ("Something", 123, "Ich");

	genStack musicStack;
	GenStackNew (&musicStack, sizeof (music), freefn);
	printf ("Created Musicstack!\n");

	GenStackPush (&musicStack, whereAll);
	GenStackPush (&musicStack, toHot);
	GenStackPush (&musicStack, monody);
	GenStackPush (&musicStack, strength);
	GenStackPush (&musicStack, onSun);
	GenStackPush (&musicStack, something);
	printf ("Pushed 5 Objects on the Musicstack\n");

	music *tmp = (music *) malloc (sizeof (music));
	printf ("Pop the 5 Objects\n");

	while (!GenStackEmpty (&musicStack))
	{
		GenStackPop (&musicStack, tmp);
		printf ("Musicname: %s, Seconds: %d, Artistname: %s\n",
			tmp->musicname, tmp->secondsToHear, tmp->artist);
	}
	GenStackDispose (&musicStack);
	printf ("Disposed Stack\n");

	GenStackNew (&musicStack, sizeof (music), freefn);
	printf ("Created Second Musicstack!\n");

	GenStackPush (&musicStack, whereAll);
	GenStackPush (&musicStack, toHot);
	GenStackPush (&musicStack, monody);
	GenStackPush (&musicStack, strength);
	GenStackPush (&musicStack, onSun);
	printf ("Pushed 5 Objects on the Musicstack\n");

	GenStackDispose (&musicStack);
	printf ("Second Musicstack disposed!\n");

	free (tmp);
	free (whereAll);
	free (toHot);
	free (monody);
	free (strength);
	free (onSun);

	return 0;
}
