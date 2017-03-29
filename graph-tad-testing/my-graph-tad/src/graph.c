#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

typedef struct __EDGE EDGE;
typedef struct __VERTEX VERTEX;
typedef struct __GRAPH GRAPH;

struct __EDGE {
	EDGE *next, *prev;
	VERTEX *convergent;
	double weight;
};

struct __VERTEX {
	int index;
	EDGE *root;
};

struct __GRAPH {
	int index, num_vertex, next_id;
	VERTEX **vertex;
};

struct __GRAPH_GENERATOR{
	int index, num_graph, next_id;
	GRAPH **graph;
};

//usage: show useful program details
void __FELSIQ_SHOWDETAIL(){
	char const * const ___FELSIQ_GRAPHS_DETAIL [] = {
		"this version will hold only one GRAPH GENERATOR per execution, for simplicy",
		"by standard, all graphs are digraphs",
		"by stardard, all graphs are weighted",
		"every graph/vertex created has a unique ID",
		"unique IDs are generated progressively, and can not be manipulated"
	};

	for (unsigned int i = 0; i < tips_size; 
		printf("%u\t- %s\n", i, *(i + ___FELSIQ_GRAPHS_DETAIL)),
		++i);
}

//usage: shows program commands detail 
void __FELSIQ_SHOWHELP(){
	char const * const ___FELSIQ_GRAPHS_CMD_LABEL [] = {
		"(!) Show this help",
		"(!) Exit program",
		"(!) Show useful program implementation details",
		"(G) Create Graph Generator G",
		"(G) Destroy Graph Generator G",
		"(G) Insert empty GRAPH g on G",
		"(G) Remove gragh g on G",
		"(G) How many graphs g on G",
		"(g) Verify if g is empty",
		"(g) Insert VERTEX v in g",
		"(g) Remove VERTEX v in g",
		"(g) Check if VERTEX v exists on g",
		"(g) How many vertex on g",
		"(g) Print GRAPH g (model adj. lists)",
		"(g) Print GRAPH g (model adj. matrix)",
		"(g) Print adj. vertex of VERTEX v",
		"(g) Insert directed EDGE i->j (with weight w)",
		"(g) Remove directed EDGE i->j",
		"(g) Check if directed EDGE i->j exists",
		"(g) Get the weight w of EDGE i->j",
		"(g) Generate a transpose digraph of g",
		"(g) Get the lightest EDGE on g",
		"(g) Get the heaviest EDGE on g",
		"(!) Number of functions available"
	};

	char const * const ___FELSIQ_GRAPHS_CMD_PARAM [] = {
		"",
		"",
		"",
		"",
		"",
		"",
		"<g index>",
		"",
		"<g index>",
		"<g index>",
		"<g index> <v index>",
		"<g index> <v index>",
		"<g index>",
		"<g index>",
		"<g index>",
		"<g index> <v index>",
		"<g index> <i index> <j index> <weight>",
		"<g index> <i index> <j index>",
		"<g index> <i index> <j index>",
		"<g index> <i index> <j index>",
		"<g index>",
		"<g index>",
		"<g index>",
		""
	};

	printf("There's %d commands available on this version:\n", 
		CMD_PROG_CMDCOUNT);
	for (unsigned int i = 0; i < CMD_PROG_CMDCOUNT; 
		printf("%u\t- %s\n\t\tusage: %d %s\n", 
			i, *(i + ___FELSIQ_GRAPHS_CMD_LABEL),
			i, *(i + ___FELSIQ_GRAPHS_CMD_PARAM)),
		++i);
}

//usage: create a brand-new GRAPH GENERATOR, that can hold n different graphs
GGEN *ggen_init(){
	GGEN *ggen = malloc(sizeof(GGEN));
	if (NULL != ggen){
		ggen->index = 0;
		ggen->num_graph = 0;
		ggen->next_id = 0;
		ggen->graph = NULL;
	}
	return ggen;
}

//usage: auxiliary function of ggen_destroy
inline static void ggen_destroy_vertexes_edges(EDGE *root){
	#ifdef DEBUG
		printf("d: will now destroy a edge linked list...\n");
	#endif

	EDGE *traveller = root, *aux;
	while (traveller != NULL){
		aux = traveller;
		traveller = traveller->next;
		free(aux);
	}

	#ifdef DEBUG
		printf("d: successfully purged this linked list.\n");
	#endif
}

//usage: auxiliary function of ggen_destroy
inline static void ggen_destroy_vertexes(VERTEX **vertex, int num_vertex){
	if (vertex != NULL){
		#ifdef DEBUG
			printf("d: will now destroy a set of %d vertexes...\n", num_vertex);
		#endif

		while(0 < num_vertex--){
			ggen_destroy_vertexes_edges((*(vertex + num_vertex))->root);
			free(*(vertex + num_vertex));
		}
		free(vertex);

		#ifdef DEBUG
			printf("d: finished destruction of this set of vertexes.\n");
		#endif
	}
}

//usage: destroy a entire GRAPH GENERATOR, and all its contents
bool ggen_destroy(GGEN **ggen){
	if (ggen != NULL && *ggen != NULL){
		#ifdef DEBUG
			printf("d: preparing to destroy a ggen of index (%d)...\n---------\n", 
				(*ggen)->index);
		#endif

		if ((*ggen)->graph != NULL){
			#ifdef DEBUG
				printf("d: detected a graph vector on this ggen!\n");
			#endif

			while (0 < (*ggen)->num_graph--){
				ggen_destroy_vertexes((*((*ggen)->graph + (*ggen)->num_graph))->vertex, 
					(*((*ggen)->graph + (*ggen)->num_graph))->num_vertex);
				free(*((*ggen)->graph + (*ggen)->num_graph));
			}
			free((*ggen)->graph);

			#ifdef DEBUG
				printf("d: finished with this graph vector for this ggen.\n");
			#endif
		}
		free(*ggen);
		(*ggen) = NULL;

		#ifdef DEBUG
			printf("d: finished destruction process of this ggen.\n---------\n");
		#endif

		return TRUE;
	}
	return FALSE;
}

//usage: create a brand-new graph g
inline static GRAPH *graph_init(int index){
	#ifdef DEBUG
		printf("d: creating a new graph with index (%d)...\n", index);
	#endif

	if (index >= 0){
		GRAPH *graph = malloc(sizeof(GRAPH));
		if (graph != NULL){
			graph->next_id = 0;
			graph->num_vertex = 0;
			graph->vertex = NULL;
			graph->index = index;
		}
		return graph;
	}
	return NULL;
}

//usage: insert a brand-new graph g on GRAPH GENERATOR G
bool graph_insert(GGEN *ggen){
	if (ggen != NULL){
		//Create a new space for the new graph
		ggen->graph = realloc(ggen->graph, 
			sizeof(GRAPH *) * (1 + ggen->num_graph));
		
		//Create a new graph for the new space
		*(ggen->graph + ggen->num_graph) = graph_init(ggen->next_id++);
		
		//increment the number of graphs availables
		++(ggen->num_graph);

		#ifdef DEBUG
			printf("d: inserted a brand-new graph on ggen of index (%d).\n", 
				ggen->index);
		#endif

		return TRUE;
	}
	return FALSE;
}

//usage: binary search, to find correct positions of the graphs
static int graph_binsearch(GRAPH **graph, int const key, int const size){
	#ifdef DEBUG
		printf("d: searching for graph with index (%d)...\n", key);
	#endif

	//This is a trivial binary search. Nothing special here.

	int start = 0, end = (size - 1), middle;
	while (start <= end){
		middle = (start + end)/2;
		if ((*(graph + middle))->index == key)
			return middle;
		else {
			if (key < (*(graph + middle))->index)
				end = middle - 1;
			else
				start = middle + 1;
		}

	}
	return (-1);
} 

//usage: remove a graph g on the GRAPH GENERATOR, given a index
bool graph_remove(GGEN *ggen, int index){
	if (ggen != NULL && ggen->graph != NULL){
		int posix = graph_binsearch(ggen->graph, index, ggen->num_graph);
		if (posix >= 0){
			#ifdef DEBUG
				printf("d: will now manually destroy a graph of index (%d)...\n", index);
			#endif
			//Found the graph with that index...
			//Purge the selected graph
			ggen_destroy_vertexes((*(ggen->graph + posix))->vertex, 
				(*(ggen->graph + posix))->num_vertex);
			free(*(ggen->graph + posix));
			
			//Realloc graph vectors, if needed
			for (int i = posix; i < (ggen->num_graph - 1); ++i)
				*(ggen->graph + i) = *(ggen->graph + i + 1);

			//Reduce the amount of graphs on this GRAPH GENERATOR
			--(ggen->num_graph);

			//Modify the size of graph vectors

			#ifdef DEBUG
				printf("d: almost finished the manual destruction process of this graph...\n");
			#endif

			if (ggen->num_graph){
				ggen->graph = realloc(ggen->graph,
					sizeof(GRAPH *) * (ggen->num_graph));
				//Make sure that realloc worked
				return (ggen->graph != NULL);
			} 
			//In this case, the number of graphs reached 0
			free(ggen->graph);
			ggen->graph = NULL;
			return TRUE;
		}
		//Not found the graph with that index
		#ifdef DEBUG
			printf("w: can't found desired graph.\n");
		#endif
	}
	return FALSE;
}

//usage: verify if a specific graph is empty
bool graph_isempty(GGEN *ggen, int index){
	if (ggen != NULL && ggen->graph != NULL){
		int posix = graph_binsearch(ggen->graph, 
			index, ggen->num_graph);
		if (posix >= 0)
			return ((*(ggen->graph + posix))->num_vertex == 0);
	}
	return FALSE;
};


//usage: check is the GRAPH GENERATOR is empty
bool ggen_isempty(GGEN *ggen){
	if (ggen != NULL)
		return (ggen->num_graph == 0);
	return FALSE;
}

//usage: count how many graphs are in the GRAPH GENERATOR
int graph_count(GGEN *ggen){
	if (ggen != NULL)
		return ggen->num_graph;
	return -1;
}

//usage: count the number of vertexes of the given graph
int vertex_count(GGEN *ggen, int index){
	if (ggen != NULL && ggen->graph != NULL){
		int posix = graph_binsearch(ggen->graph, 
			index, ggen->num_graph);
		if (posix >= 0)
			return ((*(ggen->graph + posix))->num_vertex);
	}
	return -1;
}


//usage: create a brand-new isolated VERTEX
inline static VERTEX *vertex_init(int index){
	#ifdef DEBUG
		printf("d: creating a new vertex with index (%d)...\n", index);
	#endif

	if (index >= 0){
		VERTEX *vertex = malloc(sizeof(VERTEX));
		if (vertex != NULL){
			vertex->root = NULL;
			vertex->index = index;
		}
		return vertex;
	}
	return NULL;
}

//usage: add a isolated VERTEX on graph of specific index
bool vertex_insert(GGEN *ggen, int index){
	if (ggen != NULL && ggen->graph != NULL){
		#ifdef DEBUG
			printf("d: creating a new vertex on graph of index (%d)...\n", index);
		#endif
		//Search for the right position of the graph with the given index
		int posix = graph_binsearch(ggen->graph, index, ggen->num_graph);
		if (posix >= 0){
			//Create a aux to reduce coding
			GRAPH *aux = (*(ggen->graph + posix));

			//Create a new space to the brand-new vertex
			aux->vertex = realloc(aux->vertex,
				sizeof(VERTEX *) * (1 + aux->num_vertex));

			//Verify if realloc works
			if (aux->vertex != NULL){
				//Create the new vertex and incresease the number of vertexes
				*(aux->vertex + aux->num_vertex++) = vertex_init(aux->next_id++);
				#ifdef DEBUG
					printf("d: successfully added a new vertex of index (%d) in graph of index (%d).\n", 
						aux->next_id - 1, index);
				#endif
				return TRUE;
			}
		}
		//Graph not found, return false
		#ifdef DEBUG
			printf("d: graph not found.\n");
		#endif
	}
	return FALSE;
}

//usage: binary search, to find correct positions of the vertexes
static int vertex_binsearch(VERTEX **vertex, int const key, int const size){
	#ifdef DEBUG
			printf("d: searching for vertex with index (%d)...\n", key);
	#endif

	//This another a trivial binary search. Still nothing special here.

	int start = 0, end = (size - 1), middle;
	while (start <= end){
		middle = (start + end)/2;
		if ((*(vertex + middle))->index == key)
			return middle;
		else {
			if (key < (*(vertex + middle))->index)
				end = middle - 1;
			else
				start = middle + 1;
		}

	}
	return (-1);
} 

//usage: remove a certain vertex of a given graph
bool vertex_remove(GGEN *ggen, int gindex, int vindex){
	if (ggen != NULL && ggen->graph != NULL){
		int posix0, posix1;
		//Search for the right position of the graph of GRAPH MANAGER
		posix0 = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (posix0 >= 0){
			//Then search for the right position of vertex of graph
			//Create a auxliary variable to reduce coding
			GRAPH *aux = *(ggen->graph + posix0);
			posix1 = vertex_binsearch(aux->vertex,
				vindex, aux->num_vertex);
			if (posix1 >= 0){
				//Then destroy it
				ggen_destroy_vertexes_edges((*(aux->vertex) + posix1)->root);
				free((*(aux->vertex) + posix1));

				//Then shift the positions to fill the hole, if needed
				for(int i = posix1; i < (aux->num_vertex - 1); ++i)
					(*(aux + i)) = (*(aux + i + 1));

				//Then subtract a unit from the vertex counter of this graph
				--(aux->num_vertex);

				//Then realloc the vector (or free if necessary) checking the realloc
				if (aux->num_vertex){
					aux->vertex = realloc(aux->vertex, 
						sizeof(VERTEX *) * aux->num_vertex);

					return (aux->vertex != NULL);
				} 

				//In this case, free the vector and set it NULL
				free(aux->vertex);
				aux->vertex = NULL;
				return TRUE;
			}
			#ifdef DEBUG
				printf("d: vertex of given index (%d) not found.\n", vindex);
			#endif
		}
		#ifdef DEBUG
			printf("d: graph with given index (%d) not found.\n", gindex);
		#endif
	}
	return FALSE;
}

//usage: verify if a certain vertex exists on a determined graph
bool vertex_check(GGEN *ggen, int gindex, int vindex){
	if (ggen != NULL && ggen->graph != NULL){
		int posix;
		//Search for the right position of the graph of GRAPH MANAGER
		posix = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (posix >= 0){
			//Then search for the right position of vertex of graph
			return (vertex_binsearch((*(ggen->graph + posix))->vertex, 
				vindex, (*(ggen->graph + posix))->num_vertex) >= 0);
		}
		#ifdef DEBUG
			printf("d: graph with given index (%d) not found.\n", gindex);
		#endif
	}
	return FALSE;
}

//usage: verify if a certain graph exists on a given GRAPH GENERATOR
bool graph_check(GGEN *ggen, int gindex){
	if (ggen != NULL && ggen->graph != NULL)
		return (graph_binsearch(ggen->graph, gindex, ggen->num_graph) >= 0);
	return FALSE;
}

//Usage: prints the graph, on the adjacent list model.
void graph_print(GGEN *ggen, int index){
	if (ggen != NULL){
		int posix = graph_binsearch(ggen->graph, index, ggen->num_graph);
		if (posix >= 0){
			//Aux variables, to reduce coding.
			VERTEX *aux_v;
			EDGE *aux_e;

			//Travel trough all the graph and print, vertex by vertex, it's adjacent nodes.
			for (int i = 0; i < (*(ggen->graph + posix))->num_vertex; printf("\n"), ++i){
				aux_v = *((*(ggen->graph + posix))->vertex + i);
				printf("%d: ", aux_v->index);

				//print the adjacent nodes of the aux_v node.
				aux_e = aux_v->root;
				while (aux_e != NULL){
					printf("[%d (%.3lf)] ", aux_e->convergent->index, aux_e->weight);
					aux_e = aux_e->next;
				}
			}
		}
	}
}

//usage: search a very specific adjacent vertex, given a vertex
inline static double vertex_adjcheck(EDGE *root, int key){
	if (root != NULL){
		EDGE *aux = root;
		while(aux != NULL && aux->convergent->index <= key){
			if (aux->convergent->index != key)
				aux = aux->next;
			else
				return aux->weight;
		}
	}
	return 0.0;
}

//usage: print the adjacency matrix, given a graph
void graph_adjmatrix(GGEN *ggen, int index){
	if (ggen != NULL){
		int posix = graph_binsearch(ggen->graph, index, ggen->num_graph);
		if (posix >= 0){
			//Aux variables, to reduce coding.
			VERTEX *aux_v;

			//Construct a adjacent matrix.
			//First, the aesthetics.
			printf("\t");
			for (int i = 0; i < (*(ggen->graph + posix))->num_vertex; ++i)
				printf("[%d]\t", (*((*(ggen->graph + posix))->vertex + i))->index);
			printf("\n");

			//Then, fill the matrix
			register int aux_numv = (*(ggen->graph + posix))->num_vertex;
			for (int i = 0; i < aux_numv; printf("\n"), ++i){
				aux_v = *((*(ggen->graph + posix))->vertex + i);
				printf("[%d]\t", aux_v->index);
				
				for (register int j = 0; j < aux_numv; ++j)
					printf("%.3lf\t", vertex_adjcheck(aux_v->root, 
						(*((*(ggen->graph + posix))->vertex + j))->index));
			}
		}
	}
}

//usage: given a vertex, print all his adjacent vertexes
void vertex_adjprint(GGEN *ggen, int gindex, int vindex){
	if (ggen != NULL && ggen->graph != NULL){
		int posix0 = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (posix0 >= 0){
			int posix1 = vertex_binsearch((*(ggen->graph + posix0))->vertex, 
				vindex, (*(ggen->graph + posix0))->num_vertex);
			VERTEX *aux_v = *((*(ggen->graph + posix0))->vertex + posix1);
			
			printf("%d: ", aux_v->index);

			//print the adjacent nodes of the aux_v node.
			EDGE *aux_e = aux_v->root;
			while (aux_e != NULL){
				printf("[%d (%.3lf)] ", aux_e->convergent->index, aux_e->weight);
				aux_e = aux_e->next;
			}
		}
	}
}

//usage: get both vertexes for different edge operations.
inline static bool vertexes_get(GGEN *ggen, int gindex, int vindex0, int vindex1, 
	VERTEX **v0aux, VERTEX **v1aux){
	if (ggen != NULL && ggen->graph != NULL){
		int gpos, v0pos, v1pos;
		//find the correct graph
		gpos = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (gpos >= 0){
			//Find both the vertexes
			v0pos = vertex_binsearch((*(ggen->graph + gpos))->vertex, 
				vindex0, (*(ggen->graph + gpos))->num_vertex);
			v1pos = vertex_binsearch((*(ggen->graph + gpos))->vertex, 
				vindex1, (*(ggen->graph + gpos))->num_vertex);

			if (v0pos >= 0 && v1pos >= 0){
				//Create auxiliary variables to reduce coding
				*v0aux = *((*(ggen->graph + gpos))->vertex + v0pos);
				*v1aux = *((*(ggen->graph + gpos))->vertex + v1pos);
				return TRUE;
			}
		}
	}
	return FALSE;
}

//usage: init a brand-new edge, with all parameters already initialized
inline static EDGE *edge_init(EDGE *prev, EDGE *next, VERTEX *convergent, double weight){
	EDGE *edge = malloc(sizeof(EDGE));
	if (NULL != edge){
		edge->next = next;
		edge->prev = prev;
		edge->convergent = convergent;
		edge->weight = weight;
	}
	return edge;
}

//usage: create a incident edge for two given nodes, divergent from vindex0 and convergent for vindex1 
bool edge_insert(GGEN *ggen, int gindex, int vindex0, int vindex1, double weight){
	if (ggen != NULL && ggen->graph != NULL){
		VERTEX *v0aux, *v1aux;
		if (vertexes_get(ggen, gindex, vindex0, vindex1, &v0aux, &v1aux)){
			EDGE *traveller = v0aux->root, *newedge;
			if (traveller != NULL){
				while (traveller->next != NULL && traveller->convergent->index < v1aux->index)
					traveller = traveller->next;

				//traveller are now on the correct position
				if (traveller->convergent->index > v1aux->index){
					//he come BEFORE traveller
					newedge = edge_init(traveller->prev, traveller, v1aux, weight);

					if (traveller->prev != NULL)
						traveller->prev->next = newedge;
					traveller->prev = newedge;

					if (traveller == v0aux->root)
						v0aux->root = newedge;
				} else {
					//he come AFTER traveller
					newedge = edge_init(traveller, traveller->next, v1aux, weight);
					
					if (traveller->next != NULL)
						traveller->next->prev = newedge;
					traveller->next = newedge;
				}
			} else v0aux->root = edge_init(NULL, NULL, v1aux, weight);
			return TRUE;
		}
	}
	return FALSE;
}

//usage: create a incident edge for two given nodes, divergent from vindex0 and convergent for vindex1 
bool edge_remove(GGEN *ggen, int gindex, int vindex0, int vindex1){
	if (ggen != NULL && ggen->graph != NULL){
		VERTEX *v0aux, *v1aux;
		if (vertexes_get(ggen, gindex, vindex0, vindex1, &v0aux, &v1aux)){
			
			return TRUE;
		}
	}
	return FALSE;
}

//usage: check if a given edge exists on a given graph
bool edge_check(GGEN *ggen, int gindex, int vindex0, int vindex1){
	if (ggen != NULL && ggen->graph != NULL){
		VERTEX *v0aux, *v1aux;
		if (vertexes_get(ggen, gindex, vindex0, vindex1, &v0aux, &v1aux)){
			EDGE *eaux = v0aux->root;
			while (eaux != NULL && eaux->convergent->index < vindex1)
				eaux = eaux->next;
			return  (eaux != NULL && eaux->convergent == v1aux);
		}
	}
	return FALSE;
}

//usage: recover the weigth of a edge between two graphs
double edge_weigth(GGEN *ggen, int gindex, int vindex0, int vindex1){
	if (ggen != NULL && ggen->graph != NULL){
		VERTEX *v0aux, *v1aux;
		if (vertexes_get(ggen, gindex, vindex0, vindex1, &v0aux, &v1aux)){
			EDGE *eaux = v0aux->root;
			while (eaux != NULL && eaux->convergent->index < vindex1)
				eaux = eaux->next;
			if (eaux != NULL && eaux->convergent == v1aux)
				return eaux->weight;
		}
	}
	return 0.0;
}

//usage: find which edge is the lightiest on a given graph
bool edge_lightest(GGEN *ggen, int gindex, int *vindex0, int *vindex1, double *myweight){
	if (ggen != NULL && ggen->graph != NULL && !graph_isempty(ggen, gindex)){
		int posix = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (posix >= 0){
			EDGE *lightest = NULL, *traveller;
			for (register int i = 0; i < (*(ggen->graph + posix))->num_vertex; ++i){
				traveller = (*((*(ggen->graph + posix))->vertex + i))->root;
				while (traveller != NULL){
					if (lightest == NULL || traveller->weight < lightest->weight){
						lightest = traveller;
						*vindex0 = i;
					}
					traveller = traveller->next;
				}
			}
			if (lightest != NULL){
				*vindex1 = lightest->convergent->index;
				*myweight = lightest->weight;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//usage: find which edge is the heaviest on a given graph
bool edge_heaviest(GGEN *ggen, int gindex, int *vindex0, int *vindex1, double *myweight){
	if (ggen != NULL && ggen->graph != NULL && !graph_isempty(ggen, gindex)){
		int posix = graph_binsearch(ggen->graph, gindex, ggen->num_graph);
		if (posix >= 0){
			EDGE *heaviest = NULL, *traveller;
			for (register int i = 0; i < (*(ggen->graph + posix))->num_vertex; ++i){
				traveller = (*((*(ggen->graph + posix))->vertex + i))->root;
				while (traveller != NULL){
					if (heaviest == NULL || traveller->weight > heaviest->weight){
						heaviest = traveller;
						*vindex0 = i;
					}
					traveller = traveller->next;
				}
			}
			if (heaviest != NULL){
				*vindex1 = heaviest->convergent->index;
				*myweight = heaviest->weight;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//usage: create the transpose of a given graph, as a new graph on given GRAPH GENERATOR
bool graph_transpose(GGEN *ggen, int index){
	if (ggen != NULL && ggen->graph != NULL){
		int posix = graph_binsearch(ggen->graph, index, ggen->num_graph);
		if (posix >= 0){
			//Insert a new graph
			graph_insert(ggen);

			//Insert all vertexes on given graph, to transpose
			for (int i = 0; i < (*(ggen->graph + posix))->num_vertex; ++i)
				vertex_insert(ggen, ggen->next_id - 1);

			//Insert all correspondent edges on the transpose graph
			VERTEX *vaux;
			EDGE *eaux;
			for (int i = 0; i < (*(ggen->graph + posix))->num_vertex; ++i){
				vaux = *((*(ggen->graph + posix))->vertex + i);
				eaux = vaux->root;
				while (eaux != NULL){
					edge_insert(ggen, ggen->next_id - 1, 
						eaux->convergent->index, vaux->index, eaux->weight);
					eaux = eaux->next;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}