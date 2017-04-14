#pragma once
#ifndef __MY_BIRIFOUL_QUEUE
#define __MY_BIRIFOUL_QUEUE

#define STD_RETURN_VAL -1

#include <utils.h>

//FIFO data structure
typedef int ITEM;
typedef struct __QUEUE_STRUCT QUEUE;

//usage: init a brand-new empty queue
QUEUE *queue_init();

//usage: push a new item to the last position of the queue
ITEM queue_push(QUEUE *, ITEM);

//usage: remove the next item on the queue, and return it
ITEM queue_pop(QUEUE *);

//usage: return the next item on the queue, but do not remove it
ITEM queue_next(QUEUE *);

//usage: return the last item on the queue, but do not remove it
ITEM queue_last(QUEUE *);

//usage: check if the given queue is empty
bool queue_isempty(QUEUE *);

//usage: free all memory on the queue, and set the given pointer to NULL.
void queue_purge(QUEUE **);

#endif