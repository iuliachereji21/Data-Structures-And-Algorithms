#include <stdio.h>
#include <stdlib.h>
//#include <strings.h>
#include <string.h>

typedef struct node{
    char cuv[100];
    int occurances;
    struct node*next;
    struct node*before;
}nodeT;

typedef struct head{
    nodeT*first;
    nodeT*last;
}listT;

int strcompupper(char cuv1[100], char cuv2[100])
{
    int i=0;
    char c1, c2;
    while((cuv1[i]!='\0')&&(cuv2[i]!='\0'))
    {
        c1=cuv1[i];
        c2=cuv2[i];
        if(strchr("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM",c1)==NULL)
            return 1;
        if(strchr("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM",c2)==NULL)
            return -1;

        c1=toupper(c1);
        c2=toupper(c2);
        if(c1<c2)
            return -1;
        if(c1>c2)
            return 1;
        i++;
    }
    if((cuv1[i]=='\0')&&(cuv2[i]=='\0'))
        return 0; //equal
    if(cuv1[i]=='\0')
    {
        return -1;
    }
    return 1;
}

listT* createlist()
{
    listT* plist=(listT*)malloc(sizeof(listT));
    if(plist) //there is space
    {
        plist->first=NULL;
        plist->last=NULL;
    }
    return plist;
}

nodeT* createnode(char cuvant[100])
{
    nodeT* pnode=(nodeT*)malloc(sizeof(nodeT));
    if (pnode)
    {
        strcpy(pnode->cuv,cuvant);
        pnode->next=NULL;
        pnode->before=NULL;
        pnode->occurances=1;
    }
    return pnode;
}

nodeT* search(char cuvant[100], listT* l)
{
    nodeT* ptr=l->first;
    while(ptr!=NULL)
    {
        if((strcompupper(ptr->cuv,cuvant))>=0)
        {
                return ptr;
        }
        ptr=ptr->next;
    }
    return ptr;
}

void afisare(FILE* pfout1, listT* l, int how)
{
    nodeT* ptr;
    if(how)//crescator
    {
        ptr=l->first;
        while(ptr!=NULL)
        {
            fprintf(pfout1,"%s: %d\n",ptr->cuv,ptr->occurances);
            ptr=ptr->next;
        }
    }
    else
    {
        ptr=l->last;
        while(ptr!=NULL)
        {
            fprintf(pfout1,"%s: %d\n",ptr->cuv,ptr->occurances);
            ptr=ptr->before;
        }
    }
}

//void insertInOrder

listT* plist;
char s[200];
char *Cuv;
char cuvant[100];
nodeT* ptr;
nodeT* nou;
int i;

int main(int argc, char** argv)
{
    FILE *pfin=fopen(argv[1],"r");
    FILE *pfout=fopen(argv[2],"w");

    plist=createlist();
    while(fgets(s,1000,pfin))
    {
        Cuv=strtok(s," ");
        while(Cuv!=NULL)
        {
            i=0;
            while((*(Cuv + i)!='\0')&&(*(Cuv + i)!='\n'))
            {
                cuvant[i]= *(Cuv + i);
                i++;
            }
            cuvant[i]='\0';
            ptr=search(cuvant,plist);
            if(ptr==NULL)
            {
                nou=createnode(cuvant);
                if(plist->first==NULL)//empty
                {
                    plist->first=nou;
                    plist->last=nou;
                }
                else //not empty - insert at end
                {
                    plist->last->next=nou;
                    nou->before=plist->last;
                    plist->last=nou;
                }
            }
            else
            {
                if(strcmp(ptr->cuv,cuvant)==0)  //exista cuvantul in lista
                {
                    ptr->occurances++;
                }
                else //am gasit un cuv mai mare
                {
                    nou=createnode(cuvant);
                    if(ptr==plist->first) //trebuie inserat la inceput
                    {
                        ptr->before=nou;
                        nou->next=ptr;
                        plist->first=nou;
                    }
                    else //insert between
                    {
                        nou->next=ptr;
                        nou->before=ptr->before;
                        ptr->before->next=nou;
                        ptr->before=nou;
                    }
                }
            }
            Cuv=strtok(NULL," ");
        }
    }
    fprintf(pfout,"ASCENDING:\n");
    afisare(pfout,plist,1);//crescator
    fprintf(pfout,"\n DESCENDING:\n");
    afisare(pfout,plist,0);

    return 0;
}
