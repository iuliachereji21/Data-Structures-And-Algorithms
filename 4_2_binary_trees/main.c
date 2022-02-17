#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int id;
    struct node *left, *right;
} nodet;

nodet* createBinTree(int branch, nodet* parent)
{
    nodet*p;
    int id1;
    if(branch==0)
        printf("root identifier= ");
    else
        if(branch==1)
            printf("left child of %d = ",parent->id);
        else
            if(branch==2)
                printf("right child of %d = ",parent->id);

    scanf("%d",&id1);
    if(id1==0)
            return NULL;
    p=(nodet*)malloc(sizeof(nodet));
    if(p)
    {
        p->id=id1;
        p->left=createBinTree(1,p);
        p->right=createBinTree(2,p);
    }
    return p;
}
void preorder(nodet *p, int level)
{
    if(p!=NULL)
    {
        int i;
        for(i=0;i<=level;i++) printf(" ");
        printf("%d",p->id);
        preorder(p->left, level+1);
        preorder(p->right,level+1);
    }
}

void inorder(nodet *p, int level)
{
    if(p!=NULL)
    {
        inorder(p->left, level+1);
        int i;
        for(i=0;i<=level;i++) printf(" ");
        printf("%d",p->id);
        inorder(p->right,level+1);
    }
}

void postorder(nodet *p, int level)
{
    if(p!=NULL)
    {
        postorder(p->left, level+1);
        postorder(p->right,level+1);
        int i;
        for(i=0;i<=level;i++) printf(" ");
        printf("%d",p->id);
    }
}

int maxim(int a, int b)
{
    if(a>=b) return a;
    else return b;
}

int height(nodet *p, int h)
{
    if(p==NULL) return h-1;
    else return maxim(height(p->left,h+1), height(p->right,h+1));

}

int nrOfLeaves(nodet *p)
{
    if(p==NULL) return 0;
    if((p->left==NULL)&&(p->right==NULL)) return 1;
    else return (nrOfLeaves(p->left)+nrOfLeaves(p->right));
}

nodet *choose(nodet* a, nodet* b)
{
    if(a==NULL) return b;
    else return a;
}

nodet* search(nodet* p, int ids)
{
    if(p==NULL) return NULL;
    if(p->id==ids) return p;
    return choose(search(p->left,ids),search(p->right,ids));
}

void interchange(nodet*p)
{
    nodet* aux=p->left;
    p->left=p->right;
    p->right=aux;
}

void options()
{
    printf("\nOPTIONS: pr = traversal in preorder, i = inorder, po = postorder, h = height of tree, l = nr of leaves,\nc'NR' = interchange NR's children, o = show options, z = end of program\noperation: ");
}

int nr;
nodet* ptrsearch;
int main()
{
    printf("you have to give tree's nodes identifiers as distinct integer numbers in preorder\nput 0 (zero) if no node\n\n");
    nodet *root=createBinTree(0,NULL);
    fflush(stdin);
    options();
    char c;
    while((c=getch())!='\n')
    {
        printf("%c",c);
        switch(c)
        {
            case 'p':
                {
                    c=getch();
                    if(c=='r')
                    {
                        printf("r\n");
                        preorder(root,0);
                        printf("\noperation: ");
                    }
                    else if(c=='o')
                    {
                        printf("o\n");
                        postorder(root,0);
                        printf("\noperation: ");
                    }
                } break;
            case 'i':
                {
                    printf("\n");
                    inorder(root,0);
                    printf("\noperation: ");
                } break;
            case 'h':
                {
                    printf("\n");
                    printf("%d",height(root,0));
                    printf("\noperation: ");
                } break;
            case 'l':
                {
                    printf("\n");
                    printf("%d",nrOfLeaves(root));
                    printf("\noperation: ");
                } break;
            case 'c':
                {
                    scanf("%d",&nr);
                    if(ptrsearch=search(root,nr))
                    {
                        interchange(ptrsearch);
                        printf("\nchildren of %d have been interchanged\noperation: ",nr);
                    }
                    else printf("\nthe node doesn't exist\n");
                } break;
            case 'o': options(); break;
            case 'z': exit(0);
        }
    }

    return 0;
}
