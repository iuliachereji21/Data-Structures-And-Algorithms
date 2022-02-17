#include "module2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int hashFunction1(char nume[100]) //vowels*consonants
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

int hashFunction2(char nume[100])//vowels*consonants + length of name
{
    int f=hashFunction1(nume);
    int k=0;
    while(nume[k]!='\0')
    {
        k++;
    }
    f=f+k;
    return f;
}
int hashFunction3(char nume[100]) //v*c + difference of first letter and 'A'
{
    int f=hashFunction1(nume) + (nume[0]-'A');
    return f;
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
        p->next=NULL;
        int h1=hashFunction1(s);
        if(table[h1]==NULL) //insert with first function
        {
            table[h1]=p;
            return 0;
        }
        else
        {
            int h2=hashFunction2(s);
            if(table[h2]==NULL) //insert with second fct
            {
                if(strcmp(s,table[h1]->key)==0) //is already in table
                {
                    return 1;
                }
                table[h2]=p;
                table[h1]->next=table[h2];
                return 0;
            }
            else
            {
                int h3=hashFunction3(s);
                if(table[h3]==NULL) //insert with third fct
                {
                    if((strcmp(s,table[h2]->key)==0)||(strcmp(s,table[h1]->key)==0)) //is already in table
                    {
                        return 1;
                    }
                    table[h3]=p;
                    table[h2]->next=table[h3];
                    return 0;
                }
                else return 1; //no slot available
            }
        }
    }
    else return 1; //no memory
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
    int h1=hashFunction1(s);
    if(table[h1]!=NULL)
    {
        if(strcmp(table[h1]->key,s)==0)
            return h1;
    }
    int h2=hashFunction2(s);
    if(table[h2]!=NULL)
    {
        if(strcmp(table[h2]->key,s)==0)
            return h2;
    }
    int h3=hashFunction3(s);
    if(table[h3]!=NULL)
    {
        if(strcmp(table[h3]->key,s)==0)
            return h3;
    }
    else return 0;
}

int deleteName(char s[100])
{
    int f=findname(s);
    int h1=hashFunction1(s);
    int h2=hashFunction2(s);
    int h3=hashFunction3(s);
    if(f)
    {
        cell*p=table[f];
        if(f==h1)
        {
            table[f]=NULL;
            free(p);
            return 1;
        }
        if(f==h2)
        {
            table[h1]->next=NULL;
            table[f]=NULL;
            free(p);
            return 1;
        }
        if(f==h3)
        {
            table[h2]->next=NULL;
            table[f]=NULL;
            free(p);
            return 1;
        }
    }
    else return 0;
}
