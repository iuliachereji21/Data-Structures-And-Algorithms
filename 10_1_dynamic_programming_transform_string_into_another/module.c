#include <stdio.h>
#include <stdlib.h>
#include "module.h"


int citire(char A[2000], char B[2000])
{
    fgets(A,2000,pfin);
    fgets(B,2000,pfin);

    int la=0, lb=0, i,j;
    for(i=0;i<2000;i++)
    {
        for(j=0;j<2000;j++)
        {
            c[i][j]=-1;
        }
    }


    i=0;
    while(A[i]!='\n')
    {
        i++;
    }
    la=i;
    i=0;
    while(B[i]!='\n')
    {
        i++;
    }
    lb=i;
    if(lb>la)
    {
        for(i=la;i<lb;i++)
        {
            A[i]='0';
        }
        A[lb]='\0';
        B[lb]='\0';
        return lb;
    }
    if(la>lb)
    {
        for(i=lb;i<la;i++)
        {
            B[i]='0';
        }
        A[lb]='\0';
        B[lb]='\0';
        return la;
    }
    if(la==lb) return la;
}




int getBestCost(int left, int right)
{
    if(left==right)
    {
        if(A[left]==B[left])
        {
            c[left][left]=0;
            return 0;
        }
        else
        {
            c[left][left]=1;
            return 1;
        }
    }
    if(c[left][right]!=-1)
        return c[left][right];
    int k;
    int bestcost=3000;
    for(k=left;k<right;k++) //taieturi
    {
        int cost=getBestCost(left,k)+getBestCost(k+1,right);
        if(bestcost>cost)
        {
            bestcost=cost;
        }
    }
    c[left][right]=bestcost;
    return c[left][right];
}
