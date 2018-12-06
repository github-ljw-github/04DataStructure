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

#include <string.h>
#include "sequence_list.h"

#if 0
struct student
{
	char *name;
	int   age;
	float score;
};

#endif

void show(struct student someone)
{
	printf("姓名: %s\t", someone.name);
	printf("年龄: %d\t", someone.age);
	printf("分数: %f\n", someone.score);
}

bool comp(struct student a, struct student b)
{
	return a.score > b.score; // 按成绩降序排序
}

bool equal(struct student a, struct student b)
{
	return !strcmp(a.name, b.name);
}

int main(void)
{
	// 初始化顺序表
	sqlist list = init_list(10);
	if(list == NULL)
		exit(0);

	// 插入、删除、遍历元素
	struct student Jack = {"Jack", 21, 90.5};
	struct student Rose = {"Rose", 17, 71.5};
	struct student Mike = {"Mike", 23, 59};
	struct student Bill = {"Bill", 24, 88.5};

	insert(Jack, list);
	insert(Rose, list);
	insert(Mike, list);
	insert(Bill, list);

	printf("当前学生情况:\n");
	traverse(list, show);


	delete(Jack, list, equal);
	printf("删除Jack:\n");
	traverse(list, show);


	sort(list, comp);
	printf("按成绩排序:\n");
	traverse(list, show);

	// 销毁顺序表
	destroy(list);

	return 0;
}
