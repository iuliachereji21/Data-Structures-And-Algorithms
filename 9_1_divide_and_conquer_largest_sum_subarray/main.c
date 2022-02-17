#include <stdio.h>
#include <stdlib.h>
#include "module.h"

int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");

    citire(pfin,&n,sir);
    int sum=maxSubArraySum(sir,0,n-1);

    fprintf(pfout,"%d",sum);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
