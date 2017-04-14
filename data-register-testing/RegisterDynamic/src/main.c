#include <stdlib.h>
#include <stdio.h>
#include <dados.h>

/*
	Felipe Alves Siqueira
	NUSP 9847706
*/

int main(int argc, char const *argv[]){
	char op;
	int param;

	printf("Welcome to the SISAM (\"SISAM Is a Simple Archive Manager\")!\n");

	while(op != OP_EXIT){
		printf("Please insert a valid command: (Type \"%d\" for command list!)\n> ", OP_HELP);
		scanf("%hhd%*c", &op);

		switch(op){
			case OP_HELP:
				func_help();
				break;

			case OP_EXIT:
				printf("Program will now exit. See ya!\n"); 
				break;

			case OP_WRITE: 
				printf("Please, insert the number of registers for this write:\n> ");
				scanf("%d%*c", &param);
				func_writ(param);
				break;

			case OP_SEEK: 
				printf("Type a valid the RRN:\n> ");
				scanf("%d%*c", &param);
				func_seek(param);
				break;

			case OP_BROWSING: 
				func_dump();
				break;

			default:
				printf("e: unknown command. \n");
				break;
		}
		param = 0;
	}

	return 0;
}