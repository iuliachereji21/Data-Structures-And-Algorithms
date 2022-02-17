//should be better if you can take items by parts

#include <stdio.h>
#include <stdlib.h>

FILE *pfin;
FILE *pfout;
int n, W;
int arrItems[100][3];
void citire(FILE* pf, int *nrit, int *weight, int arr[100][3])
{
    int i;
    fscanf(pf, "%d %d", nrit, weight);
    for(i=1;i<=*nrit;i++)
    {
        fscanf(pf,"%d %d %d",&arr[i][0],&arr[i][1],&arr[i][2]);
    }
}

void sortArr(int n, int arr[100][3])
{
    int i, j, auxVal, auxWeight, auxNr;
    for(i=1; i<n; i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(((double)arr[i][1]/(double)arr[i][2])<((double)arr[j][1]/(double)arr[j][2])) //sort decreasing by value/item
            {
                auxWeight=arr[i][0];
                auxVal=arr[i][1];
                auxNr=arr[i][2];
                arr[i][0]=arr[j][0];
                arr[i][1]=arr[j][1];
                arr[i][2]=arr[j][2];
                arr[j][0]=auxWeight;
                arr[j][1]=auxVal;
                arr[j][2]=auxNr;
            }
            else
            {
                if(((double)arr[i][1]/(double)arr[i][2])==((double)arr[j][1]/(double)arr[j][2]))
                {
                    if(((double)arr[i][0]/(double)arr[i][2])>((double)arr[j][0]/(double)arr[j][2])) //sort increasing by weight/item
                    {
                        auxVal=arr[i][1];
                        auxWeight=arr[i][0];
                        auxNr=arr[i][2];
                        arr[i][0]=arr[j][0];
                        arr[i][1]=arr[j][1];
                        arr[i][2]=arr[j][2];
                        arr[j][0]=auxWeight;
                        arr[j][1]=auxVal;
                        arr[j][2]=auxNr;
                    }
                }
            }
        }
    }
}

void greedy(int n, int w, int arr[100][3], FILE *pf)
{
    int weight=0;
    int value=0;
    int i=0;
    int nrToTake, weightPerItem, valPerItem;
    while((weight<w)&&(i<n))
    {
        i++;
        if(arr[i][2]==1) //can only take as a whole
        {
            if(arr[i][0]<=(w-weight)) //can add to solution
            {
                value+=arr[i][1];
                weight+=arr[i][0];
            }
        }
        else //can take parts
        {
            weightPerItem = (int)((double)arr[i][0]/(double)arr[i][2]);
            valPerItem = (int)((double)arr[i][1]/(double)arr[i][2]);
            nrToTake=0;
            while((nrToTake<arr[i][2])&&(w-weight-weightPerItem>=0))
            {
                nrToTake+=1;
                weight+=weightPerItem;
                value+=valPerItem;
            }
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
    //printf("%d",arrItems[6][0]);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
