#include <stdio.h>
#include <stdlib.h>
#include "module2.h"
#include <string.h>
/*hash function1 is made by nr_of_vowels * nr_of_consonants because it will make reasonable
different results for different names, same for hash function 2 which adds to the first one
the lenght on the name, and the third adds to first the index of first letter in alphabet*/

FILE* pfin;
FILE* pfout;
int f;

void deleteFirst(char s[100])
{
    int i;
    for(i=0;i<strlen(s)-2;i++)
    {
        s[i]=s[i+1];
    }
    s[i]='\0';
}

int main(int argc, char** argv)
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");
    inittable(table);

    while(fgets(s,100,pfin))
    {
        switch (s[0])
        {
            case 'i':
                {
                    deleteFirst(s);
                    if(insertCell(s))
                    {
                        fprintf(pfout,"Couldn't insert name '%s' into table\n",s);
                    }
                }
                break;
            case 'l':
                {
                    fprintf(pfout,"\n");
                    listtable(pfout);
                    fprintf(pfout,"\n");
                }
                break;
            case 'f':
                {
                    deleteFirst(s);
                    f=findname(s);
                    if(f)
                    {
                        fprintf(pfout,"Yes, name '%s' found at index %d\n",s,f);
                    }
                    else fprintf(pfout,"No, name '%s' not found\n",s);
                }
                break;
            case 'd':
                {
                    deleteFirst(s);
                    if(deleteName(s)==0)
                    {
                        fprintf(pfout,"Name '%s' is not in the table to delete\n",s);
                    }
                    else fprintf(pfout,"Name '%s' deleted\n",s);
                }
                break;
        }
    }
    return 0;
}
