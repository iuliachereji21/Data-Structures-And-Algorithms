#include <stdio.h>
#include <stdlib.h>
#include "module.h"

void citire(FILE *pf, int *n, double sir[100])
{
    int i;
    fscanf(pf,"%d",n);
    for(i=1;i<=*n;i++)
    {
        fscanf(pf,"%lf",&sir[i]);
    }
}
double min2(double a, double b)
{
    if(a<b) return a;
    return b;
}
double minim(double sir[100], int left, int right)
{
    if (left==right)
        return sir[left];
    int m=(left+right)/2;
    return min2(minim(sir,left,m),minim(sir,m+1,right));
}
double max2(double a, double b)
{
    if(a>b) return a;
    return b;
}
double max3(double a, double b, double c)
{
    return max2(max2(a,b),c);
}
double maxim(double sir[100], int left, int right)
{
    if (left==right)
        return sir[left];
    int m=(left+right)/2;
    return max2(maxim(sir,left,m),maxim(sir,m+1,right));
}

double maxProfit(double sir[100],int left, int right)
{
    if(left==right) return 0;
    int m=(left+right)/2;
    return max3(maxProfit(sir,left,m),maxProfit(sir,m+1,right),maxim(sir,m+1,right)-minim(sir,left,m));
}
