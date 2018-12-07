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
//  描述: 约瑟夫杀人游戏
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
		list = list_add_tail(new, list);
	}
	printf("开  始:");
	show(list);

	// 开始约瑟夫杀人游戏
	list = count3(list);
	printf("幸存者:");
	show(list);

	destroy(list);
	return 0;
}



