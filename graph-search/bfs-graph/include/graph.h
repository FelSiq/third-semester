#pragma once
#ifndef __MY_GRAPH_
#define __MY_GRAPH_

typedef int myType;

typedef struct __GRAPH_MATRIX gtype_matrix;

//Breadth-First Search on given graph, between two given vertexes
//Return a vector with the smallest path possible, if exists. Return Null otherwise.
int *graph_bfs(gtype_matrix *, int const, int const);

//Init a graph w/ adjacency matrix structure
gtype_matrix *graph_matrix_init(int const, int const, char const);

//Print the adjacent vertexes of a given node
void graph_matrix_vadjprint(gtype_matrix *, int);

//Insert a new edge between two given vertexes, if they exists
void graph_matrix_edgeinsert(gtype_matrix *, int, int, myType);

//Purge a given graph and recover its used heap memory
void graph_matrix_destroy(gtype_matrix **);

void graph_matrix_print(gtype_matrix *);

#endif