#pragma once
#ifndef __FELSIQ_GRAPHS_
#define __FELSIQ_GRAPHS_
#include "utils.h"

typedef struct __GRAPH_GENERATOR GGEN;

#define err_version {printf ("(!) sorry, but this function can not be directly controlled on this version (only one graph generator permitted)\n");}
#define err_ggenempty {printf("e: this GRAPH MANAGER is empty, there's no graph to work on.\n");}
#define wrg_nonexistent {printf("> this given index does not have a correspondent graph.\n");}

#define tips_size 5

enum {
	CMD_PROG_HELP,
	CMD_PROG_EXIT,
	CMD_PROG_TIPS,
	CMD_GGEN_INIT,
	CMD_GGEN_DEST,
	CMD_GGEN_ISRT, //(*)
	CMD_GGEN_REMV,
	CMD_GGEN_CONT,
	CMD_GRAPH_ISEMPTY,
	CMD_GRAPH_NEWVERT,
	CMD_GRAPH_REMVERT,
	CMD_GRAPH_CHKVERT,
	CMD_GRAPH_COUNT, //(*)
	CMD_GRAPH_PRINT, //(*)
	CMD_GRAPH_ADJMATR, //(*)
	CMD_GRAPH_ADJVERT, //(*)
	CMD_GRAPH_NEWEDGE, //(*)
	CMD_GRAPH_REMEDGE, //(*)
	CMD_GRAPH_CHKEDGE, //(*)
	CMD_GRAPH_WGTEDGE,
	CMD_GRAPH_TRANSPO, //(*)
	CMD_GRAPH_LGTEDGE, //(*)
	CMD_GRAPH_HVREDGE,
	CMD_PROG_CMDCOUNT
};

//Functions
void __FELSIQ_SHOWHELP();
void __FELSIQ_SHOWDETAIL();

GGEN *ggen_init();
bool ggen_destroy(GGEN **);
bool ggen_isempty(GGEN *);

bool graph_insert(GGEN *); //(*)
bool graph_remove(GGEN *, int);
bool graph_isempty(GGEN *, int);
bool graph_check(GGEN *, int);
bool graph_transpose(GGEN *, int);

void graph_print(GGEN *, int);
void graph_adjmatrix(GGEN *, int);

int graph_count(GGEN *);

void vertex_adjprint(GGEN *, int, int);

bool vertex_insert(GGEN *, int);
bool vertex_remove(GGEN *, int, int);
bool vertex_check(GGEN *, int, int);

int vertex_count(GGEN *, int);

double edge_weigth(GGEN *, int, int, int);

bool edge_insert(GGEN *, int, int, int, double);
bool edge_remove(GGEN *, int, int, int);
bool edge_check(GGEN *, int, int, int);
bool edge_lightest(GGEN *, int, int *, int *, double *);
bool edge_heaviest(GGEN *, int, int *, int *, double *);

#endif