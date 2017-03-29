#pragma once
#ifndef __MY_GRAPH_
#define __MY_GRAPH_

typedef int myType;

typedef struct __GRAPH_LIST gtype_list;
typedef struct __GRAPH_MATRIX gtype_matrix;

typedef enum {
	FALSE,
	TRUE
} bool;

gtype_matrix *graph_matrix_init(int const, int const, char const);
gtype_list *graph_list_init(int const, int const, char const);

//Print a given graph, using the appropriate model
void graph_matrix_print(gtype_matrix *);
void graph_list_print(gtype_list *);

//Print the adjacent vertexes of a given node
void graph_matrix_vadjprint(gtype_matrix *, int);
void graph_list_vadjprint(gtype_list *, int);

//Insert a new edge between two given vertexes, if they exists
void graph_matrix_edgeinsert(gtype_matrix *, int, int, myType);
void graph_list_edgeinsert(gtype_list *, int, int, myType);

//Remove a given edge,incident to two given vertexes,
//divergent from v1 and convergent to v2 (if digraph), and if it exists at all.
void graph_matrix_edgeremove(gtype_matrix *, int, int);
void graph_list_edgeremove(gtype_list *, int, int);

//Print the transpose of a given graph
void graph_matrix_transp(gtype_matrix *);
void graph_list_transp(gtype_list *);

//Find the lightest edge on a given graph
void graph_matrix_elightest(gtype_matrix *, int *, int *);
void graph_list_elightest(gtype_list *, int *, int *);

//Purge a given graph and recover its used heap memory
void graph_matrix_destroy(gtype_matrix **);
void graph_list_destroy(gtype_list **);

#endif