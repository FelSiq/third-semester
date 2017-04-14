#pragma once
#ifndef __DADOS_H_
#define __DADOS_H_

/*
	Felipe Alves Siqueira
	NUSP 9847706
*/

#define NUM_FIELDS 4
#define DUMPSIZE 3

enum {
	OP_HELP,
	OP_WRITE,
	OP_BROWSING,
	OP_SEEK,
	OP_EXIT,
	OP_NUM
};

void func_help();
void func_writ(int);
void func_seek(int);
void func_dump();

#endif