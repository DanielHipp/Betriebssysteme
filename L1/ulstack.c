#include "ulstack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void
ULStackNew (ulstack * s)
{

	assert (s != NULL);

	s->elems = (unsigned long *) calloc (4, sizeof (unsigned long));
	s->logLength = 0;
	s->allocLength = 4;

}


void
ULStackDispose (ulstack * s)
{

	assert (s != NULL);

	free (s->elems);
	s->logLength = 0;
	s->allocLength = 0;
	s->elems = NULL;

}


void
ULStackPush (ulstack * s, unsigned long value)
{

	assert (s != NULL);


	//if the smemory of the stack full, the memory gets doubled
	if (s->allocLength == s->logLength)
	{
		assert (s->allocLength != 0);
		assert (s->logLength != 0);
		unsigned long *newStack =
			realloc (s->elems, s->allocLength * 2);
		if (newStack != NULL)
		{
			s->allocLength = s->allocLength * 2;
			memcpy (s->elems +
				(s->logLength * sizeof (unsigned long)),
				&value, sizeof (unsigned long));
			s->logLength++;
		}
	}
	else
	{
		memcpy (s->elems + (s->logLength * sizeof (unsigned long)),
			&value, sizeof (unsigned long));
		s->logLength++;
	}



}


unsigned long
ULStackPop (ulstack * s)
{

	assert (s != NULL);
	assert (s->logLength > 0);
	assert (s->elems != NULL);
	s->logLength -= 1;

	return *(s->elems + (s->logLength * sizeof (unsigned long)));

}


unsigned int
GetULStackNumberOfElements (ulstack * s)
{

	assert (s != NULL);

	return s->logLength;
}
