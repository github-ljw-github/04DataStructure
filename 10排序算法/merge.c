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
//  描述: 外部归并排序算法示例
//
////////////////////////////////////////////////
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


int partition(int data[], int len)
{
	if(len <= 1)
		return 0;

	int i = 0;
	int j = len-1;
	while(i < j)
	{
		// 从右向左比较，顺序j--，逆序交换
		while(data[i]<=data[j] && i<j)
			j--;
		swap(&data[i], &data[j]);

		// 从左向右比较，顺序i++，逆序交换
		while(data[i]<=data[j] && i<j)
			i++;
		swap(&data[i], &data[j]);
	}

	return i;
}

void quick_sort(int data[], int len)
{
	if(len <= 1)
		return;

	int pivot = partition(data, len);

	quick_sort(data, pivot);
	quick_sort(data+pivot+1, len-pivot-1);
}

// 融合begin到end的所有文件，并入文件begin
void merge(int begin, int end)
{
	if(end-begin <= 0)
		return;

	// 融合begin+1到end的所有文件，并入文件begin+1
	merge(begin+1, end);


	// 合并begin和begin+1
	char f1[10], f2[10];
	bzero(f1, 10);
	bzero(f2, 10);
	snprintf(f1, 10, "%d.txt", begin);
	snprintf(f2, 10, "%d.txt", begin+1);

	printf("正在合并%s和%s...\n", f1, f2);

	FILE *fp1 = fopen(f1, "r");
	FILE *fp2 = fopen(f2, "r");

	unsigned n1, n2;
	if(fscanf(fp1, "%u", &n1) == EOF)
	{
		fclose(fp1);
		fclose(fp2);

		remove(f1);
		rename(f2, f1);
		return;
	}
	if(fscanf(fp2, "%u", &n2) == EOF)
	{
		fclose(fp1);
		fclose(fp2);

		remove(f2);
		return;
	}

	// 临时存放合并的数据，最后更名为begin
	FILE *tmp = fopen("tmp.txt", "w+");
	int fp1_done = false;
	int fp2_done = false;
	while(1)
	{
		if(n1 < n2)
		{
			fprintf(tmp, "%u\n", n1);
			if(fscanf(fp1, "%u", &n1) == EOF)
			{
				fprintf(tmp, "%u\n", n2);
				fp1_done = true;
				break;
			}
		}
		else
		{
			fprintf(tmp, "%u\n", n2);
			if(fscanf(fp2, "%u", &n2) == EOF)
			{
				fprintf(tmp, "%u\n", n1);
				fp2_done = true;
				break;
			}
		}
	}

	// 将剩余的数据置入tmp中
	if(fp1_done)
	{
		while(fscanf(fp2, "%u", &n2) != EOF)
		{
			fprintf(tmp, "%u\n", n2);
		}
	}
	else
	{
		while(fscanf(fp1, "%u", &n1) != EOF)
		{
			fprintf(tmp, "%u\n", n1);
		}
	}

	// 删除原有文件，并将tmp更名为begin
	fclose(fp1);
	fclose(fp2);

	if(remove(f1) == -1)
	{
		printf("删除文件%s失败:%s\n", f1, strerror(errno));
		exit(0);
	}
	if(remove(f2) == -1)
	{
		printf("删除文件%s失败:%s\n", f2, strerror(errno));
		exit(0);
	}

	fclose(tmp);
	rename("tmp.txt", f1);
}

int main(int argc, char **argv)
{
	// 打开一个包含百万数据级别的文件
	FILE *src = fopen("numbers.txt", "r");
	if(src == NULL)
	{
		perror("打开文件失败");
		exit(0);
	}

	// 1，将原始数据文件，分割成N个有序的子文件
	bool done = false;
	char file[20];
	int N = 0;
	int wanted = 1000*1000; // 假设每次只能读取10万个数据
	int infact = wanted;
	while(1)
	{
		// 试图从文件读取 wanted 个数据
		unsigned *data = calloc(wanted, sizeof(unsigned));
		for(int i=0; i<wanted; i++)
		{
			if(fscanf(src, "%u", &data[i]) == EOF)
			{
				done = true;
				infact = i;
				break;
			}
		}

		// 对这读到的 infact 个数据进行排序
		quick_sort(data, infact);

		// 创建临时文件，存放部分数据
		bzero(file, 20);
		snprintf(file, 20, "%d.txt", ++N);
		FILE *fp = fopen(file, "w");

		// 将排好序的部分数据写入临时文件，保存起来
		for(int i=0; i<infact; i++)
		{
			fprintf(fp, "%u\n", data[i]);
		}
		free(data);
		fclose(fp);

		if(done)
			break;
	}
	fclose(src);

	// 2，将N个有序子文件，合并成一个有序文件
	merge(1, N);

	return 0;

}
