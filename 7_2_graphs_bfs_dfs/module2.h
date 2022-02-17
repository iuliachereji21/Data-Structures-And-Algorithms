#include <stdio.h>
#include <stdlib.h>
FILE *pfin;
FILE *pfout;

int V[100][100];
int V_noduri[100];
int nr_noduri;
int read_nodes(int graf[100],int l_nume);
void read_arcs(int graf_matrice[100][100],int l_nume);

typedef struct node
{
    int label;
    struct node *next;
}nodet;

//am modificat tipu primului parametru de la fct, pt transmitere prin adresa
nodet* enqueue(nodet** ptr_coada, int id);
int dequeue(nodet** ptr_coada);
void breadth_first_traversal(int srcnode);

nodet* push(nodet** ptr_stiva, int id);
int pop(nodet** ptr_stiva);
void depth_first_traversal(int srcnode);

