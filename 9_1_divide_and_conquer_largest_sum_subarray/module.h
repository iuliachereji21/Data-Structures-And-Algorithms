#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int n;
int sir[100];

void citire(FILE *pf, int *n, int sir[100]);
int maxSumContainingMiddle(int arr[], int left, int middle, int right);
int maxSubArraySum(int arr[], int left, int right);
