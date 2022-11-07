#include<stdio.h>
#include<stdlib.h>
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