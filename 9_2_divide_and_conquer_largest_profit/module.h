#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int n;
double sir[100];

void citire(FILE *pf, int *n, double sir[100]);
double maxProfit(double sir[100],int left, int right);
