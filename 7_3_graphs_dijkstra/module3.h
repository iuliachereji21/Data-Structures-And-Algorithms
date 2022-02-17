#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int cost[100][100];
int nbnodes;
int source,destination;
int setofnodes[100];
int parent[100];

void citire(int *nrnoduri);
void dijkstra(int nrnodes, int inceput, int iteration);
void afisare(int source,int dest);
