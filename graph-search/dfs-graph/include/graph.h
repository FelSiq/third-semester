#pragma once
#ifndef __MY_GRAPH_
#define __MY_GRAPH_

typedef int myType;

typedef struct __GRAPH_MATRIX gtype_matrix;

int *graph_dfs(gtype_matrix *, int const, int const);

gtype_matrix *graph_matrix_init(int const, int const, char const);

//Print a given graph, using the appropriate model
void graph_matrix_print(gtype_matrix *);

//Print the adjacent vertexes of a given node
void graph_matrix_vadjprint(gtype_matrix *, int);

//Insert a new edge between two given vertexes, if they exists
void graph_matrix_edgeinsert(gtype_matrix *, int, int, myType);

//Purge a given graph and recover its used heap memory
void graph_matrix_destroy(gtype_matrix **);

#endif