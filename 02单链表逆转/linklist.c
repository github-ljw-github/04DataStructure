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
//  描述: 单向链表的实现
//
////////////////////////////////////////////////

#include "linklist.h"

// 初始化一条带头结点的空单向链表
linklist init_list(void)
{
	linklist list = calloc(1, sizeof(listnode));
	if(list != NULL)
	{
		list->next = NULL;
	}

	return list;
}

// 判断链表是否为空
bool is_empty(linklist list)
{
	return list->next == NULL;
}

// 新建一个新节点
linklist new_node(int data)
{
	linklist new = calloc(1, sizeof(listnode));
	if(new != NULL)
	{
		new->data = data;	
		new->next = NULL;
	}

	return new;
}

// 将新节点 new 插入链表的开头
void list_add(linklist new, linklist list)
{
	if(new == NULL)
		return;

	new->next  = list->next;
	list->next = new;
}

// 将新节点 new 插入链表的末尾
void list_add_tail(linklist new, linklist list)
{
	linklist tail;
	for(tail=list; tail->next!=NULL; tail=tail->next);

	tail->next = new;
}

// 试图删除指定的节点
// 成功: 返回被剔除的节点的指针
// 失败: 返回NULL
linklist list_remove(int data, linklist list)
{
	if(is_empty(list))
		return NULL;

	linklist pre, del;
	pre = list;      // pre指向要删除的节点的前一个节点
	del = pre->next; // del指向要删除的节点

	while(del != NULL)
	{
		if(del->data == data)
			break;

		pre = pre->next;
		del = del->next;
	}

	if(del == NULL)
		return NULL;

	pre->next = del->next;
	del->next = NULL;
	
	return del;
}

// 销毁
void destroy(linklist list)
{
	linklist tmp;
	for(tmp=list; tmp->next!=NULL; tmp=list)
	{
		list = list->next;
		free(tmp);
	}
	free(tmp);
}


// 遍历链表
void show(linklist list)
{
	for(linklist tmp=list->next; tmp!=NULL; tmp=tmp->next)
	{
		printf("%d\t", tmp->data);
	}
	printf("\n");
}


// 翻转链表
void reverse(linklist list)
{
	linklist tmp = list->next; // tmp指向待翻转链表首节点
	list->next = NULL;

	linklist p = tmp;
	while(tmp != NULL)
	{
		p = tmp->next;

		tmp->next = list->next;
		list->next = tmp;

		tmp = p;
	}
}
