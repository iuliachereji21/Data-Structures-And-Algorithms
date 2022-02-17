#include <stdio.h>
#include <stdlib.h>
#include "module.h"

void citire(FILE *pf, int *n, int sir[100])
{
    int i;
    fscanf(pf,"%d",n);
    for(i=0;i<*n;i++)
    {
        fscanf(pf,"%d",&sir[i]);
    }
}

int max2(int a, int b)
{
    return (a > b)? a : b;
}
int max3(int a, int b, int c)
{
    return max2(max2(a, b), c);
}

int maxSumContainingMiddle(int arr[], int left, int middle, int right)
{
    int sum = 0;
    int left_sum = arr[middle];
    for (int i = middle; i >= left; i--)
    {
        sum = sum + arr[i];
        if (sum > left_sum)
          left_sum = sum;
    }

    sum = 0;
    int right_sum = arr[middle+1];
    for (int i = middle+1; i <= right; i++)
    {
        sum = sum + arr[i];
        if (sum > right_sum)
          right_sum = sum;
    }
    return max3(left_sum + right_sum, left_sum, right_sum);
}

int maxSubArraySum(int arr[], int left, int right)
{
   if (left == right)
     return arr[left];

   // Find middle point
   int m = (left + right)/2;

   /* Return maximum of following three possible cases
      a) Maximum subarray sum in left halfS
      b) Maximum subarray sum in right half
      c) Maximum subarray sum such that the subarray crosses the midpoint */
   return max3(maxSubArraySum(arr, left, m),
              maxSubArraySum(arr, m+1, right),
              maxSumContainingMiddle(arr, left, m, right));
}
