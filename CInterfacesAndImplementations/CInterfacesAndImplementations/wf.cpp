#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "table.h"
#include "atom.h"
#include "mem.h"

static int first(int c)
{
   return isalpha(c);
}

static int rest(int c)
{
	return isalpha(c) || c == '_';
}

static int getword(FILE* fp, char* buf, int size, int first(int c), int rest(int c))
{
	int i = 0;
	int c;
	
	assert(fp && buf && size > 1 && first && rest);
	
	c = getc(fp);
	for ( ; c != EOF; c = getc(fp))
	{
		if (first(c))
		{
			if(i < size - 1)
				buf[i++] = c;
				
			c = getc(fp);
			
			break;
		}
		
		for (; c!= EOF && rest(c); c = getc(fp))
		{
			if(i < size - 1)
				buf[i++] = c;
		}
		
		if (i < size)
		{
			buf[i] = 0;
		}
		else{
		   buf[size - 1] = 0;
		}
		
		if (c != EOF)
		{
			ungetc(c, fp);
		}
		
		return i > 0;
	}
}

static int compare(const void* x, const void* y)
{
	return strcmp(*(char**)x, *(char**)y);
}

static void wf(char* name, FILE* fp)
{
	Table_T table = Table_new(0, NULL, NULL);
	char    buf[128];
	
	while(getword(fp, buf, sizeof buf, first,rest))
	{
		const char *word;
		int i, *count;
		
		for (i = 0; buf[i] != '\0'; i++)
		{
			buf[i] = tolower(buf[i]);
		}
		
		word = Atom_string(buf);
		count= Table_get(table, word);
		
		if (count)
		{
		  (*count)++;
		}
		else{
			NEW(count);
			*count = 1;
			Table_put(table, word, count);
		}
	}
	
	if (name)
	{
	   printf("%s:\n",name);
	}
	
	{
		int i;
		void** array = Table_toArray(table, NULL);
		qsort(array, Table_length(table), 2*sizeof(*array),compare);
		
		for (i = 0; array[i]; i+=2)
		{
			printf("%d   %s\n",*(int*)array[i+1],(char*)array[i]);
		}
		
		FREE(array);
	}	

	

}