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
//  描述: 基于队列算法，按层遍历二叉搜索树
//
////////////////////////////////////////////////

#include "drawtree.h"
#include "queue.h"

linktree bst_insert(linktree root, linktree new)
{
	if(new == NULL)
		return root;

	if(root == NULL)
		return new;

	if(new->data > root->data)
	{
		root->rchild = bst_insert(root->rchild, new);
	}
	else if(new->data < root->data)
	{
		root->lchild = bst_insert(root->lchild, new);
	}
	else
	{
		printf("%ld is already exist.\n", new->data);
	}

	return root;
}

linktree bst_find(linktree root, tn_datatype data)
{
	if(root == NULL)
		return NULL;

	if(data < root->data)
		return bst_find(root->lchild, data);
	else if(data > root->data)
		return bst_find(root->rchild, data);
	else
		return root;
}

linktree bst_remove(linktree root, tn_datatype n)
{
	if(root == NULL)
		return NULL;

	if(n < root->data)
		root->lchild = bst_remove(root->lchild, n);
	else if(n > root->data)
		root->rchild = bst_remove(root->rchild, n);
	else
	{
		linktree tmp;
		if(root->lchild != NULL)
		{
			for(tmp=root->lchild; tmp->rchild!=NULL;
			    tmp=tmp->rchild);

			root->data = tmp->data;
			root->lchild = bst_remove(root->lchild, tmp->data);
		}
		else if(root->rchild != NULL)
		{
			for(tmp=root->rchild; tmp->lchild!=NULL;
			    tmp=tmp->lchild);

			root->data = tmp->data;
			root->rchild = bst_remove(root->rchild, tmp->data);
		}
		else
		{
			free(root);
			return NULL;
		}
	}
	return root;
}

int main(void)
{
	linktree root;
	root = NULL;

	int n;
	printf("请输入节点个数:");
	if(scanf("%d", &n) != 1 || n <= 0)
	{
		printf("请输入正整数，再见！\n");
		exit(0);
	}

	// 创建一棵包含若干随机数的BST
	srand(time(NULL));
	for(int i=0; i<n; i++)
	{
		linktree new = new_node(rand() % 100);
		root = bst_insert(root, new);
	}

	// 生成网页文件
	draw(root);
	system("firefox *.html &");

	// 创建一个空队列
	queue q = create_queue();

	// 将队头元素入队
	enqueue(root, q);

	printf("按层遍历:");
	queue_node *tmp;
	while(!is_empty(q))
	{
		tmp = dequeue(q);
		if(tmp != NULL)
		{
			printf("%ld ", tmp->data->data);
		}

		if(tmp->data->lchild != NULL) enqueue(tmp->data->lchild, q);
		if(tmp->data->rchild != NULL) enqueue(tmp->data->rchild, q);
	}
	printf("\n");

	return 0;
}
