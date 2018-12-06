#ifndef __LINKLIST_H
#define __LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// 链表节点
typedef struct node
{
	int data;
	struct node *next;

}listnode, *linklist;

linklist init_list(void);
linklist new_node(int data);
bool is_empty(linklist list);

linklist list_add(linklist new, linklist list);
linklist list_add_tail(linklist new, linklist list);
linklist list_remove(linklist del);

void show(linklist list);
linklist count3(linklist list);
void destroy(linklist list);

#endif
