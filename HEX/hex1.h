#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void show_state(int n,char **graph);
void new_game(char *c1,int *b,char *c2,int *s,int a,int *n,char **graph,int**mov);
int play(int b,char **graph,int moves,int**mov);
void undo(char**graph,int**mov,int*moves,char player);
int winner(char c,int n,char **graph,char **path,int **mov,int moves,int i,int j,int *anadromes,int *edge1,int *edge2);
int find(char **path, int gi, int gj,int anadromes);
void bubble(char c,char **path,int n);
