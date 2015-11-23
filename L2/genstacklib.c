#include "genstacklib.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>


#define GenStackInitialAllocationSize 4
#define DoubleStack 2

void
GenStackNew (genStack * s, int elemSize, void(*freefn)(void *))
{

	assert (s != NULL);
	assert (elemSize > 0);

	s->freefn = freefn;
	s->logLength = 0;
	s->allocLength = GenStackInitialAllocationSize;
	s->elemSize = elemSize;
	s->elems = (size_t*) malloc (s->allocLength * s->elemSize);
	assert(s->elems != NULL);


}


void
GenStackDispose (genStack * s)
{

	assert (s != NULL);

	if(s->freefn != NULL){
		while(!GenStackEmpty){
			s->logLength--;
			void* source;
			source = (size_t *) s->elems + (s->logLength * s->elemSize);
			s->freefn(source);
		}
	}
	s->allocLength = 0;
	s->elems = NULL;

	free (s->elems);

}


void
GenStackPush (genStack * s, const void* elemAddr)
{
	assert (s != NULL);
	assert (elemAddr != NULL);

	void * destination;

	//if the memory of the stack full, the memory gets doubled
	if (s->allocLength == s->logLength)
	{
		assert (s->allocLength != 0);
		assert (s->logLength != 0);
		size_t *newStack =
			realloc (s->elems, s->allocLength * DoubleStack);
		if (newStack != NULL)
		{
			s->allocLength = s->allocLength * DoubleStack;
			destination = (size_t*) s->elems + (s->logLength * s->elemSize);
			memcpy (destination, elemAddr, s->elemSize);
			s->logLength++;
		}
	}
	else
	{
		destination = (size_t*) s->elems + (s->logLength * s->elemSize);
		memcpy (destination, elemAddr, s->elemSize);
		s->logLength++;
	}



}


void
GenStackPop (genStack * s,void * elemAddr)
{

	assert (s != NULL);
	assert (s->logLength > 0);
	assert (s->elems != NULL);
	s->logLength--;
	void *start;
	start  = (size_t*) s->elems + (s->logLength * s->elemSize);

	memcpy(elemAddr, start, s->elemSize);

}


bool GenStackEmpty(const genStack *s){
	assert(s->elems != NULL);

	if(s->logLength > 0){
		return false;
	}
	return true;
}
