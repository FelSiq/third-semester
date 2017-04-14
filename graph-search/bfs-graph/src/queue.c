#include <stdlib.h>
#include <stdio.h>
#include <queue.h>
#include <utils.h>

typedef struct __queue_node{
	struct __queue_node *prev;
	ITEM item;
} __QUEUE_NODE;

struct __QUEUE_STRUCT{
	__QUEUE_NODE *first, *last;
};

inline static __QUEUE_NODE *__node_init(ITEM const item){
	__QUEUE_NODE *qn = malloc(sizeof(__QUEUE_NODE));
	if (qn != NULL){
		qn->item = item;
		qn->prev = NULL;
	}
	return qn;
} 

QUEUE *queue_init(){
	QUEUE *q = malloc(sizeof(QUEUE *));
	if (q != NULL){
		q->first = NULL;
		q->last = NULL;
	}
	return q;
}

ITEM queue_push(QUEUE *q, ITEM const item){
	if (q != NULL){
		__QUEUE_NODE *qn = __node_init(item);
		if (qn != NULL){
			if (!queue_isempty(q))
				q->last->prev = qn;
			else 
				q->first = qn;
			q->last = qn;
			return item;
		}
	}
	return STD_RETURN_VAL;
};

bool queue_isempty(QUEUE *q){
	if (q != NULL)
		return (q->first == NULL && q->last == NULL);
	return FALSE;
};


ITEM queue_pop(QUEUE *q){
	if (!queue_isempty(q)){
		__QUEUE_NODE *aux = q->first;
		ITEM item = aux->item;
		q->first = q->first->prev;
		if (q->first == NULL)
			q->last = NULL;
		free(aux);
		return item;
	}
	return STD_RETURN_VAL;
};


ITEM queue_next(QUEUE *q){
	if (!queue_isempty(q))
		return q->first->item;
	return STD_RETURN_VAL;
};


ITEM queue_last(QUEUE *q){
	if (!queue_isempty(q))
		return q->last->item;
	return STD_RETURN_VAL;
};


void queue_purge(QUEUE **q){
	if (q != NULL && *q != NULL){
		if (!queue_isempty(*q)){
			register __QUEUE_NODE *tvl = (*q)->first, *rem;
			while (tvl != NULL){
				rem = tvl;
				tvl = tvl->prev;
				free(rem);
			}
			rem = NULL;
		}
		free(*q);
		(*q) = NULL;
	}
};