#pragma once
#ifndef __MY_COSEQ_LIB_
#define __MY_COSEQ_LIB_

#define errmessage(x) {printf("fatal error: can't not open \"%s\".\n", *(x + argv));}

enum {
	PROGNAME,
	OPTION,
	INPUTA,
	INPUTB,
	ARGNUM
};


void matching(FILE *, FILE *,FILE *);
void merging(FILE *, FILE *,FILE *);

#endif