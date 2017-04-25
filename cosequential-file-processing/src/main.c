#include <stdlib.h>
#include <stdio.h>
#include <cosequential.h>

int main(int argc, char const *argv[]){
	if (argc != ARGNUM){
		printf("usage: %s <option> <input1> <input2>\n", *argv);
		printf("<option> can be:\n\t- 'u' for union/merge\n\t- 'i' for intersection/matching\n");
		exit(1);
	}
	FILE *inputA, *inputB, *output;

	if((inputA = fopen(*(INPUTA + argv), "r")) == NULL){
		errmessage(INPUTA);
		exit(2);
	}
	if ((inputB = fopen(*(INPUTB + argv), "r")) == NULL){
		fclose(inputA);
		errmessage(INPUTB)
		exit(2);
	}

	if (**(OPTION + argv) == 'u'){
		if ((output = fopen("saidaMerging.txt", "w")) == NULL){
			fclose(inputA);
			fclose(inputB);
			printf("fatal error: can't not open \"saidaMerging.txt\".\n");
			exit(2);
		}
		merging(inputA, inputB, output);
	} else if (**(OPTION + argv) == 'i') {
		if ((output = fopen("saidaMatching.txt", "w")) == NULL){
			fclose(inputA);
			fclose(inputB);
			printf("fatal error: can't not open \"saidaMatching.txt\".\n");
			exit(2);
		}
		matching(inputA, inputB, output);
	}
	else printf("error: unknown option '%c'. aborting.\n", 
		**(OPTION + argv));

	fclose(inputA);
	fclose(inputB);
	fclose(output);
	return 0;
}