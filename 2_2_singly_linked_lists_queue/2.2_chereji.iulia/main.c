#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pfin;
FILE *pfout;
char s[10], nr[5];
int lungime;

typedef struct node {
    int truck_id;
    struct node* next;
} nodeT;

typedef struct Head {
    int count;
    nodeT* first;
    nodeT* last;
} headerList;

headerList* proad;
headerList* pgarage;

headerList* createemptylist()
{
    headerList* hptr=(headerList*)malloc(sizeof(headerList));
    if(hptr)
    {
        hptr->count=0;
        hptr->first=NULL;
        hptr->last=NULL;
    }
    return hptr;
}

nodeT* createnode(int id)
{
    nodeT* p;
    p=(nodeT*)malloc(sizeof(nodeT));
    if(p)
    {
        p->next=NULL;
        p->truck_id=id;
    }
    return p;
}

int getnr(char str[10])
{
    char nr[5];
    char *c=str+2;
    int i=0, j;
    for(j=0;j<=4;j++)
        nr[j]='\0';
    while(*c!=')')
    {
        nr[i]=*c;
        i++;
        c++;
    }
    return atoi(nr);
}

nodeT* isOnRoad(int id)
{
    nodeT* p=proad->first;
    while(p!=NULL)
    {
        if(p->truck_id==id) return p;
        else p=p->next;
    }
    return p;
}

int insertRoad(headerList* pr, int id) //queue
{
    nodeT* p=createnode(id);
    if(p)
    {
        pr->count++;
        if(pr->first==NULL)//if empty list
        {
            pr->first=p;
            pr->last=p;
        }
        else
        {
            pr->last->next=p;
            pr->last=p;
        }
        return 1;
    }
    else return 0; //failure no memory
}

void deleteNodeRoad(nodeT* pnode)
{
    proad->count--;
    nodeT* p=proad->first;
    if(p==pnode)//first
    {
        proad->first=p->next;
    }
    else
    {
        while(p->next!=pnode)
            p=p->next;
        p->next=pnode->next;
        if(proad->last==pnode) proad->last=p;
    }
    free(pnode);
}

int entergarage(headerList* pg, int id) //stack
{
    if (isOnRoad(id)!=NULL)
    {
        deleteNodeRoad(isOnRoad(id));
        nodeT* p=createnode(id);
        if(p)
        {
            pg->count++;
            if(pg->first==NULL) //if empty list
            {
                pg->first=p;
                pg->last=p;
            }
            else
            {
                pg->last->next=p;
                pg->last=p;
            }
            return 1;
        }
        return 0; //no memory
    }
    else
    {
        fprintf(pfout,"error: %d not on road!\n",id);
        return 0;
    }
}
void exitgarage(int id)
{
    if(pgarage->first->truck_id!=id)
        fprintf(pfout,"error: %d not at exit!\n",id);
    else
    {
        pgarage->count--;
        nodeT*p=pgarage->first;
        pgarage->first=p->next;
        if(p->next==NULL) pgarage->last=NULL; //daca era singurul nod
        free(p);
        insertRoad(proad,id);
    }
}
void show(headerList*plist, char c)
{
    nodeT* p=plist->first;
    fprintf(pfout,"%c:",c);
    if(p==NULL) fprintf(pfout," none");
    else
        while(p!=NULL)
        {
            fprintf(pfout," %d",p->truck_id);
            p=p->next;
        }
    fprintf(pfout,"\n");
}

int main()
{
    pfin=fopen("data2_2.in","r");
    pfout=fopen("data2_2.out","w");

    proad=createemptylist();
    pgarage=createemptylist();

    while(fgets(s,10,pfin))
    {
        if(s[0]=='R') insertRoad(proad,getnr(s));
        else
            if(s[0]=='E') entergarage(pgarage,getnr(s));
            else
                if(s[0]=='S')
                {
                    if(s[2]=='R') show(proad,'R');
                    if(s[2]=='G') show(pgarage,'G');
                }
                else
                    if(s[0]=='X') exitgarage(getnr(s));
    }
    return 0;
}
