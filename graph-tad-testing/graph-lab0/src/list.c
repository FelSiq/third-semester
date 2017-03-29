#include <stdlib.h>
#include <stdio.h>
#include <list.h>

typedef struct __NODE {
	struct __NODE *next, *prev;
	myType weight;
	int key;
} node;

struct __LIST {
	node *root;
};

list *list_init(){
	list *l = malloc(sizeof(list));
	if (l != NULL){
		l->root = malloc(sizeof(node));
		if (l->root != NULL){
			l->root->next = l->root;
			l->root->prev = l->root;
		}
	}
	return l;
}

void list_insert(list *l, int const key, myType weight){
	if (l != NULL && key >= 0){
		node *n = malloc(sizeof(node)), *travel;
		if (n != NULL){
			//setup
			l->root->key = key + 1;

			//Copy the node info, to the node
			n->weight = weight;
			n->key = key;

			//find the right position on the list
			travel = l->root->next;
			while (travel->key < key)
				travel = travel->next;
			
			if (travel->key == key){
				travel->weight = weight;
				free(n);
			} else{
				//Connect the new node on the list
				n->next = travel;
				n->prev = travel->prev;
				travel->prev->next = n;
				travel->prev = n;
			}
		}
	}
}

void list_remove(list *l, int const key){
	if (l != NULL && key >= 0){
		//setup
		node *travel = l->root->next;
		l->root->key = key + 1;

		//find the right node
		while(travel->key <= key)
			travel = travel->next;
		travel = travel->prev;
		//if found the right node
		if (travel->key == key){
			travel->next->prev = travel->prev;
			travel->prev->next = travel->next;
			free(travel);
		}
	}
}

//print the indexes and the weights
void list_print(list *l){
	if (l != NULL){
		//setup
		node *travel = l->root->next;

		//find the right node
		if (travel != l->root){
			while(travel != l->root){
				printf("%d(%d) ", travel->key, travel->weight);
				travel = travel->next;
			}
			printf("\n");
		}
	}
}

//print only the indexes of the list
void list_indexdump(list *l){
	if (l != NULL){
		//setup
		node *travel = l->root->next;

		//find the right node
		if (travel != l->root){
			while(travel != l->root){
				printf("%d ", travel->key);
				travel = travel->next;
			}
			printf("\n");
		}
	}
}

//usage: recover the memory used on the given list
void list_destroy(list **l){
	if (l != NULL && *l != NULL){
		node *travel = (*l)->root->next, *rem;
		while (travel != (*l)->root){
			rem = travel;
			travel = travel->next;
			free(rem);
		}
		free((*l)->root);
		free(*l);
		(*l) = NULL;
	}
}

//usage: check if a list is empty
int list_isempty(list *l){
	if (l != NULL)
		return (l->root == l->root->next);
	return 0;
}

//usage: recover the lightest edge on a graph, represented by a list adj. structure
int list_elightest(list *l, int *v2, myType *w_lightest){
	int myret = 0;
	if (!list_isempty(l)){
		node *travel = l->root->next;
		while(travel != l->root){
			if (*w_lightest > travel->weight || *w_lightest == -1){
				*w_lightest = travel->weight;
				*v2 = travel->key;
				myret = 1;
			}
			travel = travel->next;
		}
	}
	return myret;
}

//usage: this function is an auxiliary to the 
void list_adjdump(list *l, int *size, int **index, myType **weight){
	if (l != NULL){
		//setup
		node *travel = l->root->next;

		//find the right node
		while(travel != l->root){
			*index = realloc(*index, sizeof(int *) * (1 + *size));
			*weight = realloc(*weight, sizeof(myType *) * (1 + *size));
			*((*index) + *size) = travel->key;
			*((*weight) + *size) = travel->weight;
			++(*size);
			//printf("%d(%d) ", travel->key, travel->weight);
			travel = travel->next;
		}
	}	
}