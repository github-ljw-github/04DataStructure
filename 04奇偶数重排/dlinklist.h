////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)
//
//  微信公众号: 秘籍酷
//  技术交流群: 260492823（QQ群）
//  GitHub链接: https://github.com/vincent040
//
//  描述: 普通双向循环链表（头文件）
//
////////////////////////////////////////////////

#ifndef __DLINKLIST_H
#define __DLINKLIST_H

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>


typedef struct node
{
	int data;

	struct node *prev;
	struct node *next;
}dlistnode, *dlinklist;


dlinklist init_list(void);
dlinklist new_node(int data);

bool is_empty(dlinklist head);
void list_add_tail(dlinklist new, dlinklist head);
void list_remove(dlinklist del);
void show(dlinklist head);

void rearrange(dlinklist head);

#endif
