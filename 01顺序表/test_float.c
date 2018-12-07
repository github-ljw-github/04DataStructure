////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  描述: 测试顺序表
//
////////////////////////////////////////////////////

#include "sequence_list.h"

void show(float n)
{
	printf("%.2f ", n);
}

bool comp(float f1, float f2)
{
	return f1 > f2; // 降序排列
}

bool equal(float f1, float f2)
{
	return f1 == f2;
}

int main(void)
{
	// 初始化顺序表
	sqlist list = init_list(10);
	if(list == NULL)
		exit(0);

	// 插入、删除、遍历元素
	float n;
	while(1)
	{
		if(scanf("%f", &n) != 1)
		{
			printf("请输入实数\n");
			while(getchar() != '\n');
			continue;
		}

		if(n == 0)
			break;

		if(n > 0)
		{
			if(!insert(n, list))
				printf("【插入元素失败】\n");
		}

		if(n < 0)
		{
			if(!delete(-n, list, equal))
				printf("【删除元素失败】\n");
		}

		printf("当前顺序表元素:");
		traverse(list, show);
		printf("\n");
	
	}

	// 排序并输出
	sort(list, comp);
	printf("排序后元素:");
	traverse(list, show);
	printf("\n");

	// 销毁顺序表
	destroy(list);

	return 0;
}
