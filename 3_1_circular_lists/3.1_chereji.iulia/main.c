#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* pfin;
FILE* pfout;
int n;
char s[100];
//consideram ca la inceput numaratoarea incepe de la primul copil pt ca nu se specifica altceva
typedef struct node{
        char nume[20];
        struct node* next;
} nodet;

nodet* listptr=NULL;

nodet* insertkid(char name[20])
{
    nodet* ptr=(nodet*)malloc(sizeof(nodet));
    if(ptr)
    {
        strcpy(ptr->nume,name);
        if(listptr==NULL)//empty list
        {
            listptr=ptr;
            ptr->next=ptr;
        }
        else
        {
            nodet*p=listptr;
            while(p->next!=listptr)
            {
                p=p->next;
            }
            p->next=ptr;
            ptr->next=listptr;
        }
    }
    return ptr;
}

void deletenode(nodet*ptr)
{
    nodet* p=listptr;

    while(p->next!=ptr)
    {
        p=p->next;
    }
    p->next=ptr->next;
    if(listptr==ptr)//first node
    {
        listptr=listptr->next;
    }
    free(ptr);
}

int main(int argc, char** argv)
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    fscanf(pfin,"%d%*c",&n);
    while(fgets(s,100,pfin))
    {
        s[strlen(s)-1]='\0';
        insertkid(s);
    }
    nodet* p=listptr;
    int i; //inceput
    while((listptr->next)!=listptr)
    {
        for(i=2;i<n;i++)
        {
            p=p->next;
        }
        deletenode(p->next);
        p=p->next;
    }
    fprintf(pfout,"%s",listptr->nume);
    return 0;
}
