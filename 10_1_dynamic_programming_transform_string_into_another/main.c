#include <stdio.h>
#include <stdlib.h>
#include "module.h"

int i, cost;

int main(int argc, char *argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    fscanf(pfin,"%d\n",&t);
    for(i=1;i<=t;i++)
    {
        length = citire(A, B);
        cost=getBestCost(0,length);
        fprintf(pfout,"%d\n",cost);
    }

    fclose(pfin);
    fclose(pfout);
    return 0;
}
