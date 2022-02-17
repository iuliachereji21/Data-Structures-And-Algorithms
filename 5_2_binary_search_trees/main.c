#include <stdio.h>
#include <stdlib.h>
#include "module1.h"


char s[10];
nodet* root=NULL;
nodet* f;

int main(int argc, char** argv)
{
    pfin=fopen(argv[1],"r");
    pfout=fopen(argv[2],"w");


    while(fgets(s,4,pfin))
    {
        s[2]='\0';
        //printf("%s a",s);
        switch (s[0])
        {
            case 'i': root=insertn(root,s[1]);
                break;
            case 't':
                {
                    switch(s[1])
                    {
                        case 'p':
                            {
                                fprintf(pfout,"Preorder:\n");
                                preorder(root,0);
                                fprintf(pfout,"\n");
                            }
                            break;
                        case 'P':
                            {
                                fprintf(pfout,"Postorder:\n");
                                postorder(root,0);
                                fprintf(pfout,"\n");
                            }
                            break;
                        case 'i':
                            {
                                fprintf(pfout,"Inorder:\n");
                                inorder(root,0);
                                fprintf(pfout,"\n");
                            }
                            break;
                    }
                }
                break;
            case 'f':
                {
                    f=findn(root,s[1]);
                    if(f==NULL)
                    {
                        fprintf(pfout,"Node %c not found\n",s[1]);
                    }
                    else
                    {
                        fprintf(pfout,"Node %c found\n",s[1]);
                    }
                }
                break;
            case 'g':
                {
                    if(s[1]=='m')
                    {
                        f=findmin(root);
                        if(f==NULL)
                            fprintf(pfout,"Tree empty\n");
                        else
                        {
                            fprintf(pfout,"Node with minimum value = %c\n",f->key);
                        }
                    }
                    else
                    {
                        if(s[1]=='M')
                        {
                            f=findmax(root);
                            if(f==NULL)
                                fprintf(pfout,"Tree empty\n");
                            else
                            {
                                fprintf(pfout,"Node with maximum value = %c\n",f->key);
                            }
                        }

                    }
                }
                break;
            case 'd':
                {
                    f=findn(root,s[1]);
                    if(f==NULL)
                        fprintf(pfout,"Node with key = %c not found to delete\n",s[1]);
                    else
                    {
                        delnode(root, s[1]);
                        fprintf(pfout,"Node with key = %c was deleted\n",s[1]);
                    }
                }
                break;

        }
    }
    return 0;
}
