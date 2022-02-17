
FILE *pfin;
FILE* pfout;

typedef struct node
{
    char key;
    struct node *left, *right;
}nodet;

nodet* createnode(char key1);
nodet* insertn(nodet* root, char key1);
void preorder(nodet*p, int level);
void inorder(nodet*p, int level);
void postorder(nodet*p, int level);
nodet* findn(nodet* p, char key1);
nodet* findmin(nodet* p);
nodet* findmax(nodet* p);
void delnode(nodet* r, char key1);


