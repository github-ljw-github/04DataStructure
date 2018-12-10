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
//  描述: 基于除留余数法+链地址法的哈希表示例
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

char *random_string(void)
{
	char *s = calloc(1, 19);

	char ch[] = {'a', 'A'};
	for(int i=0; i<5; i++)
	{
		s[i] = ch[rand()%2]+rand()%26;
	}

	printf("随机字符串: %s\n", s);
	return s;
}

int sumup(char *s)
{
	int sum = 0;

	for(int i=0; i<strlen(s); i++)
	{
		sum += s[i];
	}

	return sum;
}

bool is_primery(int n)
{
	for(int k=2; k*k<=n; k++)
	{
		if(n%k == 0)
			return false;
	}
	return true;
}

int primery(int max)
{
	if(max <= 1)
		return -1;

	for(int i=max; i>0; i--)
	{
		if(is_primery(i))
			return i;
	}
}

// 哈希链表（单链表）节点
typedef struct node
{
	char *data;
	struct node *next;
}hashnode;


// 哈希表管理结构体
typedef struct
{
	hashnode **table; // 指向哈希表入口
	int capacity;    // 哈希表总容量

	int primery; // 除留余数法最大素数
}*hash_table;


hash_table init_hash(int cap)
{
	if(cap <= 0)
		return NULL;

	hash_table ht = calloc(1, sizeof(*ht));
	if(ht != NULL)
	{
		ht->table    = calloc(cap, sizeof(hashnode *));
		if(ht->table == NULL)
		{
			free(ht);
			return NULL;
		}
		ht->capacity = cap;
		ht->primery  = primery(cap); // 不超过容量的最大素数
		printf("primry: %d\n", ht->primery);
	}
	return ht;
}

void hash_add(char *s, hash_table ht)
{
	// 新建一个节点，存入数据s
	hashnode *new = calloc(1, sizeof(hashnode));
	if(new != NULL)
	{
		new->data = s;
		new->next = NULL;
	}

	// 1，使用除留余数法，获得哈希地址
	int haddr = sumup(s) % ht->primery;
	printf("sumup: %d\n", sumup(s));
	printf("haddr: %d\n", haddr);

	if(ht->table[haddr] == NULL)
	{
		// 将新节点置入哈希表
		ht->table[haddr] = new;
	}
	else
	{
		// 2，使用链地址法，解决冲突
		hashnode *tmp;
		for(tmp=ht->table[haddr]; tmp->next!=NULL; tmp=tmp->next);
		tmp->next = new;
	}
}

int hash_search(char *s, hash_table ht)
{
	// 1，使用除留余数法，获得哈希地址
	int haddr = sumup(s) % ht->primery;

	// 2，使用链地址法，查找冲突链表
	hashnode *tmp;
	for(tmp=ht->table[haddr]; tmp!=NULL; tmp=tmp->next)
	{
		if(!strcmp(tmp->data, s))
			return haddr;
	}
	return -1;
}

void show(hash_table ht)
{
	for(int i=0; i<ht->capacity; i++)
	{
		printf("【%02d】", i);

		for(hashnode *tmp=ht->table[i]; tmp!=NULL; tmp=tmp->next)
		{
			printf("--> \"%s\" ", tmp->data);
		}
		printf("\n");
	}
	printf("=========================\n\n");
}

int main(int argc, char **argv)
{
	// 创建一个容量不超过100的空哈希表
	hash_table ht = init_hash(30);


	// 1，造表: 将若干随机字符串置入哈希表
	srand(time(NULL));
	for(int i=0; i<30; i++)
	{
		hash_add(random_string(), ht);
		usleep(300*1000);
		show(ht);
	}

	
	// 2，查表: 按要求查到（或查不到）所需字符串的位置
	while(1)
	{
		printf("你想要查询的字符串:");
		char s[20];
		bzero(s, 20);
		fgets(s, 20, stdin);

		int pos = hash_search(strtok(s, "\n"), ht);
		if(pos == -1)
		{
			printf("无此字符串，请重新输入.\n");
			continue;
		}

		printf("位置是【%d】\n", pos);
	}

	return 0;
}
