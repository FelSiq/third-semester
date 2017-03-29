#pragma once
#ifndef __MY_LIST_
#define __MY_LIST_

typedef struct __LIST list;
typedef int myType;

list *list_init();
void list_insert(list *, int, myType);
void list_remove(list *, int);
void list_print(list *);
void list_destroy(list **);
int list_isempty(list *);
int list_elightest(list *, int *, myType *);
void list_adjdump(list *, int *, int **, myType **);
void list_indexdump(list *);

#endif