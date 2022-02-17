#include <stdio.h>
#include <stdlib.h>
FILE *pfin;
FILE *pfout;

int V[100][100];
int V1[100][100];
int V_noduri[100];
int V1_noduri[100];
void read_nodes(int graf[100],int l_nume);
void read_arcs(int graf_matrice[100][100],int l_nume);
void afisare();
