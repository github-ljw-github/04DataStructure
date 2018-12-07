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
//  描述: 链式栈
//
////////////////////////////////////////////////

#include "linkstack.h"

linkstack init_stack(void)
{
	linkstack stack = calloc(1, sizeof(*stack));
	if(stack != NULL)
	{
		stack->top  = NULL;
		stack->size = 0;
	}
	return stack;
}

bool is_empty(linkstack stack)
{
	return stack->size == 0;
}

stacknode *pop(linkstack stack)
{
	if(is_empty(stack))	
		return NULL;

	stacknode *p = stack->top;
	stack->top = stack->top->next;
	p->next = NULL;
	stack->size--;

	return p;
}

void push(stacknode *new, linkstack stack)
{
	if(is_empty(stack))
	{
		stack->top = new;
	}
	else
	{
		new->next = stack->top;
		stack->top = new;
	}

	stack->size++;
}
