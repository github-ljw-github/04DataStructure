#include "queue.h"

queue create_queue()
{
	queue q = calloc(1, sizeof(*q));
	if(q != NULL)
	{
		q->head = calloc(1, sizeof(queue_node));
		if(q->head == NULL)
		{
			free(q);
			return NULL;
		}

		INIT_LIST_HEAD(&q->head->list);
		q->size  = 0;
	}
	return q;
}


bool is_empty(queue q)
{
	return q->size == 0;
}


// 入队
void enqueue(linktree data, queue q)
{
	// 1，创建新节点
	queue_node *new = calloc(1, sizeof(queue_node));
	if(new != NULL)
	{
		new->data = data;
		INIT_LIST_HEAD(&new->list);
	}

	// 2，将新节点入队
	if(is_empty(q))
	{
		q->head = new;
	}
	else
	{
		// 将新节点接入链表的末尾
		list_add_tail(&new->list, &q->head->list);
	}

	q->size++;
}

// 出队
queue_node *dequeue(queue q)
{
	if(is_empty(q))
		return NULL;

	struct list_head *pos;
	pos = q->head->list.next;

	list_del(pos);
	q->size--;

	return list_entry(pos, queue_node, list);

}
