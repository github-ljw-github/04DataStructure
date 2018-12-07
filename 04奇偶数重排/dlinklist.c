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
//  描述: 普通双向循环链表
//
////////////////////////////////////////////////

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


dlinklist init_list(void)
{
	dlinklist head = calloc(1, sizeof(dlistnode));
	if(head != NULL)
	{
		head->prev = head;
		head->next = head;
	}
	return head;
}

bool is_empty(dlinklist head)
{
	return head->next == head;
}

dlinklist new_node(int data)
{
	dlinklist new = calloc(1, sizeof(dlistnode));
	if(new != NULL)
	{
		new->data = data;
		new->prev = new;
		new->next = new;
	}
	return new;
}

void list_add_tail(dlinklist new, dlinklist head)
{
	if(new == NULL)
		return;

	new->prev = head->prev;
	new->next = head;

	head->prev->next = new;
	head->prev = new;
}

// 将del指向的节点从链表中剔除
void list_remove(dlinklist del)
{
	if(del == NULL)
		return;

	del->prev->next = del->next;
	del->next->prev = del->prev;

	del->prev = NULL;
	del->next = NULL;
}

void list_move_tail(dlinklist p, dlinklist head)
{
	list_remove(p);
	list_add_tail(p, head);
}


// 奇偶数重排
void rearrange(dlinklist head)
{
	if(is_empty(head))
		return;

	// 从后往前遍历
	dlinklist odd = head->prev; // 负责指向奇数节点
	dlinklist p; // 负责往前遍历每一个节点
	for(p=head->prev; p!=head; p=p->prev)
	{
		// 1，偶数
		if(p->data % 2 == 0)
		{
			// 将偶数节点tmp丢到链表的末尾
			list_move_tail(p, head);

			// 回到上次的奇数节点处继续往前遍历
			p = odd;
		}

		// 2，奇数
		else
		{
			// 记下当前的位置
			odd = p;
		}
	}
}

void show(dlinklist head)
{
	if(is_empty(head))
		return;

	for(dlinklist tmp=head->next; tmp!=head; tmp=tmp->next)
	{
		printf("%d ", tmp->data);
	}
	printf("\n");
}
