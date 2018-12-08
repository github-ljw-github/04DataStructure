#ifndef __QUEUE_H
#define __QUEUE_H

#include "tree.h"
#include "kernel_list.h"

// 队列节点
typedef struct node
{
	linktree data;
	struct list_head list;
}queue_node;


// 队列管理结构体
typedef struct
{
	queue_node *head; // 队头指针
	int size;
}*queue;

queue create_queue();
void enqueue(linktree data, queue q);
queue_node *dequeue(queue q);
bool is_empty(queue q);

#endif
