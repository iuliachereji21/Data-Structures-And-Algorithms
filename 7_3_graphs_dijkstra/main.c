#include <stdio.h>
#include <stdlib.h>
#include "module3.h"


int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    nbnodes=0;
    citire(&nbnodes);

    printf("Introduce the source index: ");
    scanf("%d",&source);
    printf("\n");
    while((source>nbnodes)||(source<1))
    {
        printf("Node not in the graph, introduce another node: ");
        scanf("%d",&source);
        printf("\n");
    }

    dijkstra(nbnodes,source,0);

    printf("Introduce the destination index: ");
    scanf("%d",&destination);
    printf("\n");
    while((destination>nbnodes)||(destination<1)||(parent[destination]<=0))
    {
        if(parent[destination]<=0)
            printf("Node %d can't be reached from node %d, introduce another node: ",destination,source);
        else
            printf("Node not in the graph, introduce another node: ");
        scanf("%d",&destination);
        printf("\n");
    }

    afisare(source,destination);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
