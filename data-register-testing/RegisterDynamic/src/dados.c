#include <stdlib.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <dados.h>
#include <string.h>

/*
	Felipe Alves Siqueira
	NUSP 9847706
*/

typedef struct {
	char *fname, 
	*lname,
	*email;
	int age;
} REG_PERSON;

void func_help(){
	char const * const HELP [] = {
		"show this help",
		"write n given registers",
		"browse all saved registers",
		"seek a register with given rnn",
		"end this program"
	};

	for (int i = 0; i < OP_NUM; ++i)
		printf("%d - %s\n", i, *(HELP + i));
}

void func_writ(int num){
	if (num > 0){
		FILE *fp = fopen("DATA", "ab");
		if (fp != NULL){
			int indexHolder = 0;
			size_t sizeHolder[1 + NUM_FIELDS];
			char * (info [NUM_FIELDS]);

			char const * const LABELS [] = {
				"1. first name:",
				"2. last name:",
				"3. email:",
				"4. How old?"
			};

			register int i; 
			while(0 < num--){
				printf("Please supply #%d person information:\n", 
					++indexHolder);

				for (i = 0; i < NUM_FIELDS; ++i){
					printf("%s\n", *(i + LABELS));
					scanf("%m[^\n]s", (i + info));
					__fpurge(stdin);

					*(sizeHolder + i) = 0;
					if (*(i + info) != NULL)
						*(sizeHolder + i) = (1 + strlen(*(i + info)));
				}

				*(sizeHolder + NUM_FIELDS - 1) = sizeof(int);

				*(sizeHolder + NUM_FIELDS) = 0;
				for (i = 0; i < NUM_FIELDS; ++i)
					*(sizeHolder + NUM_FIELDS) += *(sizeHolder + i);
				fwrite ((sizeHolder + NUM_FIELDS), sizeof(int), 1, fp);

				for (i = 0; i < NUM_FIELDS; ++i){
					fwrite ((sizeHolder + i), sizeof(int), 1, fp);
					if (*(i + info) != NULL){
						fwrite (*(i + info), sizeof(char) * *(sizeHolder + i), 1, fp);
						free(*(i + info));
						*(i + info) = NULL;
					}
				}
			}
			printf("End of write process.\n-------------------\n");
			fclose(fp);
		} else printf("e: DATA file can not be opened/created.\n");
	} else printf("e: this number does not make sense at this context.\n");
}

inline static void print_register(FILE *fp, char const * const LABELS []){
	char *myString = NULL;
	int aux = 0;

	for (register int i = 0; i < NUM_FIELDS; ++i){
		fread(&aux, sizeof(int), 1, fp);
		printf("%s", *(i + LABELS));
		if (aux > 0){
			myString = malloc(sizeof(char) * aux);
			if (myString != NULL){
				if (fread(myString, aux, 1, fp))
					printf("%s", myString);
				free(myString);
				myString = NULL;
			}
			aux = 0;
		}
		printf("\n");
	}
	printf("-------------------\n");
}

void func_seek(int rrn){
	if (rrn >= 0){
		FILE *fp = fopen("DATA", "rb");
		if (fp != NULL){
			int aux = 0;
			while (0 < rrn--){
				fread(&aux, sizeof(int), 1, fp);
				if (!fseek(fp, aux, SEEK_CUR)){
					printf("e: invalid RRN.\n");
					fclose(fp);
					return;
				}
			}

			char const * const LABELS [] = {
				"1. first name: ",
				"2. last name: ",
				"3. email: ",
				"4. age: "
			};

			printf("Found a valid register:\n");
			fseek(fp, sizeof(int), SEEK_CUR);
			print_register(fp, LABELS);

			fclose(fp);
		}
	} else printf("e: RRN must be a positive integer.\n");
}

void func_dump(){
	FILE *fp = fopen("DATA", "rb");
	if (fp != NULL){
		char const * const LABELS [] = {
			"1. first name: ",
			"2. last name: ",
			"3. email: ",
			"4. age: "
		};

		//unsigned long int i = 0;
		int regSize = 0;
		unsigned char counter = DUMPSIZE;
		printf("Note: will show registers in packs of %d.\n", counter);

		while(!feof(fp)){
			if(fread(&regSize, sizeof(int), 1, fp)){
				print_register(fp, LABELS);
				if (--counter <= 0){
					printf("Press ENTER to continue...\n");
					getchar();
					counter = DUMPSIZE;
				}
			}
		}

		fclose(fp);
	}
}