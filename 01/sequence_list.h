#ifndef __SEQUENCE_LIST
#define __SEQUENCE_LIST


#ifndef SQLIST_NODE_DATATYPE
#define SQLIST_NODE_DATATYPE int
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct student
{
	char *name;
	int   age;
	float score;
};

typedef SQLIST_NODE_DATATYPE datatype;

typedef struct
{
	datatype *data;

	int size;
	int last;
}*sqlist;

sqlist init_list(int size);

bool is_empty(sqlist list);
bool is_full (sqlist list);

bool insert(datatype n, sqlist list);
bool delete(datatype n, sqlist list, bool (*comp)(datatype d1, datatype d2));

void traverse(sqlist list, void(*operation)(datatype));
void destroy(sqlist list);

void sort(sqlist, bool(*comp)(datatype d1, datatype d2));

#endif
