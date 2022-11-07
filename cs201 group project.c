#include <stdio.h>
#include <stdlib.h>
char arry[10000];
struct rope
{
    struct rope *left, *right, *parent;
    int alp;
    char *para;
    int coumt;
};
void construct_rope(struct rope **root, struct rope *par, char array[], int lft, int rht)
{

    struct rope *temp = (struct rope *)malloc(sizeof(struct rope));
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = par;
    if (rht - lft > 4)
    {
        // printf("hell");
        temp->para = NULL;
        temp->alp = (rht - lft) / 2;
        //temp->coumt=0;
        (*root) = temp;
        int n = (rht + lft) / 2;
        construct_rope(&((*root)->left), *root, array, lft, n);
        construct_rope(&((*root)->right), *root, array, n + 1, rht);
    }
    else
    {
        // printf("hello");
        *root = temp;
        temp->alp = rht - lft;
        // if(rht<lft){
        //     temp=NULL;
        //     return;
        // }
        int j = 0;
        char *ans = (char *)malloc(4 * sizeof(char));
        temp->para = ans;
        // for(int i=0;i<4;i++){
        //     ans[i]=0;
        // }
        temp->coumt = rht - lft + 1;
        for (int i = lft; i <= rht; i++)
        {
            ans[j] = array[i];
            j++;
        }
    }
}