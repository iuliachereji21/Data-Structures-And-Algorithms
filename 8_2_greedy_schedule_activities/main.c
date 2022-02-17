#include <stdio.h>
#include <stdlib.h>

int n, firsthour, lasthour;
FILE *pfin;
FILE *pfout;
int activities[100][4];

void citire(FILE *pf, int *n, int arr[100][4], int *firsthour, int *lasthour)
{
    int i;
    *firsthour=-1;
    *lasthour=-1;
    fscanf(pf,"%d",n);
    for(i=1;i<=*n;i++)
    {
        arr[i][0]=i;
        fscanf(pf,"%d %d",&arr[i][1],&arr[i][2]);
        arr[i][3]=arr[i][2]-arr[i][1]; //lenght
        if((*firsthour==-1)&&(*lasthour==-1))
        {
            *firsthour=arr[i][1];
            *lasthour=arr[i][2];
        }
        else
        {
            if(arr[i][1]<*firsthour)
                *firsthour=arr[i][1];
            if(arr[i][2]>*lasthour)
                *lasthour=arr[i][2];
        }
    }
}

void order(int n, int arr[100][4]) //care dureaza cel mai putin si care incepe cel mai repede
{
    int i,j;
    int aux;
    for(i=1;i<n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(arr[i][3]>arr[j][3]) //daca dureaza mai putin
            {
                aux=arr[i][0];
                arr[i][0]=arr[j][0];
                arr[j][0]=aux;
                aux=arr[i][1];
                arr[i][1]=arr[j][1];
                arr[j][1]=aux;
                aux=arr[i][2];
                arr[i][2]=arr[j][2];
                arr[j][2]=aux;
                aux=arr[i][3];
                arr[i][3]=arr[j][3];
                arr[j][3]=aux;
            }
            else
            {
                if((arr[i][3]==arr[j][3])&&(arr[i][1]>arr[j][1])) //daca dureaza egal si unul incepe mai repede
                {
                    aux=arr[i][0];
                    arr[i][0]=arr[j][0];
                    arr[j][0]=aux;
                    aux=arr[i][1];
                    arr[i][1]=arr[j][1];
                    arr[j][1]=aux;
                    aux=arr[i][2];
                    arr[i][2]=arr[j][2];
                    arr[j][2]=aux;
                    aux=arr[i][3];
                    arr[i][3]=arr[j][3];
                    arr[j][3]=aux;
                }
            }
        }
    }
}

int verif(int first, int last, int hour[100])
{
    int ok=1;
    int i;
    for(i=first+1;i<=last;i++)
    {
        if(hour[i]==1)
            ok=0;
    }
    return ok;
}

void greedy(int n, int firsthour, int lasthour, int arr[100][4], FILE *pf)
{
    int hour[lasthour+1];
    int programate[n];
    int i, j, k;
    for(i=firsthour+1; i<=lasthour;i++)
    {
        hour[i]=0; //unused
    }
    k=0;
    for(i=1;i<=n;i++)
    {
        if(verif(arr[i][1],arr[i][2],hour)) //o adaugam
        {
            k++;
            programate[k]=arr[i][0];
            for(j=arr[i][1]+1; j<=arr[i][2];j++)
            {
                hour[j]=1; //mark as used
            }
        }
    }
    for(i=1;i<=k;i++)
        fprintf(pf,"%d ",programate[i]);
}

int main(int argc, char* argv[])
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");

    citire(pfin,&n,activities,&firsthour,&lasthour);
    order(n,activities);
    greedy(n, firsthour, lasthour, activities, pfout);

    fclose(pfin);
    fclose(pfout);
    return 0;
}
