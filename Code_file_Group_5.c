#include<stdio.h>
#include<stdlib.h>
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
struct node *Split_rope(struct rope **root, int index, struct rope **newnode)
{
    int flag = 0;
    struct rope *str = return_leafnode_at_given_position(index, *root);
    char f = chr_index(index, *root);
    // printf("%c",f);
    struct rope *temp;
    int pos;
    if (str->para[0] == f)
    { // printf("yes");
        flag = 1;
        temp = str;
    }
    if (str->para[0] != f)
    {
        for (int j = 0; j < str->coumt; j++)
        {
            if (str->para[j] == f)
            {
                pos = j;
                break;
            }
        }
        // printf("alp is %d",str->alp);
        int n = str->alp;
        // str->alp=pos-1;
        char *aay = (char *)malloc(pos * sizeof(char));
        char *aay1 = (char *)malloc((n - pos + 1) * sizeof(char));
        ;
        for (int i = 0; i < pos; i++)
        {
            aay[i] = str->para[i];
        }
        for (int i = pos; i <= n; i++)
        {
            aay1[i - pos] = str->para[i];
        }
        struct rope *t1 = (struct rope *)malloc(sizeof(struct rope));
        struct rope *t2 = (struct rope *)malloc(sizeof(struct rope));
        t1->left = NULL;
        t1->right = NULL;
        t2->left = NULL;
        t2->right = NULL;
        str->left = t1;
        str->right = t2;
        str->para = NULL;
        str->left->para = aay;
        str->left->alp = pos - 1;
        str->left->coumt = pos;
        str->right->alp = (n - pos);
        str->right->coumt = (n - pos) + 1;
        str->right->para = aay1;
        str->alp = pos - 1;
        t1->parent = str;
        t2->parent = str;
        temp = str->right;
    }
    int number = 0;
    number = temp->coumt;
    struct rope *m;
    struct rope *s;
    m = temp->parent;
    if (flag != 1)
    {
       // printf("no");
        m->right = NULL;
    }
    if (flag == 0)
    {  // printf("no1");
        s = temp;
        *newnode = temp;
    }
    else
    {    //printf("no2");
        s = temp->parent;
        *newnode = temp->parent;
        if (m != NULL)
        {
            if (temp ==temp->parent->right)
            {
                s = temp;
                *newnode = temp;
                m->right=NULL;
            }
            else
            {
                //printf("hi");
                struct rope *new1 = (struct rope *)malloc(sizeof(struct rope));
                if(m->right==NULL){
                    printf("yess");
                }
                concat(&new1, temp, temp->parent->right, temp->coumt);
                m->right = NULL;
                m->left=NULL;
                // if(temp->parent==(*newnode)){
                //     printf("yo");
                // }
                m->coumt = 0;
                s = new1;
                
                //print(new1);
                *newnode = new1;
                //print(*root);
            }
        }
        else
        {   //printf("yo");
            *root = NULL;
            s = temp;
            *newnode = temp;
        }
    }

    while (m != root && m != NULL)
    {
        if (m->parent != NULL && m == m->parent->left)
        {
            if (m->parent->right != NULL)
            {
                struct rope *new = (struct rope *)malloc(sizeof(struct rope));
                concat(&new, s, m->parent->right, number);
                s = new;
                m->parent->alp = m->parent->alp - number + 1;
                struct rope *l = m->parent->right;
                m->parent->right = NULL;
                while (l != NULL)
                {
                    number = number + l->alp + 1;
                    l = l->right;
                }
                *newnode = new;
            }
        }
        m = m->parent;
    }

    return *newnode;
}
