#include <stdlib.h>
#include <stdio.h>
#include <stack.h>

typedef struct __stack_node{
	struct __stack_node *prev;
	ITEM item;
} __STACK_NODE;

struct __STACK_STRUCT{
	__STACK_NODE *top;
};

inline static __STACK_NODE *__node_init(__STACK_NODE *prev, ITEM const item){
	__STACK_NODE *qn = malloc(sizeof(__STACK_NODE));
	if (qn != NULL){
		qn->item = item;
		qn->prev = prev;
	}
	return qn;
} 

STACK *stack_init(){
	STACK *q = malloc(sizeof(STACK *));
	if (q != NULL)
		q->top = NULL;
	return q;
}

ITEM stack_push(STACK *q, ITEM const item){
	if (q != NULL){
		__STACK_NODE *qn = __node_init(q->top, item);
		if (qn != NULL){
			q->top = qn;
			return item;
		}
	}
	return STD_RETURN_VAL;
};

bool stack_isempty(STACK *q){
	if (q != NULL)
		return (q->top == NULL);
	return FALSE;
};


ITEM stack_pop(STACK *q){
	if (!stack_isempty(q)){
		__STACK_NODE *aux = q->top;
		ITEM item = aux->item;
		q->top = q->top->prev;
		free(aux);
		return item;
	}
	return STD_RETURN_VAL;
};


ITEM stack_top(STACK *q){
	if (!stack_isempty(q))
		return q->top->item;
	return STD_RETURN_VAL;
};


void stack_purge(STACK **q){
	if (q != NULL && *q != NULL){
		if (!stack_isempty(*q)){
			register __STACK_NODE *tvl = (*q)->top, *rem;
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

//Debug hell
/*
#include <time.h>
int main(int argc, char const *argv[]){
	STACK *q = stack_init();
	srand(time(NULL));

	for (register int k = 0; k < 9; ++k)
		printf("%d ", stack_push(q, rand() % 1001));
	printf("top: %d\n", stack_top(q));
	for (register int k = 0; k < 9; ++k)
		printf("%d ", stack_pop(q));
	printf("\n");
	stack_purge(&q);	
	return 0;
}
*/