#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int main(int argc, char const *argv[]){
	printf("> WELCOME TO GRAPH GENERATOR. (Type \"%d\" for help.)\n",
		CMD_PROG_HELP);

	#ifdef DEBUG
		printf("d: running on DEBUG MODE.\n");
	#endif

	//Creating my graph generator.
	//this program driver will support only one graph generator at a time,
	//for implementation simplicity.
	GGEN *ggen = ggen_init();

	if (ggen != NULL){
		//Variables to catch inputs
		int myindex, myindex1, myindex2;
		char myopt;
		double myweight;

		//Aesthetics
		printf("> please insert a valid command:\n");

		do {
			printf("> ");
			//Getting the option
			scanf("%hhd%*c", &myopt);

			switch(myopt){
				case CMD_PROG_HELP: 
					__FELSIQ_SHOWHELP(); 
					break;

				case CMD_PROG_TIPS: 
					__FELSIQ_SHOWDETAIL(); 
					break;

				case CMD_PROG_EXIT: 
					printf("> program will now exit...\n");
					break;

				case CMD_GGEN_INIT: 
					err_version;
					break;

				case CMD_GGEN_DEST: 
					err_version;
					break;

				case CMD_GGEN_ISRT: 
					if (graph_insert(ggen))
						printf("> successfully inserted a brand-new graph.\n");
					else
						printf("e: failed to insert a new empty graph.\n");
					break;

				case CMD_GGEN_REMV:
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (graph_remove(ggen, myindex))
								printf("> successfully removed graph of index %d.\n", myindex);
							else
								printf("e: can't remove graph of given index.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break;

				case CMD_GGEN_CONT:
					if (!ggen_isempty(ggen))
						printf("> there is %d graphs on this GRAPH GENERATOR.\n", graph_count(ggen));
					else
						printf("> the GRAPH GENERATOR is empty.\n");
					break;
				
				case CMD_GRAPH_ISEMPTY:
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (graph_isempty(ggen, myindex))
								printf("> the graph of index (%d) is empty.\n", myindex);
							else
								printf("> the graph of index (%d) is not empty.\n", myindex);
						} else wrg_nonexistent;
					} else err_ggenempty;
					break;

				case CMD_GRAPH_NEWVERT: 
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (vertex_insert(ggen, myindex))
								printf("> successfully created a new vertex on graph of index (%d).\n", myindex);
							else
								printf("e: can't create a vertex, something went wrong.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_REMVERT: 
					scanf("%d%*c%d%*c", &myindex, &myindex1);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (vertex_remove(ggen, myindex, myindex1))
								printf("> successfully removed the vertex (%d) on graph of index (%d).\n", 
									myindex1, myindex);
							else
								printf("e: can't remove the given vertex, something went wrong.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break;

				case CMD_GRAPH_CHKVERT:
					scanf("%d%*c%d%*c", &myindex, &myindex1);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (vertex_check(ggen, myindex, myindex1))
								printf("> found given vertex (%d).\n", myindex1);
							else
								printf("> given vertex (%d) is not found.\n", myindex1);
						} else wrg_nonexistent;
					} else err_ggenempty;
					break;

				case CMD_GRAPH_COUNT:
					scanf("%d%*c", &myindex);
					if (graph_check(ggen, myindex)){
						if (!graph_isempty(ggen, myindex))
							printf("The selected graph has %d vertex(es) in it.\n", vertex_count(ggen, myindex));
						else 
							printf("> selected graph is empty (no vertexes).\n");
					} else wrg_nonexistent;
					break; //(*)

				case CMD_GRAPH_PRINT: 
					scanf("%d%*c", &myindex);
					if (graph_check(ggen, myindex)){
						if (!ggen_isempty(ggen))
							graph_print(ggen, myindex);
						else 
							err_ggenempty;
					} else wrg_nonexistent;
					break; //(*)

				case CMD_GRAPH_ADJMATR: 
					scanf("%d%*c", &myindex);
					if (graph_check(ggen, myindex)){
						if (!ggen_isempty(ggen))
							graph_adjmatrix(ggen, myindex);
						else 
							err_ggenempty;
					} else wrg_nonexistent;
					break; //(*)

				case CMD_GRAPH_ADJVERT: 
					scanf("%d%*c%d%*c", &myindex, &myindex1);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (vertex_check(ggen, myindex, myindex1))
								vertex_adjprint(ggen, myindex, myindex1);
							else
								printf("> given vertex (%d) is not found.\n", myindex1);
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_NEWEDGE: 
					scanf("%d%*c%d%*c%d%*c%lf%*c", &myindex, &myindex1, &myindex2, &myweight);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if(edge_insert(ggen, myindex, myindex1, myindex2, myweight))
								printf("> successfully created a new edge between given vertexes.\n");
							else
								printf("e: can't create edge, something went wrong.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_REMEDGE: 
					scanf("%d%*c%d%*c%d%*c", &myindex, &myindex1, &myindex2);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if(edge_remove(ggen, myindex, myindex1, myindex2))
								printf("> successfully removed the edge between given vertexes.\n");
							else
								printf("e: can't remove edge, something went wrong.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_CHKEDGE: 
					scanf("%d%*c%d%*c%d%*c", &myindex, &myindex1, &myindex2);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if(edge_check(ggen, myindex, myindex1, myindex2))
								printf("> there is a edge between given vertexes.\n");
							else
								printf("> no edge found between given vertexes.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_WGTEDGE: 
					scanf("%d%*c%d%*c%d%*c", &myindex, &myindex1, &myindex2);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							printf("> weigth of the edge (%d)->(%d) of graph (%d): %.3lf\n", 
								myindex1, myindex2, myindex, edge_weigth(ggen, myindex, myindex1, myindex2));
						} else err_ggenempty;
					} else wrg_nonexistent;
					break;
				
				case CMD_GRAPH_LGTEDGE: 
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (edge_lightest(ggen, myindex, &myindex1, &myindex2, &myweight))
								printf("> the lightest edge are described by (%d)->(%d) (w: %.3lf).\n", 
									myindex1, myindex2, myweight);
							else printf("e: can't get the lightest edge on the graph.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				case CMD_GRAPH_HVREDGE: 
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if (edge_heaviest(ggen, myindex, &myindex1, &myindex2, &myweight))
								printf("> the heaviest edge are described by (%d)->(%d) (w: %.3lf).\n", 
									myindex1, myindex2, myweight);
							else printf("e: can't get the heaviest edge on the graph.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break;
				
				case CMD_GRAPH_TRANSPO: 
					scanf("%d%*c", &myindex);
					if (!ggen_isempty(ggen)){
						if (graph_check(ggen, myindex)){
							if(graph_transpose(ggen, myindex))
								printf("> successfully created transpose digraph of graph with index (%d).\n", 
									myindex);
							else printf("e: can't create transpose digraph, something went wrong.\n");
						} else wrg_nonexistent;
					} else err_ggenempty;
					break; //(*)

				default: 
					printf("e: sorry, but this command is not valid. please try again:\n");
					break;
			}
		} while (myopt != CMD_PROG_EXIT);

		if (!ggen_destroy(&ggen)){
			printf("e: something went wrong with GRAPH GENERATOR destruction...\n");
			return 2;
		}

		printf("bye!\n");
		return 0;
	}

	printf("e: program will now exit.\n");
	return 1;
}