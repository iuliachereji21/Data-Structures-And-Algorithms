#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int n, W;
int arrItems[100][2]; //arr0 = weight, arr1 = value
void citire(FILE* pf, int *nrit, int *weight, int arr[100][2])
{
    int i;
    fscanf(pf, "%d %d", nrit, weight);
    for(i=1;i<=*nrit;i++)
    {
        fscanf(pf,"%d %d",&arr[i][0],&arr[i][1]);
    }
}

void sortArr(int n, int arr[100][2])
{
    int i,j,auxVal,auxWeight;
    for(i=1; i<n; i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(arr[i][1]<arr[j][1]) //sort decreasing by value
            {
                auxVal=arr[i][1];
                auxWeight=arr[i][0];
                arr[i][0]=arr[j][0];
                arr[i][1]=arr[j][1];
                arr[j][0]=auxWeight;
                arr[j][1]=auxVal;
            }
        }
    }
}

void greedy(int n, int w, int arr[100][2], FILE *pf)
{
    int weight=0;
    int value=0;
    int i=0;
    while((weight<w)&&(i<n))
    {
        i++;
        if(arr[i][0]<=(w-weight)) //can add to solution
        {
            value+=arr[i][1];
            weight+=arr[i][0];
        }
    }
    fprintf(pf,"Total weight: %d Total value: %d",weight,value);
}

int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    citire(pfin, &n, &W, arrItems);
    sortArr(n,arrItems);
    greedy(n,W,arrItems,pfout);


    fclose(pfin);
    fclose(pfout);
    return 0;
}
