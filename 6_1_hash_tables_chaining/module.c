#include "module.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int hashFunction(char nume[100])
{
    int i,vowels=0, cons=0;
    for(i=0;i<=strlen(nume)-1;i++)
    {
        if((strchr("AEIOUaeiou",nume[i]))!=NULL)
        {
            vowels+=1;
        }
        else
        {
            if(nume[i]!=' ')
            {
                cons+=1;
            }
        }
    }
    return vowels*cons;
}
void inittable(cell *table[dim])
{
    int i;
    for(i=0;i<dim; i++)
    {
        table[i]=NULL;
    }
}

int insertCell(char s[100])
{
    cell *p=(cell*)malloc(sizeof(cell));
    if(p)
    {
        strcpy(p->key,s);
        int h=hashFunction(s);
        if(table[h]==NULL) //insert first
        {
            table[h]=p;
            p->next=NULL;
            return 0;
        }
        else
        {
            cell*f=table[h];
            while(f!=NULL)
            {
                if(strcmp(f->key,s)==0)//found name
                {
                    return 1;
                    //break;
                }
                f=f->next;
            }
            if(f==NULL)//not found
            {
                p->next=table[h]->next;
                table[h]->next=p;
                return 0;
            }
        }
    }
    else return 1;
        //fprintf(pfout,"Not enough memory to insert name %s in table\n",s);
}
void listtable(FILE* pf)
{
    int i;
    cell* p;
    for(i=0;i<dim;i++)
    {
        if(table[i]!=NULL)
        {
            fprintf(pf,"%d: ",i);
            p=table[i];
            while(p)
            {
                fprintf(pf,"%s, ",p->key);
                p=p->next;
            }
            fprintf(pf,"\n");
        }
    }
}

int findname(char s[100])
{
    int h=hashFunction(s);
    if(table[h]==NULL)
        return 0;
    cell*p=table[h];
    while(p)
    {
        if(strcmp(p->key,s)==0) //found
            return h;
        p=p->next;
    }
    return 0;
}

int deleteName(char s[100])
{
    int f=findname(s);
    if(f)
    {
        cell*p=table[f];
        if(strcmp(p->key,s)==0)//delete first
        {
            table[f]=table[f]->next;
            free(p);
            return 1;
        }
        else
        {
            while(strcmp(p->next->key,s)!=0)
            {
                p=p->next;
            }
            cell*del=p->next;
            p->next=del->next;
            free(del);
            return 1;
        }
    }
    else return 0;
}
