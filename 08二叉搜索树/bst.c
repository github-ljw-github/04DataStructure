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

#include "tree.h"
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

	printf("输入大于0的数插入节点\n");
	printf("输入小于0的数删除节点\n");
	printf("输入0退出程序\n");

	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n > 0)
		{
			linktree new = new_node(n);
			root = bst_insert(root, new);
		}
		else if(n < 0)
		{
			root = bst_remove(root, -n);
		}
		if(n == 0)
			break;

		draw(root);
		sleep(1);
	}
	system("firefox *.html &");

	return 0;
}
