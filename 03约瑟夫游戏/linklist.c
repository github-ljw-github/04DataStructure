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
//  描述: 单向循环链表
//
////////////////////////////////////////////////

#include "linklist.h"

// 初始化一条不带头结点的空单向循环链表
linklist init_list(void)
{
	return NULL;
}

// 判断链表是否为空
bool is_empty(linklist list)
{
	return list == NULL;
}

// 新建一个新节点
linklist new_node(int data)
{
	linklist new = calloc(1, sizeof(listnode));
	if(new != NULL)
	{
		new->data = data;	
		new->next = new;
	}

	return new;
}

// 将新节点 new 插入 list 的前面（链表的末尾）
linklist list_add_tail(linklist new, linklist list)
{
	if(new == NULL)
		return list;

	if(!is_empty(list))
	{
		linklist tail;
		for(tail=list; tail->next!=list; tail=tail->next);

		new->next  = list;
		tail->next = new;
		return list;
	}

	return new;
}

// 将新节点 new 插入 list 的后面
linklist list_add(linklist new, linklist list)
{
	if(new == NULL)
		return list;

	if(is_empty(list))
		return new;

	new->next  = list->next;
	list->next = new;
	return list;
}

// 将指定的节点剔除出链表
linklist list_remove(linklist del)
{
	if(del == NULL)
		return NULL;

	linklist pre;
	for(pre=del; pre->next!=del; pre=pre->next);

	pre->next = del->next;
	del->next = NULL;
	
	return del;
}

// 销毁
void destroy(linklist list)
{
	if(list == NULL)
		return;

	linklist del;
	for(del=list->next; del!=list; del=list->next)
	{
		list_remove(del);
		free(del);
	}
	free(list);
}


// 遍历链表
void show(linklist list)
{
	linklist tmp;
	for(tmp=list; tmp->next!=list; tmp=tmp->next)
	{
		printf("%d ", tmp->data);
	}
	printf("%d\n", tmp->data);
}


// 数三出局
// 当链表中只剩下两个节点时返回
linklist count3(linklist list)
{
	if(list == NULL)
		return list;

	linklist del;
	while(1)
	{
		del = list->next->next;

		if(del == list)
			break;

		list_remove(del);
		free(del);

		list = list->next->next;
	}

	return list;
}
