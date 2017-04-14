#include <stdlib.h>
#include <stdio.h>
#include <dados.h>

/*
	Felipe Alves Siqueira
	NUSP 9847706
*/

typedef struct {
	char fname[SIZE_FNAME], 
	lname[SIZE_LNAME],
	email[SIZE_EMAIL];
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
			char aux[5];
			while(0 < num--){
				REG_PERSON myTemplate = {"", "", "", 0};
				printf("Please supply #%d person information:\n", 
					++indexHolder);

				printf("1. first name:\n");
				scanf("%[^\n]14s", myTemplate.fname);
				__fpurge(stdin);

				printf("2. last name:\n");
				scanf("%[^\n]14s", myTemplate.lname);
				__fpurge(stdin);

				printf("3. email:\n");
				scanf("%[^\n]24s", myTemplate.email);
				__fpurge(stdin);

				printf("4. How old?\n");
				scanf("%[^\n]4s", aux);
				__fpurge(stdin);

				myTemplate.age = atoi(aux);

				fwrite (&myTemplate, sizeof(REG_PERSON), 1, fp);
			}
			printf("End of write process.\n-------------------\n");
			fclose(fp);
		} else printf("e: DATA file can not be open/created.\n");
	} else printf("e: this number does not make sense at this context.\n");
}

void func_seek(int rrn){
	if (rrn >= 0){
		FILE *fp = fopen("DATA", "rb");
		if (fp != NULL){
			fseek(fp, 0, SEEK_END);
			size_t dataSize = ftell(fp);

			if (rrn < dataSize/sizeof(REG_PERSON)){
				REG_PERSON myTemplate;
				
				fseek(fp, rrn * sizeof(REG_PERSON), SEEK_SET);
				fread(&myTemplate, sizeof(REG_PERSON), 1, fp);

				printf("Recovered register:\nFirst name: %s\nLast name: %s\nEmail: %s\nAge: %d\n",
					myTemplate.fname,
					myTemplate.lname,
					myTemplate.email,
					myTemplate.age);

				fclose(fp);
			} else printf("e: invalid RRN.\n");
		}
	} else printf("e: RRN must be a positive integer.\n");
}

void func_dump(){
	FILE *fp = fopen("DATA", "rb");
	if (fp != NULL){
		unsigned long int i = 0;
		unsigned char counter = DUMPSIZE;
		printf("Note: will show registers in packs of %d.\n", counter);
		REG_PERSON myTemplate;
		while(!feof(fp)){
			if(fread(&myTemplate, sizeof(REG_PERSON), 1, fp)){
				printf("- Recovered register w/ RNN #%lu:\nFirst name: %s\nLast name: %s\nEmail: %s\nAge: %d\n------------------------------\n",
					i++,
					myTemplate.fname,
					myTemplate.lname,
					myTemplate.email,
					myTemplate.age);

				if (--counter <= 0){
					printf("Press any key to continue...\n");
					getchar();
					counter = DUMPSIZE;
				}
			}
		}

		fclose(fp);
	}
}