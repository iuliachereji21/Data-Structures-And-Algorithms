#include <stdio.h>
#include <stdlib.h>
#include "module3.h"

void citire(int *nrnoduri)
{
    char*s;
    int i,j,nr,found[100];
    for(i=0;i<=99;i++)
    {
        found[i]=0;
        for(j=0;j<=99;j++)
        {
            if(i==j) cost[i][j]=0;
            else cost[i][j]=-1;
        }
    }

    while(fgets(s,100,pfin))
    {
        sscanf(s,"%d,%d=%d",&i,&j,&nr);
        cost[i][j]=nr;
        if(found[i]==0)
        {
            found[i]=1;
            (*nrnoduri)++;
        }
        if(found[j]==0)
        {
            found[j]=1;
            (*nrnoduri)++;
        }
    }
}

void dijkstra(int nrnodes, int inceput, int iteration)
{
    int i,j;
    int terminat=0; //cat timp nu am adaugat toate nodurile
    int dist[nrnodes+1]; //at each step the dist from a vertex already taken to this vertex
    int p[nrnodes+1][nrnodes+1];
    int minpvalue, mini, minj;
    int se_poate_ajunge;
    int it=iteration;
    for(i=1;i<=nrnodes;i++)
    {
        setofnodes[i]=0;
        dist[i]=cost[inceput][i]; //-1 if no edge, 0 if same vertex, cost if there is an edge
        //we will modify dist for every edge when it is added to the tree
        parent[i]=0;
        se_poate_ajunge=0;
        for(j=1;j<=nrnodes;j++)
        {
            p[i][j]=0;
            if((j!=i)&&(cost[j][i]!=-1))
            {
                se_poate_ajunge=1;
            }
        }
        if (se_poate_ajunge==0)
            parent[i]=-1;
    }
    parent[source]=0;
    setofnodes[inceput]=1;
    while(!terminat)
    {
        it++;
        minpvalue=0;
        for(i=1;i<=nrnodes;i++)
        {
            for(j=1;j<=nrnodes;j++)
            {
                if((setofnodes[i]==1)&&(setofnodes[j]==0)&&(cost[i][j]>0)) //i taken, j not taken, there is an edge i-j
                {
                    p[i][j]=dist[i]+cost[i][j];

                    if((p[i][j]<minpvalue)||(minpvalue==0))
                    {
                        minpvalue=p[i][j];
                        mini=i;
                        minj=j;
                    }

                }
                else p[i][j]=0;

            }
        }
        setofnodes[minj]=1;
        dist[minj]=minpvalue; //the new distance
        parent[minj]=mini;
        terminat=1;
        for(i=1;i<=nbnodes;i++)
        {
            if(setofnodes[i]==0) //daca mai exista inca noduri pe care nu le-am adaugat
                terminat=0;
        }
        if(it>=nbnodes) //daca am depasit nr de iteratii inseamna ca nodurile ramase nu pot fi atinse => iesim
        {
            terminat=1;
        }

    }
}

void afisare(int source,int dest)
{
    int noduri[nbnodes+1]; //to put the nodes which are to be printed in reverse order
    int l=0, d=dest, pret=1,i;
    if(source==dest) fprintf(pfout,"0 %d\n",source);
    else
    {
        while(d!=0) //compute total cost and make the array of nodes
        {
            l++;
            noduri[l]=d;
            pret=pret+cost[parent[d]][d];
            d=parent[d];
        }
        fprintf(pfout,"%d %d",pret,noduri[l]);
        for(i=l-1;i>=1;i--)
        {
            fprintf(pfout,"-%d",noduri[i]);
        }
        fprintf(pfout," (%d",cost[noduri[l]][noduri[l-1]]);
        for(i=l-1;i>=2;i--)
        {
            fprintf(pfout,",%d",cost[noduri[i]][noduri[i-1]]);
        }
        fprintf(pfout,")\n");
    }

}
