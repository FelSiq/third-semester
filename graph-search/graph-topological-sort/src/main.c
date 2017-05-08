#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int main(int argc, char const *argv[]){
	int numVert, numEdge;
	scanf("%d%*c%d%*c", &numVert, &numEdge);
	gtype_matrix *g = graph_matrix_init(numVert, numEdge, 'D');

	if (g != NULL){
		graph_dfs(g);
		graph_matrix_destroy(&g);
		return 0;
	}
	return 1;
}