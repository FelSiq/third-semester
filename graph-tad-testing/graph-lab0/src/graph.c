#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <list.h>

//Placeholder value, used for filling the adj. matrix gaps, 
//because "0" is assumed a valid edge weight value on this application.
#define INVALID -1

struct __GRAPH_MATRIX {
	//Struct used for adj. matrix structured graph/digraph
	myType **adjmat;
	int num_vert;
	bool directed;
};

struct __GRAPH_LIST {
	//And this one for adj. lists structured graph/digraph
	list **vertex;
	int num_vert;
	bool directed;
};

//usage: this function inits a brand-new adj. matrix graph/digraph, with all its vertexes plus input edges
gtype_matrix *graph_matrix_init(int const v_num, int const e_num, char const directed){
	gtype_matrix *graph = malloc(sizeof(gtype_matrix));
	if (graph != NULL){
		//Create matrix
		graph->num_vert = v_num;
		graph->directed = (directed == 'D');
		graph->adjmat = malloc(sizeof(myType *) * v_num);

		if (graph->adjmat != NULL){
			//Init all weights INVALID by default
			for (register int i = 0; i < v_num; ++i){
				*(graph->adjmat + i) = malloc(sizeof(myType) * v_num);
				for (register int j = 0; j < v_num; 
					*(*(graph->adjmat + i) + j) = INVALID,
					++j);
			}
			//Insert the edges
			int n, m;
			myType weight;
			for (register int i = 0; i < e_num; ++i){
				//Get edge indexes and weight
				scanf("%d%*c%d%*c%d%*c", &n, &m, &weight);

				//Verify if n and m are valid indexes
				if (n < v_num && m < v_num){
					*(*(graph->adjmat + n) + m) = weight;
					//if NOT directed, do the simetric entry on adj. matrix
					if (!graph->directed && m != n)
						*(*(graph->adjmat + m) + n) = weight;
				}
			}
		}
	}
	return graph;
}

//usage: same as above, whoever, using the adj. lists.
gtype_list *graph_list_init(int const v_num, int const e_num, char const directed){
	gtype_list *graph = malloc(sizeof(gtype_list));
	if (graph != NULL){
		graph->num_vert = v_num;
		graph->directed = (directed == 'D');
		graph->vertex = malloc(sizeof(list *) * v_num);

		if (graph->vertex != NULL){
			for (register int i = 0; i < v_num; ++i)
				*(graph->vertex + i) = list_init();

			//Insert the given input edges
			int n, m;
			myType weight;
			for (register int i = 0; i < e_num; ++i){
				//Get edge indexes and weight
				scanf("%d%*c%d%*c%d%*c", &n, &m, &weight);
				if (n < v_num && m < v_num){
					list_insert(*(graph->vertex + n), m, weight);
					//if NOT directed, do the simetric entry on adj. matrix
					if (!graph->directed && m != n)
						list_insert(*(graph->vertex + m), n, weight);
				}
			}
		}
	}
	return graph;
}

//usage: print a adjacency matrix, describing a given graph/digraph
void graph_matrix_print(gtype_matrix *graph){
	if (graph != NULL && graph->adjmat != NULL){
		register int aux = graph->num_vert;
		for (register int i = 0; i < aux; printf("\n"), ++i){
			for (register int j = 0; j < aux; ++j)
				if (INVALID != *(*(graph->adjmat + i) + j))
					printf("%d ", *(*(graph->adjmat + i) + j));
				else 
					printf(". ");
				
		}
	}
}

//usage: print a given graph/digraph list-structured, showing the 
//adjacency nodes of each vertex (line-by-line) and the weight of the edges
void graph_list_print(gtype_list *graph){
	if (graph != NULL && graph->vertex != NULL){
		register int aux = graph->num_vert;
		for (register int i = 0; i < aux; ++i){
			printf("%d. ", i); //Print the index of the current vertex in the front,
			//even if it is actually a isolated vertex.
			list_print(*(graph->vertex + i));
		}
	}
}

//usage: print all adjacent nodes of a given vertex, if it exists (in matrix graphs/digraphs)
void graph_matrix_vadjprint(gtype_matrix *graph, int v1){
	if (graph != NULL && graph->adjmat != NULL && v1 < graph->num_vert){
		register bool FLAG = FALSE; //this flag is used to print a "\n", if any result is found.
		register int aux = graph->num_vert; 
		for (register int i = 0; i < aux; ++i)
			if (*(*(graph->adjmat + v1) + i) != INVALID){
				printf("%d ", i);
				FLAG = TRUE;
			}
		if (FLAG)//See local declaration above for a very quick explanation
			printf("\n");
	}
}

//usage: exactly the same as above. (but for list graphs/digraphs)
void graph_list_vadjprint(gtype_list *graph, int v1){
	if (graph != NULL && graph->vertex != NULL && v1 < graph->num_vert)
		if (!list_isempty(*(graph->vertex + v1)))
			list_indexdump(*(graph->vertex + v1));
}

//usage: insert a brand-new edge, with given parameters, incident to both v1 and v2. (for matrix graphs/digraphs)
//note: if digraph, then v1 is the divergent vertex of the new edge, and v2, the convergent one. 
void graph_matrix_edgeinsert(gtype_matrix *graph, int v1, int v2, myType weight){
	if (graph != NULL && graph->adjmat != NULL &&
		v1 < graph->num_vert && v2 < graph->num_vert){
		*(*(graph->adjmat + v1) + v2) = weight;
		if (!graph->directed && v1 != v2)
			*(*(graph->adjmat + v2) + v1) = weight;
	}
}

//usage: exactly the same as above, but this time with lists graphs/digraphs.
void graph_list_edgeinsert(gtype_list *graph, int v1, int v2, myType weight){
	if (graph != NULL && graph->vertex != NULL &&
		v1 < graph->num_vert && v2 < graph->num_vert){
		list_insert(*(graph->vertex + v1), v2, weight);
		if (!graph->directed && v1 != v2)
			list_insert(*(graph->vertex + v2), v1, weight);
	}
}

//usage: remove a edge (if it exists), incident to v1 and v2. (for matrix-structured graphs/digraphs)
//note: if digraph, then v1 is the divergent vertex of the given edge, and v2 the covergent one.
void graph_matrix_edgeremove(gtype_matrix *graph, int v1, int v2){
	if (graph != NULL && graph->adjmat != NULL &&
		v1 < graph->num_vert && v2 < graph->num_vert){
		*(*(graph->adjmat + v1) + v2) = INVALID;
		if (!graph->directed && v2 != v1)
			*(*(graph->adjmat + v2) + v1) = INVALID;
	}
}

//usage: same as above, but, of course, for list-structured graphs/digraphs.
void graph_list_edgeremove(gtype_list *graph, int v1, int v2){
	if (graph != NULL && graph->vertex != NULL &&
		v1 < graph->num_vert && v2 < graph->num_vert){
		list_remove(*(graph->vertex + v1), v2);
		if (!graph->directed && v2 != v1)
			list_remove(*(graph->vertex + v2), v1);
	}
}

//usage: print the transpose of a matrix-structured digraph
void graph_matrix_transp(gtype_matrix *graph){
	if (graph != NULL && graph->adjmat != NULL){
		register int aux = graph->num_vert; 
		for (register int i = 0; i < aux; printf("\n"), ++i)
			for (register int j = 0; j < aux; ++j)
				if (INVALID != *(*(graph->adjmat + j) + i))
					printf("%d ", *(*(graph->adjmat + j) + i));
				else 
					printf(". ");
	}
}

//usage: the same as above, but, this time, for list-structured digraphs.
//note: this is a extremely costly implementation (both for time and for space) of this function.
void graph_list_transp(gtype_list *graph){
	if (graph != NULL && graph->vertex != NULL){
		//Setup and new variables
		register int aux = graph->num_vert;

		//A new graph is generated for this function.
		gtype_list *myAux = graph_list_init(aux, 0, 'D');

		int *index = NULL, size;
		myType *weight = NULL;

		//Then, the exactly same number of edges are inserted,
		//maintaining its incident nodes, however, of couse,
		//swapping the convergent and divergent vertexes. 
		for (register int i = 0; i < aux; ++i){
			//Reset the size counter
			size = 0;
			//Construct the new transpose graph
			list_adjdump(*(graph->vertex + i), &size, &index, &weight);
			for(register int j = 0; j < size; ++j)
				list_insert(*(myAux->vertex + *(index + j)), i, 
					*(weight + j));
		}

		//Print result
		graph_list_print(myAux);

		//Destroy all auxiliary heap memory used
		free(index);
		free(weight);
		graph_list_destroy(&myAux);
	}
}

//usage: get the lightest edge on a given graph/digraph (for matrix-structured graphs/digraphs)
//note: does not return anything, instead, put the result indexes on *v1 and *v2.
void graph_matrix_elightest(gtype_matrix *graph, int *v1, int *v2){
	if (graph != NULL && graph->adjmat != NULL){
		myType w_lightest = INVALID;

		if (graph != NULL && graph->adjmat != NULL){
			register int aux = graph->num_vert; 
			for (register int i = 0; i < aux; ++i)
				for (register int j = 0; j < aux; ++j)
					if (*(*(graph->adjmat + i) + j) != INVALID && 
						((w_lightest > *(*(graph->adjmat + i) + j)) || 
							w_lightest == INVALID)){
						w_lightest = *(*(graph->adjmat + i) + j);
						*v1 = i;
						*v2 = j;
					}
		}
	}
}

//usage: get the lightest edge on a given graph/digraph (this time for adj. lists graphs/digraphs)
//note: does not return anything, instead, put the result indexes on *v1 and *v2.
void graph_list_elightest(gtype_list *graph, int *v1, int *v2){
	if (graph != NULL && graph->vertex != NULL){
		register int aux = graph->num_vert;
		myType w_lightest = -1;
		for (register int i = 0; i < aux; ++i)
			if (list_elightest(*(graph->vertex + i), v2, &w_lightest)) //search inside lists
				*v1 = i;
	}
}

//usage: same as below, but this time with matrix-structured graph/digraph
void graph_matrix_destroy(gtype_matrix **graph){
	if (graph != NULL && *graph != NULL){
		if ((*graph)->adjmat != NULL){
			register int aux = (*graph)->num_vert;
			for (register int i = 0; i < aux; ++i)
				free(*((*graph)->adjmat + i));
			free((*graph)->adjmat);
		}
		free(*graph);
		(*graph) = NULL;
	}
}

//usage: destroy a given list-structured graph/digraph
void graph_list_destroy(gtype_list **graph){
	if (graph != NULL && *graph != NULL){
		if ((*graph)->vertex != NULL){
			register int aux = (*graph)->num_vert;
			for (register int i = 0; i < aux; ++i)
				list_destroy((*graph)->vertex + i);
			free((*graph)->vertex);
		}
		free(*graph);
		(*graph) = NULL;
	}
}