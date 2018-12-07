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
//  描述: 将单链表各项元素前后翻转
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

#include "linklist.h"

int main(int argc, char **argv)
{
	printf("请输入链表节点个数:");

	int n;
	if(scanf("%d", &n) != 1 || n <= 0)
	{
		printf("请输入一个正整数.\n");
		exit(0);
	}

	// 创建一条空链表
	linklist list = init_list();

	// 将1...n的自然数填入链表
	for(int i=1; i<=n; i++)
	{
		linklist new = new_node(i);
		list_add_tail(new, list);
	}
	printf("原始链表数据: ");
	show(list);

	// 翻转各个元素
	reverse(list);
	printf("逆转后的数据: ");
	show(list);

	destroy(list);
	return 0;
}



