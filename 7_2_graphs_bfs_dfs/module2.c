#include <stdio.h>
#include <stdlib.h>
#include "module2.h"
#include <string.h>

int read_nodes(int graf[100],int l_nume) //return nr of nodes
{
    int j, i=8+l_nume, numar, nr_noduri=0;
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
    nr_noduri++;

    while(nr=strtok(NULL," "))
    {
        j++;
        numar=atoi(nr);
        graf[numar]=1;
        nr_noduri++;
    }
    return nr_noduri;
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

nodet* enqueue(nodet** ptr_coada, int id)
{
    nodet* p=(nodet*)malloc(sizeof(nodet));
    if(p)
    {
        p->label=id;
        p->next=NULL;
        nodet* walker=*ptr_coada;
        if(*ptr_coada==NULL)/*empty*/
        {
            *ptr_coada=p;
        }
        else
        {
            while((walker->next)!=NULL)
            {
                walker=walker->next;
            }
            walker->next=p;
        }
        return p;
    }
    else return NULL;
}

int dequeue(nodet** ptr_coada)
{
    int label=(*ptr_coada)->label;
    nodet* w=*ptr_coada;
    *ptr_coada=(*ptr_coada)->next;
    free(w);
    return label;
}


void breadth_first_traversal(int srcnode)
{
    fprintf(pfout,"Breadth-First Traversal:\n");
    int mark[100];
    int w,i;
    nodet* p_queue=NULL;
    for(i=0;i<=99;i++)
    {
        mark[i]=0;
    }
    mark[srcnode]=1;
    fprintf(pfout,"%d ",srcnode);
    enqueue(&p_queue,srcnode);
    while(p_queue!=NULL)/*not empty*/
    {
        int v=dequeue(&p_queue);
        for(w=0;w<=99;w++)
        {
            if(V[v][w]==1)/*node adj to v*/
            {
                if(mark[w]==0)
                {
                    mark[w]=1;
                    fprintf(pfout,"%d ",w);
                    enqueue(&p_queue,w);
                }
            }
        }
    }
    fprintf(pfout,"\n");
}

nodet* push(nodet** ptr_stiva, int id)
{
    nodet* p=(nodet*)malloc(sizeof(nodet));
    if(p)
    {
        p->label=id;
        p->next=*ptr_stiva;
        *ptr_stiva=p;
        return p;

    }
    else return NULL;
}

int pop(nodet** ptr_stiva)
{
    nodet*p=*ptr_stiva;
    *ptr_stiva=p->next;
    int label=p->label;
    free(p);
    return label;

}

void depth_first_traversal(int srcnode)
{
    fprintf(pfout,"Depth-First Traversal:\n");
    int mark[100];
    int w,i;
    nodet* p_stack=NULL;
    for(i=0;i<=99;i++)
    {
        mark[i]=0;
    }
    mark[srcnode]=1;
    fprintf(pfout,"%d ",srcnode);
    push(&p_stack,srcnode);
    while(p_stack!=NULL)/*not empty*/
    {
        int v=p_stack->label;
        int found=0;
        w=0;
        while((w<=99)&&(found==0)) //cautam noduri adiacente pt adaugat in stiva
        {
            if((V[v][w]==1)&&(mark[w]==0))
            {
                mark[w]=1;
                fprintf(pfout,"%d ",w);
                push(&p_stack,w);
                found=1;
            }
            w++;
        }
        if(found==0) //daca nu am gasit nici un nod nou, dam pop ca sa vedem la altul
        {
            pop(&p_stack);
        }
    }
    fprintf(pfout,"\n");
}

