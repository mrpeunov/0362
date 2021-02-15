#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stddef.h>

typedef struct primes
{
    size_t val;
    struct primes *next;
}node;

int add_item(node*,size_t);
int print(node*);
int free_mem(node*);

int main()
{
    int n, res;
    size_t i, j, cnt = 0;
    node *p = (node*)malloc(sizeof(node));
    res = SetConsoleOutputCP(CP_UTF8);
    if (res == 0)
    {
        printf("Ошибка!\n");
        return 1;
    }
    if (p == NULL)
    {
        printf("Ошибка!\n");
        return 2;
    }
    printf("Введите границу поиска простых чисел:");
    res = scanf("%d",&n);
    while (res != 1)
    {
        printf("Со вводом что-то не то, давай по новой:");
        fflush(stdin);
        res = scanf("%d",&n);
    }
    if (n <= 2)
    {
        printf("Я так не играю");
        return 0;
    }
    p->val = 2;
    p->next = NULL;
    for (i = 3; i < n; i+=2)
    {
        for (j = 2; j <= round(sqrt(i)); j++)
        {
            if (i % j == 0)
            {
                cnt++;
                break;
            }
        }
        if (cnt == 0)
        {
            res = add_item(p,i);
            if (res != 0)
            {
                printf("Ошибка!\n");
                return 3;
            }
            cnt = 0;
        }
        else
            cnt = 0;
    }
    res = print(p);
    if (res != 0)
    {
        printf("Ошибка!\n");
        return 4;
    }
    res = free_mem(p);
    if (res != 0)
    {
        printf("Ошибка!\n");
        return 5;
    }
    return 0;
}

int add_item(node *head, size_t value)
{
    node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (node*)malloc(sizeof(node));
    if (current->next == NULL)
        {
            printf("Ошибка!\n");
            return 1;
        }
    current->next->val = value;
    current->next->next = NULL;
    return 0;
}

int print(node *head)
{
    node *current = head;
    size_t count = 0;
    while (current != NULL)
    {
        printf("%zu ",current->val);
        count++;
        if (count >= 25)
        {
            count = 0;
            printf("\n");
        }
        current = current->next;
    }
    return 0;
}

int free_mem(node *head)
{
    node *current = head, *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}
