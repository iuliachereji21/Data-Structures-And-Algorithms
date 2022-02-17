#include <stdio.h>
#include <stdlib.h>
#include "module.h"

int main(int argc, char *argv[])
{
    pfin = fopen(argv[1], "r");
    pfout=fopen(argv[2],"w");
    if(pfin == NULL)
    {
        printf("error: cannot open input file");
        return 0;
    }
    if(pfin == NULL)
    {
        printf("error: cannot open output file");
        return 0;
    }

    //row and col dislacement
    dRow[0]=1;
    dRow[1]=0;
    dRow[2]=-1;
    dRow[3]=0;

    dCol[0]=0;
    dCol[1]=-1;
    dCol[2]=0;
    dCol[3]=1;

    int i,j;
    /*read input data*/

    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            fscanf(pfin, "%d", &initialMat[i][j]);
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            fscanf(pfin, "%d", &finalMat[i][j]);

    /*get initial positions of 0 in initial matrix*/
    int xPos0, yPos0;
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            if(initialMat[i][j] == 0)
                xPos0 = i, yPos0 = j;

    solve(initialMat, xPos0, yPos0, finalMat);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
