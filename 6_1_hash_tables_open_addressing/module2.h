#include <stdio.h>
#include <stdlib.h>
#define dim 300

typedef struct node
{
    char key[100];
    struct node *next;
}cell;

cell *table[dim];
char s[100];

int hashFunction1(char nume[100]);
void inittable(cell *table[dim]);
int hashFunction2(char nume[100]);
int hashFunction3(char nume[100]);
int insertCell(char s[100]);
void listtable(FILE* pf);
int findname(char s[100]);
int deleteName(char s[100]);
