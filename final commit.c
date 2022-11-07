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
void print(struct rope *r)
{
    if (r == NULL)
    {
        return;
    }
    if (r->left == NULL && r->right == NULL)
    {
        int i = 0;
        while (i < r->coumt)
        {
            printf("%c", r->para[i]);
            i++;
        }
    }
    print(r->left);
    print(r->right);
}
void concat(struct rope **root3, struct rope *root2, struct rope *root1, int n1)
{
    struct rope *temp = (struct rope *)malloc(sizeof(struct rope));
    temp->parent = NULL;
    temp->left = root2;
    temp->right = root1;
    root1->parent = temp;
    root2->parent = temp;
    temp->alp = n1 - 1;
    temp->para = NULL;
    *root3 = temp;
}
int countr = 0;
void rebalance(struct rope *r, char time[])
{

    if (r == NULL)
    {
        return;
    }
    if (r->left == NULL && r->right == NULL)
    {
        int i = 0;
       // printf("hm%d",r->coumt);
        while (i < r->coumt)
        {   //printf("%c",r->para[i]);
            time[countr] = r->para[i];
            countr++;
            i++;
        }
    }
    rebalance(r->left, time);
    rebalance(r->right, time);
}
void blance(struct rope *r, char time[], struct rope **root1)
{
    countr = 0;
    //printf("han");
    rebalance(r, time);
    //printf("%d",countr);
    construct_rope(root1, NULL, time, 0, countr - 1);
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
    // for(int i=0;i<length;i++){
    //     printf("%c\n",string[i]);
    // }
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
                    //  printf("yo\n");
                }
                count1++;
                i++;
            }
            if (count1 == length)
            {
                // printf("hello");
                return ans;
            }
        }
    }
    return -1;
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
int main()
{

    FILE *fptr;
    fptr = fopen("example.txt", "r");
    char k;
    char c;
    int count = 0;

    while ((c = fscanf(fptr, "%c", &k)) != EOF)
    {
        // array[count]=k;
        count++;
    }
    fclose(fptr);
    char array[count];
    FILE *fr;
    fr = fopen("example.txt", "r");
    int i = 0;
    while ((c = fscanf(fr, "%c", &k)) != EOF)
    {
        array[i] = k;
        i++;
    }
    struct rope *root = NULL;
    construct_rope(&root, NULL, array, 0, count - 1);
    FILE *fptr1;
    fptr1 = fopen("name.txt", "r");
    char k1;
    char c1;
    int count1 = 0;

    while ((c1 = fscanf(fptr1, "%c", &k1)) != EOF)
    {
        // array[count]=k;
        count1++;
    }
    fclose(fptr1);
    char array1[count1];
    FILE *fr1;
    fr1 = fopen("name.txt", "r");
    int i1 = 0;
    while ((c1 = fscanf(fr1, "%c", &k1)) != EOF)
    {
        array1[i1] = k1;
        i1++;
    }
    struct rope *root1 = NULL;
    construct_rope(&root1, NULL, array1, 0, count1 - 1);
    // print(root);
    // print(root1);
    printf("what do you want to perform: \n");
    printf("1.Print the rope\n2.concateate two ropes\n3.delete a string\n4.find and replace\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        print(root);
    }
    else if (choice == 2)
    {
        struct rope *newnode = (struct rope *)malloc(sizeof(struct rope));
        concat(&newnode, root1, root, count1 - 1);
        char time[10000] = {0};
        blance(newnode, time, &newnode);
        print(newnode);
    }
    else if (choice == 3)
    {
       
        printf("enter the length of string: ");
        int size;
        scanf("%d", &size);
        getchar();
        int val = index_search(array, count);
        struct rope *newnode = (struct rope *)malloc(sizeof(struct rope));
        struct rope *new = (struct rope *)malloc(sizeof(struct rope));

        new = Split_rope(&root, val, &newnode);
        char time[10000] = {0};
        blance(new, time, &new);
        for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(root, time, &root);
        struct rope *newnode1 = (struct rope *)malloc(sizeof(struct rope));
        struct rope *new1 = (struct rope *)malloc(sizeof(struct rope));
        new1 = Split_rope(&new, size, &newnode1);
        for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(new1, time, &new1);
        struct rope *newnode2 = (struct rope *)malloc(sizeof(struct rope));
        concat(&newnode2, root, new1, count-val-size);
        for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(newnode2, time, &newnode2);
        
       
        print(newnode2);
    }
    else if(choice==4){

        printf("enter the length of string: ");
        int size;
        scanf("%d", &size);
        getchar();
        int val = index_search(array, count);
        struct rope *newnode = (struct rope *)malloc(sizeof(struct rope));
        struct rope *new = (struct rope *)malloc(sizeof(struct rope));

        new = Split_rope(&root, val, &newnode);
        char time[10000] = {0};
        blance(new, time, &new);
        for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(root, time, &root);
        struct rope *newnode1 = (struct rope *)malloc(sizeof(struct rope));
        struct rope *new1 = (struct rope *)malloc(sizeof(struct rope));
        new1 = Split_rope(&new, size, &newnode1);
        for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(new1, time, &new1);
        //print(new1);
        printf("enter the length of string(you want to replace it wih): ");
        int size1;
        scanf("%d",&size1);
        getchar();
        char ar[size1];
        for(int i=0;i<size1;i++){
            scanf("%c",&ar[i]);
        }
        struct rope *newnode2 = (struct rope *)malloc(sizeof(struct rope));
        construct_rope(&newnode2, NULL, ar, 0, size1-1);
        struct rope *newnode3 = (struct rope *)malloc(sizeof(struct rope));
        concat(&newnode3, root, newnode2, count-val);
         for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(newnode3, time, &newnode3);
        //print(newnode3);
        struct rope *newnode4 = (struct rope *)malloc(sizeof(struct rope));
        concat(&newnode4, newnode3, newnode1, count-val);
         for (int i = 0; i < 10000; i++)
        {
            time[i] = 0;
        }
        blance(newnode4, time, &newnode4);
        print(newnode4);

    }
    

    return 0;
}