#include <stdio.h>
#include <stdlib.h>
#define inf 1000000
#define N 4

typedef struct sNode Node;
struct sNode
{
    Node* dad;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

typedef struct heapStructt heapStruct;
struct heapStructt{
    Node* nodeHeap;
    int visited;
};




FILE *pfin;
FILE *pfout;
heapStruct heap[50];
int rightHeap, sizeHeap;
int dRow[4];
int dCol[4];
int initialMat[N][N], finalMat[N][N];

void printMat(int mat[N][N]);
int swap(int *a, int *b);
Node* createNewNode(int mat[N][N], int x, int y, int newx, int newy, int level, Node* dad);
int whatCost(int initialMat[N][N], int finalMat[N][N]);
int isOk(int x, int y);
void printSol(Node* root);
int min(int a, int b);
Node* getTopNode();
void solve(int initialMat[N][N], int x, int y, int finalMat[N][N]);
