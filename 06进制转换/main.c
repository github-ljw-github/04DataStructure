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
//  描述: 使用链式栈实现进制转换
//
////////////////////////////////////////////////

#include <time.h>
#include <math.h>
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

#include "linkstack.h"

// 将十进制转换成八进制
void transform_to_oct(int dec)
{
	if(dec == 0)
	{
		printf("八进制: 0\n");
		return;
	}

	// 初始化一个空栈
	linkstack stack = init_stack();

	for(int n=abs(dec); n>0; n/=8)
	{
		// 1，创建新节点
		stacknode *new = calloc(1, sizeof(stacknode));
		new->data.oct = n%8;
		new->next = NULL;

		// 2，将新节点入栈
		push(new, stack);
	}

	printf("八进制:%c0", dec>=0 ? ' ' : '-');
	stacknode *p;
	while(1)
	{
		p = pop(stack);
		if(p == NULL)
			break;

		printf("%d", p->data.oct);
		free(p);
	}
	printf("\n");
}

// 将十进制转换成十六进制
void transform_to_hex(int dec)
{
	if(dec == 0)
	{
		printf("十六进制: 0x0\n");
		return;
	}

	// 初始化一个空栈
	linkstack stack = init_stack();

	int n = abs(dec); // 绝对值
	while(n > 0)
	{
		// 1，创建新节点
		stacknode *new = calloc(1, sizeof(stacknode));
		switch(n%16)
		{
		case 0 ... 9:
			new->data.hex = n%16 + '0';
			break;
		case 10 ... 15:
			new->data.hex = n%16-10 + 'A';
			break;

		}
		new->next = NULL;

		// 2，将新节点入栈
		push(new, stack);

		n /= 16;
	}

	printf("十六进制:%c0x", dec>=0 ? ' ' : '-');
	stacknode *p;
	while(1)
	{
		p = pop(stack);
		if(p == NULL)
			break;

		printf("%c", p->data.hex);
		free(p);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	printf("请输入一个十进制数:");
	int dec;
	if(scanf("%d", &dec) != 1)
	{
		printf("请输入十进制整数，再见！\n");
		exit(0);
	}

	transform_to_oct(dec);
	transform_to_hex(dec);

	return 0;
}
