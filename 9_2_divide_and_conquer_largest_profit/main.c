#include <stdio.h>
#include <stdlib.h>
#include "module.h"


int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    citire(pfin,&n,sir);
    double profit=maxProfit(sir,1,n);

    fprintf(pfout,"%lf",profit);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
