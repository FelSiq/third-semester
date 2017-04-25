#include <stdlib.h>
#include <stdio.h>
#include <cosequential.h>
#include <string.h>

static char *get_str(FILE *input){
	char *s = malloc(sizeof(char));
	register char c = 0x0;
	register unsigned long int i = 0x0, cur_size = 0x1;

	do {
		c = fgetc(input);
		if (c == EOF)
			c = 0xA;
		if (i >= cur_size){
			if (cur_size < ((unsigned long int) 0x1 << (sizeof(unsigned long int) * 0x8 - 0x1))){
				cur_size <<= 0x1;
				s = realloc(s, sizeof(char) * (0x1 + cur_size));
			} else c = 0xA;
		}
		*(s + i++) = c;
	} while (c != 0xA);

	if (i > 0x1){
		s = realloc(s, sizeof(char) * i);
		*(i - 0x1 + s) = 0x0;
		return s;
	} 

	if (s != NULL)
		free(s);
	return NULL;
}

static void dumpfile(FILE *input, FILE *output){
	char *word = NULL;

	while(!feof(input)){
		word = get_str(input);
		if (word != NULL){
			fprintf(output, "%s\n", word);
			free(word);
			word = NULL;
		}
	}
}

inline static char *canonicalkey(char *key){
	char *canonical = malloc(sizeof(char) * (strlen(key) + 1));
	register char *auxpointer;
	const int asciiDif = (int) ('a' - 'A'); 
	if (canonical != NULL){
		strcpy(canonical, key);
		for (register char i = 0; *(i + canonical) != '\0'; ++i){
			//auxpointer is in a register and don't need pointer arithmetic, so it is much faster
			auxpointer = (i + canonical);
			//to upper case...
			if (*auxpointer >= 'a' && *auxpointer <= 'z')
				*auxpointer -= asciiDif;
			//'A'
			if (*auxpointer >= 192 && *auxpointer <= 197)
				*auxpointer = 'A';
			//'E'
			if (*auxpointer >= 200 && *auxpointer <= 203)
				*auxpointer = 'E';
			//'I'
			if (*auxpointer >= 204 && *auxpointer <= 207)
				*auxpointer = 'I';
			//'O'
			if (*auxpointer >= 210 && *auxpointer <= 214)
				*auxpointer = 'O';
			//'U'
			if (*auxpointer >= 217 && *auxpointer <= 220)
				*auxpointer = 'U';

			//'a'
			if (*auxpointer >= 224 && *auxpointer <= 229)
				*auxpointer = 'a';
			//'e'
			if (*auxpointer >= 232 && *auxpointer <= 235)
				*auxpointer = 'e';
			//'i'
			if (*auxpointer >= 236 && *auxpointer <= 239)
				*auxpointer = 'i';
			//'o'
			if (*auxpointer >= 242 && *auxpointer <= 246)
				*auxpointer = 'o';
			//'u'
			if (*auxpointer >= 249 && *auxpointer <= 252)
				*auxpointer = 'u';
		}
	}
	return canonical;
}

void matching(FILE *inputA, FILE *inputB, FILE *output){
	if (inputA != NULL && inputB != NULL && output != NULL){
		//Read the initial keys
		char *word1 = get_str(inputA), *word2 = get_str(inputB);
		char *canonical1 = NULL, *canonical2 = NULL;
		char rescomp = 0;
		while(!feof(inputA) && !feof(inputB)){
			
			#ifdef DEBUG
				printf("comparing: %s\t%s\n", word1, word2);
			#endif
			
			canonical1 = canonicalkey(word1);
			canonical2 = canonicalkey(word2);

			rescomp = strcmp(canonical1, canonical2);

			free(canonical1);
			free(canonical2);
			
			if (rescomp < 0){
				free(word1);
				word1 = get_str(inputA);
			} else if (rescomp > 0){
				free(word2);
				word2 = get_str(inputB);
			} else {
				fprintf(output, "%s\n", word1);
				free(word1);
				free(word2);
				word1 = get_str(inputA);
				word2 = get_str(inputB);	
			}
		}
	}
}

void merging(FILE *inputA, FILE *inputB, FILE *output){
	if (inputA != NULL && inputB != NULL && output != NULL){
		//Read the initial keys
		char *word1 = get_str(inputA), *word2 = get_str(inputB);
		char *canonical1 = NULL, *canonical2 = NULL;
		char rescomp = 0;
		while(!feof(inputA) && !feof(inputB)){
			
			#ifdef DEBUG
				printf("comparing: %s\t%s\n", word1, word2);
			#endif
			
			canonical1 = canonicalkey(word1);
			canonical2 = canonicalkey(word2);

			rescomp = strcmp(canonical1, canonical2);

			free(canonical1);
			free(canonical2);
			

			if (rescomp < 0){
				fprintf(output, "%s\n", word1);
				free(word1);
				word1 = get_str(inputA);
			} else if (rescomp > 0){
				fprintf(output, "%s\n", word2);
				free(word2);
				word2 = get_str(inputB);
			} else {
				fprintf(output, "%s\n", word1);
				free(word1);
				free(word2);
				word1 = get_str(inputA);
				word2 = get_str(inputB);	
			}
		}
		//Check if there's no input remainder
		if (word1 != NULL){
			fprintf(output, "%s\n", word1);
			free(word1);
		}
		if (word2 != NULL){
			fprintf(output, "%s\n", word2);
			free(word2);	
		}

		//Complete the output, if necessary
		if (feof(inputB) && !feof(inputA)){
			dumpfile(inputA, output);
			return;
		}
		if (feof(inputA) && !feof(inputB)){
			dumpfile(inputB, output);
			return;
		}
	}
}