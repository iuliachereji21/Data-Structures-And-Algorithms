#include <stdio.h>
#include <stdlib.h>

#include "module1.h"

nodet* createnode(char key1)
{
    nodet* p=(nodet*)malloc(sizeof(nodet));
    if(p)
    {
        p->key=key1;
        p->left=NULL;
        p->right=NULL;
    }
    return p;
}

nodet* insertn(nodet* root, char key1)
{
    if(root==NULL)
    {
        root=createnode(key1);
    }
    else
    {
        if(key1<root->key)
        {
            root->left=insertn(root->left,key1);
        }
        else
        {
            if(key1>root->key)
            {
                root->right=insertn(root->right,key1);
            }
            else printf("\nNode with key = %c already exists\n",key1);
        }

    }
   return root;
}

void preorder(nodet*p, int level)
{
    int i;
    if(p!=NULL)
    {
        for(i=0;i<=level;i++)
            fprintf(pfout," ");
        fprintf(pfout,"%c",p->key);
        preorder(p->left,level+1);
        preorder(p->right,level+1);
    }
}

void inorder(nodet*p, int level)
{
    int i;
    if(p!=NULL)
    {
        inorder(p->left,level+1);
        for(i=0;i<=level;i++)
            fprintf(pfout," ");
        fprintf(pfout,"%c",p->key);
        inorder(p->right,level+1);
    }
}

void postorder(nodet*p, int level)
{
    int i;
    if(p!=NULL)
    {
        postorder(p->left,level+1);
        postorder(p->right,level+1);
        for(i=0;i<=level;i++)
            fprintf(pfout," ");
        fprintf(pfout,"%c",p->key);

    }
}

nodet* findn(nodet* p, char key1)
{
    if(p==NULL)
    {
        return p;
    }
    else
    {
        if(key1<p->key)
        {
            return findn(p->left,key1);
        }
        else
        {
            if(key1>p->key)
            {
                return findn(p->right,key1);
            }
            else return p;
        }
    }
}

nodet* findmin(nodet* p)
{
    if(p==NULL)
    {
        return NULL;
    }
    if(p->left)
    {
        return findmin(p->left);
    }
    else
    {
        return p;
    }
}

nodet* findmax(nodet* p)
{
    if(p==NULL)
    {
        return NULL;
    }
    if(p->right)
    {
        return findmax(p->right);
    }
    else
    {
        return p;
    }
}

nodet* findprec(nodet *p, char key1)
{
    if(p==NULL) return NULL;
    if(key1<p->key)
    {
        if(p->left!=NULL)
        {
            if(p->left->key==key1) return p;
            else return findprec(p->left,key1);
        }
        else return NULL;
    }
    else
    {
        if(key1>p->key)
        {
            if(p->right!=NULL)
            {
                if(p->right->key==key1) return p;
                else return findprec(p->right,key1);
            }
            else return NULL;
        }
        else return p; // p has key==key1
    }
}

void delnode(nodet* r, char key1)
{
        nodet*p=findn(r,key1);
        nodet*f;
        if(p->left&&p->right)
        {
            f=findmin(p->right);
            char c=f->key;
            delnode(r,f->key);
            p->key=c;
        }
        else
        {
            nodet* nod=findprec(r, p->key);
            if((p->left==NULL)&&(p->right==NULL))
            {

                if(nod->left==p)
                {
                    nod->left=NULL;
                    free(p);
                }
                else
                {
                    if(nod->right==p)
                    {
                        nod->right=NULL;
                        free(p);
                    }
                    else //nod==p
                    {
                        r=NULL;
                        free(p);
                    }

                }
            }
            else //node has 1 child
            {
                if(nod->left==p)
                {
                    if(p->left==NULL)
                        nod->left=p->right;
                    else nod->left=p->left;
                }
                else
                {
                    if(nod->right==p)
                    {
                        if(p->left==NULL)
                        nod->right=p->right;
                        else nod->right=p->left;
                    }
                    else //nod==p
                    {
                        if(p->left!=NULL)
                        {
                            r=p->left;
                        }
                        else r=p->right;
                    }
                }

                free(p);
            }
        }
}
