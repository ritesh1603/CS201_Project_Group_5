#include<stdio.h>
#include<stdlib.h>
char arry[10000];
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
char chr_index(int index_of_element, struct rope *root)
{
    struct rope *temp = root;

    int a = index_of_element;
    while (1)
    {
        if (temp->right == NULL && temp->left == NULL)
        {
            break;
        }
        else
        {
            if (a > (temp->alp))
            {
                a -= temp->alp;
                a--;
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    return temp->para[a];
}
int index_search(char array[], int count)
{
    printf("enter length of string");
    char string[1000] = {0};
    int length;
    scanf("%d", &length);
    getchar();
    for (int i = 0; i < length; i++)
    {
        scanf("%c", &string[i]);
    }
    
    for (int i = 0; i < count; i++)
    {
        int ans = 0;

        if (array[i] == string[0])
        {
            int count1 = 0;
            while (array[i] == string[count1] && i < count)
            {
                if (count1 == 0)
                {
                    ans = i;
                }
                count1++;
                i++;
            }
            if (count1 == length)
            {
                return ans;
            }
        }
    }
    return -1;
}
struct rope *return_leafnode_at_given_position(int index_of_element, struct rope *root)
{
    struct rope *temp = root;

    int a = index_of_element;
    while (1)
    {
        if (temp->right == NULL && temp->left == NULL)
        {
            break;
        }
        else
        {
            if (a > (temp->alp))
            {
                a -= temp->alp;
                a--;
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
    }
    return temp;
}
