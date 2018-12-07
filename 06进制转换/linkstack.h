#ifndef __LINKSTACK_H
#define __LINKSTACK_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// 单链表节点
typedef struct node
{
	union
	{
		int  oct;
		char hex;
	}data;
	struct node *next;
}stacknode;


// 链式栈管理结构体
typedef struct
{
	struct node *top; // 栈顶指针
	int size;         // 栈元素个数
}*linkstack;

linkstack init_stack(void);
bool is_empty(linkstack stack);
stacknode *pop(linkstack stack);
void push(stacknode *new, linkstack stack);

#endif
