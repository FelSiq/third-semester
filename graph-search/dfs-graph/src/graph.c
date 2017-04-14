#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <graph.h>
#include <stack.h>

#define INVALID -1

struct __GRAPH_MATRIX {
	//Struct used for adj. matrix structured graph/digraph
	myType **adjmat;
	int num_vert;
	bool directed;
};

//usage: this function inits a brand-new adj. matrix graph/digraph, with all its vertexes plus input edges
gtype_matrix *graph_matrix_init(int const v_num, 
	int const e_num, char const directed){
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
			myType const weight = 1;
			for (register int i = 0; i < e_num; ++i){
				//Get edge indexes
				scanf("%d%*c%d%*c", &n, &m);

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

//usage: insert a brand-new edge, with given parameters, incident to both v1 and v2. (for matrix graphs/digraphs)
//note: if digraph, then v1 is the divergent vertex of the new edge, and v2, the convergent one. 
void graph_matrix_edgeinsert(gtype_matrix *graph, int const v1, 
	int const v2, myType const weight){
	if (graph != NULL && graph->adjmat != NULL &&
		v1 < graph->num_vert && v2 < graph->num_vert){
		*(*(graph->adjmat + v1) + v2) = weight;
		if (!graph->directed && v1 != v2)
			*(*(graph->adjmat + v2) + v1) = weight;
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

//usage: aux function to graph_dfs()
inline static void cleanVec(bool *myVec, int size){
	for (int i = 0; i < size; myVec[i] = FALSE, ++i);
}

//usage: aux function to graph_dfs()
static bool dfs_rec(gtype_matrix *graph, STACK *q, 
	bool *markVector, int curIndex, int const key, int *pathSize){
			
	if (!markVector[curIndex]){

		stack_push(q, curIndex);
		++(*pathSize);
		markVector[curIndex] = TRUE;
		if (curIndex == key)
			return TRUE;

		for (int i = 0; i < graph->num_vert; ++i)
			if (graph->adjmat[curIndex][i] > 0 && dfs_rec(graph, q, markVector, i, key, pathSize))
				return TRUE;
		markVector[curIndex] = FALSE;
		--(*pathSize);
		stack_pop(q);
	}
	return FALSE;
}

//usage: find the first path available between two given vertexes, using dfs algorithm
int *graph_dfs(gtype_matrix *graph, int const aVert, int const bVert){
	int *result = NULL, auxSize = 0;
	if (graph != NULL){
		bool *markVector = malloc(sizeof(bool) * graph->num_vert);
		cleanVec(markVector, graph->num_vert);
		if (markVector != NULL){
			STACK *q = stack_init();
			if (q != NULL){
				if(dfs_rec(graph, q, markVector, aVert, bVert, &auxSize)){
					result = malloc(sizeof(int) * (1 + auxSize));
					if (result != NULL){
						//Mark the end of vector, to print in main
						*(result + auxSize--) = INVALID;
						while(!stack_isempty(q))
							*(result + auxSize--) = stack_pop(q);
					}
				}
				stack_purge(&q);
			}
			free(markVector);
		}
	}
	return result;
}