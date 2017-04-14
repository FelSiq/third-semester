#pragma once
#ifndef __MY_BIRIFOUL_STACK
#define __MY_BIRIFOUL_STACK

#define STD_RETURN_VAL -1

#include <utils.h>

//LIFO data structure
typedef int ITEM;
typedef struct __STACK_STRUCT STACK;

//usage: init a brand-new empty stack
STACK *stack_init();

//usage: push a new item to the last position of the stack
ITEM stack_push(STACK *, ITEM);

//usage: remove the top item on the stack, and return it
ITEM stack_pop(STACK *);

//usage: return the top item on the stack, but do not remove it
ITEM stack_top(STACK *);

//usage: check if the given stack is empty
bool stack_isempty(STACK *);

//usage: free all memory on the stack, and set the given pointer to NULL.
void stack_purge(STACK **);

#endif