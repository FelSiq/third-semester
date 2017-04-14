#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int main(int argc, char const *argv[]){
	int numVert, numEdge, aVert, bVert;
	int *indexPath;
	scanf("%d%*c%d%*c", &numVert, &numEdge);
	gtype_matrix *g = graph_matrix_init(numVert, numEdge, 'D');

	if (g != NULL){
		do {
			scanf("%d%*c%d%*c", &aVert, &bVert);
			if (!feof(stdin)){
				if ((indexPath = graph_dfs(g, aVert, bVert)) != NULL){
					for (int i = 0; *(indexPath + i) != -1; 
						printf("%d ", *(indexPath + i)), ++i);
					free(indexPath);
					indexPath = NULL;
				}
				printf("\n");
			}			
		} while(!feof(stdin));
		graph_matrix_destroy(&g);
		return 0;
	}
	return 1;
}