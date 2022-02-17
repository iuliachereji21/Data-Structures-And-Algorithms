#include <stdio.h>
#include <stdlib.h>
#include "module.h"

void printMat(int mat[N][N])
{
    int i, j;
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
           fprintf(pfout,"%d ", mat[i][j]);
           if((j==0) && (mat[i][j]<10) && (mat[i][j+1]<10))
                fprintf(pfout,"  ");
           else
           {
                if((j==0) && (mat[i][j]<10) && (mat[i][j+1]>9))
                    fprintf(pfout," ");
                else
                    if(mat[i][j+1]<10)
                        fprintf(pfout," ");
           }

        }
        fprintf(pfout,"\n");
    }
    fprintf(pfout,"\n");
}

int swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

Node* createNewNode(int mat[N][N], int x, int y, int newx, int newy, int level, Node* dad)
{
    Node* node = malloc(sizeof(Node));
    node->dad = dad;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(&node->mat[x][y], &node->mat[newx][newy]);
    node->x = newx;
    node->y = newy;
    node->level = level;
    node->cost = inf;
    return node;
}

int whatCost(int initialMat[N][N], int finalMat[N][N])
{
    int i, j;
    int count = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (initialMat[i][j] && initialMat[i][j] != finalMat[i][j])
                count++;
    return count;
}

/*if x and y is in matrix*/
int isOk(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printSol(Node* root)
{
    if (root == NULL)
        return;
    printSol(root->dad);
    printMat(root->mat);
    fprintf(pfout,"--------------------------------------------\n");
    printf("\n");
}

int min(int a, int b)
{
    return a > b ? b : a;
}

Node* getTopNode()
{
    int i, minm = 1000000;
    for(i=1; i<=rightHeap; i++)
        if(heap[i].visited == 0)
            minm = min(minm, heap[i].nodeHeap->cost + heap[i].nodeHeap->level);
    for(i=1; i<=rightHeap; i++)
        if(heap[i].visited == 0)
        if(minm == heap[i].nodeHeap->cost + heap[i].nodeHeap->level)
        {
            heap[i].visited = 1;
            return heap[i].nodeHeap;
        }
}

void solve(int initialMat[N][N], int x, int y, int finalMat[N][N])
{
    int i;
    Node* root = createNewNode(initialMat, x, y, x, y, 0, NULL);
    root->cost = whatCost(initialMat, finalMat);
    rightHeap = 1;
    sizeHeap = 1;
    heap[rightHeap].nodeHeap = root;
    heap[rightHeap].visited = 0;

    while (sizeHeap != 0)
    {
        Node* minn = getTopNode();
        sizeHeap--;

        if (minn->cost == 0)
        {
            fprintf(pfout,"Number of moves required is: %d\n",minn->level);
            printSol(minn);
            return;
        }

        for (i = 0; i < 4; i++)
        {
            if (isOk(minn->x + dRow[i], minn->y + dCol[i]))
            {
                Node* child = createNewNode(minn->mat, minn->x,
                            minn->y, minn->x + dRow[i],
                            minn->y + dCol[i],
                            minn->level + 1, minn);
                child->cost = whatCost(child->mat, finalMat);

                rightHeap++;
                sizeHeap++;
                heap[rightHeap].nodeHeap = child;
                heap[rightHeap].visited = 0;
            }
        }
    }
}
