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
static bool dfs_rec(gtype_matrix *graph, STACK *q, bool *markVector, int curIndex, STACK *answer){
	if (curIndex < 0) 
		return FALSE;

	if (!markVector[curIndex]){
		stack_push(q, curIndex);
		markVector[curIndex] = TRUE;

		for (int i = 0; i < graph->num_vert; ++i)
			if (graph->adjmat[curIndex][i] > 0)
				dfs_rec(graph, q, markVector, i, answer);

		stack_push(answer, curIndex);
		stack_pop(q);
		return TRUE;
	}
	return FALSE;
}

static int next(bool *markVector, int vec_size){
	for (register int i = 0; i < vec_size; ++i)
		if (!markVector[i])
			return i;
	return -1;
}

static int getFountain(gtype_matrix *graph){
	for (register int i = 0, counter = 0; i < graph->num_vert; ++i, counter = 0){
		for (register int j = 0; j < graph->num_vert; ++j)
			counter += (graph->adjmat[j][i] > 0 ? 1 : 0);
		//printf("counter:%d\n", counter);
		if (counter == 0)
			return i;
	}
	return -1;
} 

//usage: find the first path available between two given vertexes, using dfs algorithm
void graph_dfs(gtype_matrix *graph){
	if (graph != NULL){
		bool *markVector = malloc(sizeof(bool) * graph->num_vert);
		cleanVec(markVector, graph->num_vert);
		//graph_matrix_print(graph);
		if (markVector != NULL){
			STACK *q = stack_init(), *answer = stack_init();
			if (q != NULL && answer != NULL){
				int k = getFountain(graph);
				do {
					dfs_rec(graph, q, markVector, k, answer);
					k = next(markVector, graph->num_vert);
				} while(k > 0);
				
				while(!stack_isempty(answer))
					printf("%d ", stack_pop(answer));
				printf("\n");
				
				stack_purge(&q);
				stack_purge(&answer);
			}
			free(markVector);
		}
	}
}