#include <stdio.h>
#include <stdlib.h>
#include "module.h"
#include <string.h>

void read_nodes(int graf[100],int l_nume)
{
    int j, i=8+l_nume, numar ;
    char s[200], *nr;

    for(j=0;j<=99;j++)
    {
        graf[j]=0;
    }
    fgets(s,i,pfin); //read until first nr
    fgets(s,200,pfin);

    nr=strtok(s," ");
    numar=atoi(nr);
    graf[numar]=1;

    while(nr=strtok(NULL," "))
    {
        j++;
        numar=atoi(nr);
        graf[numar]=1;
    }
}

void read_arcs(int graf_matrice[100][100],int l_nume)
{
    int i,j,n1,n2;
    char s[100], *pereche;
    for(i=0;i<=99;i++)
    {
        for(j=0;j<=99;j++)
        {
            graf_matrice[i][j]=0;
        }
    }
    i=6+l_nume;

    fgets(s,i,pfin);
    while(fscanf(pfin," (%d %d)",&n1,&n2)>0)
    {
        graf_matrice[n1][n2]=1;
    }
}

void afisare()
{
    int i,j,nod;
    fprintf(pfout,"V1 arcs ");
    for(i=0;i<=99;i++)
    {
        if(V1_noduri[i]==1)
        {
            for(j=0;j<=99;j++)
            {
                if((V1_noduri[j]==1)&&(V[i][j]==1))
                {
                    fprintf(pfout,"(%d %d) ",i,j);
                }
            }
        }
    }
}
