#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <graph.h>
#include <queue.h>

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

//usage: aux function to graph_bfs()
inline static void setVec(int *myVec, int size, int value){
	for (int i = 0; i < size; myVec[i] = value, ++i);
}

//usage: find the first path available between two given vertexes, using bfs algorithm
int *graph_bfs(gtype_matrix *graph, int const aVert, int const bVert){
	int *result = NULL, auxSize = 0;
	if (graph != NULL){
		bool *markVector = malloc(sizeof(bool) * graph->num_vert);
		setVec((int *) markVector, graph->num_vert, FALSE);

		if (markVector != NULL){
			int *predecessor = malloc(sizeof(int) * graph->num_vert);
			setVec(predecessor, graph->num_vert, INVALID);

			if (predecessor != NULL){
				//This queue will keep track to the next node set of the BFS algorithm
				QUEUE *q = queue_init();
				if (q != NULL){
					*(markVector + aVert) = TRUE;
					int currentIndex = aVert;
					queue_push(q, currentIndex);
					do {
						if (currentIndex != bVert){
							queue_pop(q);
							//Key still not found, key searching.
							for (register int i = 0; i < graph->num_vert; ++i)
								if (!(*(markVector + i)) && graph->adjmat[currentIndex][i] >= 0){
									*(markVector + i) = TRUE;
									//Enqueue all non-marked adjacent nodes, mark then and keep track of its predecessors. 
									*(predecessor + i) = currentIndex;
									queue_push(q, i);
								}
							
							currentIndex = queue_next(q);
						} else {
							//Key is found.
							//dump all queue, in order to end the loop. Then, 
							//free all memory, and finally return the result.
							while(!queue_isempty(q))
								queue_pop(q);
						}
					} while(!queue_isempty(q));

					//This verification must be here, because the wanted key can be the very last one.
					if (currentIndex == bVert){
						//Key is found, construct the result vector.
						while(currentIndex != INVALID){
							result = realloc(result, sizeof(int) * (2 + auxSize));
							*(result + 1 + auxSize++) = currentIndex;
							currentIndex = *(predecessor + currentIndex);
						}
						if (result != NULL)
							*(result + 0) = auxSize;
					} 

					queue_purge(&q);
				}
				free(predecessor);
			}
			free(markVector);
		}
	}
	return result;
}