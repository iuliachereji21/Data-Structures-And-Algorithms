#include <stdio.h>
#include <stdlib.h>
#define dim 200

typedef struct node
{
    char key[100];
    struct node *next;
}cell;

cell *table[dim];
char s[100];

void inittable(cell *table[dim]);
int hashFunction(char nume[100]);
int insertCell(char s[100]);
void listtable(FILE* pf);
int findname(char s[100]);
int deleteName(char s[100]);
