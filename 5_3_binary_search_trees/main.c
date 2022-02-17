#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *fin,*fout;

typedef struct N
{
    char name[30];
    float price;
    int amount;
    int dateOfManufacturing;
    int dateOfExpiration;
    struct N* pLeft;
    struct N* pRight;
} Product;

Product*  createnode( char *name, float price, int amount, int dateOfManufacturing, int dateOfExpiration)
{
    Product* p=(Product*)malloc(sizeof(Product));
    if(p)
    {
        strcpy(p->name,name);
        p->price=price;
        p->amount=amount;
        p->dateOfManufacturing=dateOfManufacturing;
        p->dateOfExpiration=dateOfExpiration;
        p->pLeft=p->pRight=NULL;
    }
    return p;
}

Product* insertproduct(Product* pTree, char name[30], float price, int amount, int dateOfManufacturing, int dateOfExpiration)
{
    if(pTree == NULL)
    {
        pTree=createnode(name,price,amount,dateOfManufacturing,dateOfExpiration);
        return pTree;
    }
    if( stricmp(pTree->name,name) == 0)
    {
        fprintf(fout,"Product %s already exists\n",name);
        return pTree;
    }

    if( stricmp(pTree->name,name) < 0)
        pTree->pRight=insertproduct(pTree->pRight,name,price,amount,dateOfManufacturing,dateOfExpiration);
    else
        pTree->pLeft=insertproduct(pTree->pLeft,name,price,amount,dateOfManufacturing,dateOfExpiration);
    return pTree;

}

Product* findproduct(Product* pTree, char *name)
{
    if(pTree == NULL) //empty tree
        return NULL;
    else if( stricmp(pTree->name,name) == 0 )
        return pTree;
    else if ( stricmp(pTree->name,name) < 0)
        return findproduct(pTree->pRight, name);
    else
        return findproduct(pTree->pLeft, name);
}



Product* findMax(Product* pTree)
{
    if(pTree == NULL)
        return NULL;
    else
        if(pTree->pRight)
            return findMax(pTree->pRight);
        else
            return pTree;
}

Product* findMin(Product* pTree)
{
    if(pTree == NULL)
        return NULL;
    else
        if (pTree->pLeft)
            return findMin((pTree->pLeft));
        else
            return pTree;
}

Product* deletenode(Product* pTree, char *name)
{
    if(pTree == NULL)
        fprintf(fout,"Medicine %s not found to delete\n",name);
    else
        if( stricmp(pTree->name,name) < 0) //it must be in the right subtree
            pTree->pRight = deletenode(pTree->pRight,name);
        else
            if( stricmp(pTree->name,name) > 0) //it must be in the left subtree
                pTree->pLeft = deletenode(pTree->pLeft,name);
            else
            {
                //we found node
                // Now We can delete this node and replace with either
                //minimum element in the right sub tree or
                //maximum element in the left subtree
                if( pTree->pRight && pTree->pLeft )
                {
                    Product* temp=findMin(pTree->pRight);

                    strcpy(pTree->name,temp->name);
                    pTree->amount=temp->amount;
                    pTree->dateOfExpiration=temp->dateOfExpiration;
                    pTree->dateOfManufacturing=temp->dateOfManufacturing;
                    pTree->price=temp->price;

                    pTree->pRight=deletenode(pTree->pRight, temp->name);
                    free(temp);
                }
                else
                {
                    // If there is only one or zero children then we can directly
                    // remove it from the tree and connect its parent to its child
                    Product* temp = pTree;
                    if(pTree->pLeft == NULL)
                        pTree = pTree->pRight;
                    else //if(pTree->pRight == NULL)
                        pTree = pTree->pLeft;
                    free(temp); // temp is no longer required
                }
            }
    return pTree;
}

void preorder ( Product *pTree, int level)
{
    int i;
    if(pTree != NULL)
    {
        fprintf(fout,"%s %f %d %d %d \n",pTree->name,pTree->price,pTree->amount,pTree->dateOfManufacturing,pTree->dateOfExpiration);
        preorder( pTree->pLeft, level + 1);
        preorder( pTree->pRight, level + 1);
    }
}

int getDate()
{
        // convert local time to string of form "YYYYMMDD"
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[10];

        time ( &rawtime );
        timeinfo = localtime( &rawtime );
        strftime(buffer, sizeof(buffer), "%Y%m%d", timeinfo);
        int currentDate=atoi(buffer);
        return currentDate;
}

int isExpired(int dateOfExpiration) {
    int currentDate = getDate();
    if(dateOfExpiration < currentDate)
        return 1;
    else
        return 0;
}

void change_product(Product* ptree, Product* ptr, char n1[30], char n2[30], char p2[30], char am2[30], char datem2[30], char datee2[30])
{
    float price;
    int amount, dm, de;

    if(strcmp(p2,"~")!=0)
        price=atof(p2);
    else price=ptr->price;

    if(strcmp(am2,"~")!=0)
        amount=atoi(am2);
    else amount=ptr->amount;

    if(strcmp(datem2,"~")!=0)
        dm=atoi(datem2);
    else dm=ptr->dateOfManufacturing;

    if(strcmp(datee2,"~")!=0)
        de=atoi(datee2);
    else de=ptr->dateOfExpiration;

    if(strcmp(n2,"~")!=0)
    {
        ptree = deletenode(ptree,n1);
        ptree= insertproduct(ptree,n2,price,amount,dm,de);
    }
    else
    {
        ptr->price=price;
        ptr->amount=amount;
        ptr->dateOfManufacturing=dm;
        ptr->dateOfExpiration=de;
    }
}

int main(int argc, char* argv[])
{
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"w");
    if(fin== NULL)
    {
        perror("not found input");
        exit(-1);
    }

    if(fout== NULL)
    {
        perror("not found");
        exit(-1);
    }
    Product *pBST=NULL;
    Product *pFindT=NULL;
    Product *pFindE=NULL;
    Product *pBSTE=NULL;

    char buffer[300];
    char c;
    char name[30];
    float price;
    int amount;
    int dateOfManufacturing;
    int dateOfExpiration;

    char name2[30];
    char price2[30];
    char amount2[30];
    char dm2[30];
    char de2[30];

    while(fgets(buffer,300,fin)!=NULL)
    {
        c=buffer[0];
        strcpy(buffer, buffer+1);
        switch(c)
        {
            case 'i':
                {
                    sscanf(buffer, "%s %f %d %d %d",name,&price,&amount,&dateOfManufacturing,&dateOfExpiration);
                    pBST=insertproduct(pBST,name,price,amount,dateOfManufacturing,dateOfExpiration);
                    if(isExpired(dateOfExpiration) == 1)
                        pBSTE=insertproduct(pBSTE,name,price,amount,dateOfManufacturing,dateOfExpiration);
                } break;
            case 'd':
                {
                    sscanf(buffer, "%s\n",name);
                    pFindT = findproduct(pBST,name);
                    pFindE = findproduct(pBSTE,name);
                    if (pFindT == NULL)
                        fprintf(fout,"Medicine %s not found to delete\n", name);
                    else
                    {
                        pBST=deletenode(pBST,name);
                        fprintf(fout,"Medicine %s deleted from products list\n", name);
                        if ( pFindE != NULL)
                        {
                            pBSTE=deletenode(pBSTE,name);
                            fprintf(fout,"Medicine %s deleted from expired products list\n", name);
                        }
                        fprintf(fout,"\n");
                    }

                } break;
            case 'u':
                {
                    sscanf(buffer,"%s %s %s %s %s %s",name, name2, price2, amount2, dm2, de2);
                    pFindT = findproduct(pBST,name);
                    pFindE = findproduct(pBSTE,name);
                    if ( pFindT == NULL)
                        fprintf(fout,"Medicine %s not found\n\n", name);
                    else
                    {
                        fprintf(fout,"Medicine %s found and modified\n", name);
                        change_product(pBST,pFindT,name,name2,price2,amount2,dm2,de2);
                        if(pFindE!=NULL)
                        {
                            if(strcmp(de2,"~")==0) //if date of expiration doesn't change => it is still expired
                                change_product(pBSTE,pFindE, name, name2, price2, amount2, dm2, de2);
                            else
                            {
                                int datee=atoi(de2);
                                if(isExpired(datee)==0)//not expired anymore
                                {
                                    pBSTE=deletenode(pBSTE, name);
                                    fprintf(fout,"Medicine %s deleted from expired products list because it is not expired anymore\n", name);
                                }
                                else //still expired
                                    change_product(pBSTE,pFindE, name, name2, price2, amount2, dm2, de2);
                            }
                        }
                     }
                     fprintf(fout,"\n");
                 } break;
            case 'p':
                {
                    fprintf(fout,"The products in preorder are:\n");
                    preorder(pBST,0);
                    fprintf(fout,"\n");
                } break;
            case 'P':
                {
                    fprintf(fout,"Expired products are:\n");
                    preorder(pBSTE,0);
                    fprintf(fout,"\n");
                } break;
        }
    }
    return 0;
}
