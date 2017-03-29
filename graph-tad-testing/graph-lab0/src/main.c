#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <graph.h>

#define INVALID -1
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))

int main(int argc, char const *argv[]){
	char directed, gtype, options[3];
	int v1, v2, v_num, e_num;
	myType weight;

	//Can be used to close the program, with the specified command ("EP"), by hand
	bool FLAG = TRUE;
	//Used to shut down the program (after 1000 commands), 
	//as no explicit way to finish the program was delivered.
	short int SEC_VAL = 1000; //Stands for "Security value"

	gtype_matrix *graphm = NULL;
	gtype_list *graphl = NULL;

	//input <D/G> <M/L> <VERTEX NUM> <EDGES NUM>
	scanf("%c%*c%c%*c%d%*c%d%*c", &directed, &gtype, &v_num, &e_num);

	//Init the right core structure
	switch(gtype){
		case 'M': graphm = graph_matrix_init(v_num, e_num, directed); break; //Init a adj. matrix graph
		case 'L': graphl = graph_list_init(v_num, e_num, directed); break; //Init a list graph
		default: exit(0); //Invalid option, exit.
	}

	//edges: <v1 divergent if D> <v2> <weight>
	while (FLAG && 0 < SEC_VAL--){
		//get option
		scanf("%2s%*c", options);
		if (strcmp(options, "IG") == 0){
			switch(gtype){
				//Print command
				case 'M': graph_matrix_print(graphm); break;
				case 'L': graph_list_print(graphl); break;
			}
		} else 	if (strcmp(options, "VA") == 0){
			scanf("%d%*c", &v1);
			switch(gtype){
				//Print adjacent vertexes to a given node
				case 'M': graph_matrix_vadjprint(graphm, v1); break;
				case 'L': graph_list_vadjprint(graphl, v1); break;
			}
		} else 	if (strcmp(options, "AA") == 0){
			scanf("%d%*c%d%*c%d%*c", &v1, &v2, &weight);
			switch(gtype){
				//insert a new edge, given two existent nodes
				case 'M': graph_matrix_edgeinsert(graphm, v1, v2, weight); break;
				case 'L': graph_list_edgeinsert(graphl, v1, v2, weight); break;
			}
		} else 	if (strcmp(options, "RA") == 0){
			scanf("%d%*c%d%*c", &v1, &v2);
			switch(gtype){
				//remove a existent edge, given its incident vertexes
				case 'M': graph_matrix_edgeremove(graphm, v1, v2); break;
				case 'L': graph_list_edgeremove(graphl, v1, v2); break;
			}
		} else 	if (strcmp(options, "IT") == 0){
			//Print transpose, but only if its a digraph
			if (directed == 'D'){
				switch(gtype){
					case 'M': graph_matrix_transp(graphm); break;
					case 'L': graph_list_transp(graphl); break;
				}
			}
		} else 	if (strcmp(options, "MP") == 0){
			//Recover the lightest edge of a weighted graph/digraph, if any
			v1 = INVALID;
			v2 = INVALID;
			switch(gtype){
				case 'M': graph_matrix_elightest(graphm, &v1, &v2); break;
				case 'L': graph_list_elightest(graphl, &v1, &v2); break;
			}
			if (v1 != INVALID && v2 != INVALID){
				if (directed == 'G')
					printf("%d %d\n", MIN(v1, v2), MAX(v1, v2));
				else
					printf("%d %d\n", v1, v2);
			}

		} else if (strcmp(options, "EP") == 0){
			//Command created to finish the program, by hand
			//The run.codes uses the counter (SEC_VAL) to finish, after 1000 iterations.
			FLAG = FALSE;
		}

		//Kinda fugly way to clean the input mini-buffer. But works.
		options[0] = 0;
		options[1] = 0;
	}

	switch(gtype){
		//Destroy the graph/digraph structures, and recover its heap memory to the OS.
		case 'M': graph_matrix_destroy(&graphm); break; //Purge a adj. matrix graph
		case 'L': graph_list_destroy(&graphl); break; //Purge a list graph
	}

	return 0;
}