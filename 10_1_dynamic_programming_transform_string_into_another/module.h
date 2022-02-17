#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int t;
int length;
char A[2000];
char B[2000];
int c[2000][2000];

int citire(char A[2000], char B[2000]);
int getBestCost(int left, int right);
