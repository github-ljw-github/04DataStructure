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
//  描述: 通用顺序表，支持不同类型的节点
//  1) 对于内置类型节点，在编译时通过如下宏指定类型即可:
//     -DSQLIST_NODE_DATATYPE="long double"
//
//  2) 对于自定义类型节点，还需在本头文件作显式声明，如:
//  struct student
//  {
//	char *name;
//	int   age;
//	float score;
//  };
//
////////////////////////////////////////////////

#ifndef __SEQUENCE_LIST
#define __SEQUENCE_LIST

#ifndef SQLIST_NODE_DATATYPE
#define SQLIST_NODE_DATATYPE int
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct student
{
	char *name;
	int   age;
	float score;
};

typedef SQLIST_NODE_DATATYPE datatype;

typedef struct
{
	datatype *data;

	int size;
	int last;
}*sqlist;

sqlist init_list(int size);

bool is_empty(sqlist list);
bool is_full (sqlist list);

bool insert(datatype n, sqlist list);
bool delete(datatype n, sqlist list, bool (*comp)(datatype d1, datatype d2));

void traverse(sqlist list, void(*operation)(datatype));
void destroy(sqlist list);

void sort(sqlist, bool(*comp)(datatype d1, datatype d2));

#endif


