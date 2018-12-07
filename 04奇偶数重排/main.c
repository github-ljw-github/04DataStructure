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
//  描述: 使用传统双循环链表，实现奇偶数重排
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

#include "dlinklist.h"

int main(int argc, char **argv)
{
	// 创建空链表
	dlinklist head = init_list();
	
	printf("请输入节点个数:");
	int n;
	if(scanf("%d", &n)!=1 || n<=0)
	{
		printf("请输入正整数，再见！\n");
		exit(0);
	}

	// 依次在链表中插入自然数
	for(int i=1; i<=n; i++)
	{
		dlinklist new = new_node(i);
		list_add_tail(new, head);
	}
	printf("重排前:");
	show(head);

	rearrange(head);
	printf("重排后:");
	show(head);

	return 0;
}



