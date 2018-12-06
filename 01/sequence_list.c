#include "sequence_list.h"

// 初始化
sqlist init_list(int size)
{
	if(size <= 0)
		return NULL;


	sqlist list = calloc(1, sizeof(*list));
	if(list != NULL)
	{
		list->data = calloc(size, sizeof(datatype));
		if(list->data != NULL)
		{
			list->size = size;
			list->last = -1;
		}
		else
		{
			perror("分配顺序表失败");
			free(list);
		}
	}
	else
		perror("分配管理结构体失败");

	return list;
}

// 判断是否为空
bool is_empty(sqlist list)
{
	return list->last == -1;
}

// 判断是否为满
bool is_full(sqlist list)
{
	return list->last >= list->size;
}

// 插入（末尾）
bool insert(datatype n, sqlist list)
{
	if(is_full(list))
		return false;

	// 放入数据n，并更新最后元素下标
	list->data[++list->last] = n;
	return true;
}


// 删除
bool delete(datatype n, sqlist list, bool (*comp)(datatype d1, datatype d2))
{
	if(is_empty(list))
		return false;

	// 找到要删除的元素的位置
	int pos;
	for(pos = 0; pos<=list->last; pos++)
	{
		if(comp(list->data[pos], n))
			break;
	}

	// 找了一圈没找到
	if(pos > list->last)
		return false;

	// 找到后，将pos后续的所有数据，全部往前移
	for(int i=pos; i<=list->last; i++)
	{
		list->data[i] = list->data[i+1];
	}

	list->last--;
	return true;
}


// 遍历
void traverse(sqlist list, void (*operation)(datatype n))
{
	for(int i=0; i<=list->last; i++)
	{
		operation(list->data[i]);
	}
}


// 销毁
void destroy(sqlist list)
{
	if(list == NULL)
		return;

	free(list->data);
	free(list);
}

// 排序
void sort(sqlist list, bool (*comp)(datatype d1, datatype d2))
{
	if(list->last <= 0)
		return;

	for(int i=1; i<=list->last; i++)
	{
		// 将第i个元素暂存起来
		datatype tmp = list->data[i];

		int pos;
		for(pos=i-1; pos>=0; pos--)
		{
			// 找到data[i]顺序的地方，跳出
			if(comp(list->data[pos], tmp))
				break;

			// 将所有与data[i]逆序的元素依次往后移动
			list->data[pos+1] = list->data[pos];

		}

		// 将data[i]放入恰当的地方
		list->data[pos+1] = tmp;
	}
}
