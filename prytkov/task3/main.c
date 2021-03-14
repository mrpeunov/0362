/* https://web.math.princeton.edu/mathlab/jr02fall/Periodicity/alexajp.pdf
 * эта штучка была весьма полезна */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

typedef struct node
{
    int value;
    struct node *next;
}node;

int add_item(node*, int);
int free_memory(node*);
int continued_fraction(int, node*);
int formatted_out(node*);

int main()
{
    int result, n;
    node *list;
    result = SetConsoleOutputCP(CP_UTF8);
    if (result == 0)
    {
        printf ("An error occurred while setting language\n");
        return 1;
    }
    printf("Введите число:");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("С нулем / отрицательным числом работать не интересно\n");
        return 0;
    }
    list = (node*)malloc(sizeof(node));
    if (list == NULL)
    {
        printf("Ошибка!\n");
        return 2;
    }
    for (size_t i = 1; i <= n; i++)
    {
        printf("%zu = ", i);
        result = continued_fraction(i, list);
        if (result != 0)
        {
            printf("Ошибка!\n");
            return 3;
        }
        result = formatted_out(list);
        if (result != 0)
        {
            printf("Ошибка!\n");
            return 4;
        }
        result = free_memory(list);
        if (result != 0)
        {
            printf("Ошибка!\n");
            return 5;
        }
        list = (node*)malloc(sizeof(node));
        if (list == NULL)
        {
            printf("Ошибка!\n");
            return 6;
        }
    }
    free(list);
    return 0;
}

int continued_fraction(int num, node *head)
{
    /* Реализация алгоритма разложения иррационального числа в периодическую цепную дробь
     * аргумент num - целое число, для корня из которого производится разложение
     * аргумент head - указатель на начало списка */
    if (num <= 0)
        /* Если в качестве первого аргумента был был передан 0 или отрицательное число, вернем -1 */
        return -1;
    if (head == NULL)
        /* Если в качестве второго аргумента был передан указатель на нулевой адрес памяти, вернем -2 */
        return -2;
    int result, integer_part, remainder_part[2], denominator[2];
    node  *current = head;
    double root;
    root = sqrt(num);
    integer_part = (int)root;
    if (integer_part == root)
    {
        /* Если число оказалось полным квадратом - дальше что-либо считать не имеет смысла */
        head->value = integer_part;
        head->next = NULL;
        return 0;
    }
    head->value = integer_part;
    head->next = NULL;
    denominator[0] = 1;
    remainder_part[0] = 0;
    do
    {
        remainder_part[1] = denominator[0] * current->value - remainder_part[0];
        denominator[1] = (num - remainder_part[1] * remainder_part[1]) / denominator[0];
        integer_part = (int)(head->value + remainder_part[1]) / denominator[1];
        result = add_item(head, integer_part);
        if (result != 0)
            /* Если по какой-то причине не удалось добавить элемент в список - вернем -2 */
            return -2;
        remainder_part[0] = remainder_part[1];
        denominator[0] = denominator[1];
        current = current->next;
    }
    while (integer_part != 2 * head->value);
    /* Условие выхода из цикла - основывается на следствии 3.3 из теоремы 3(Галуа)(материал, указанный в начале) */
    return 0;
}

int add_item(node *head, int val)
{
    /* Реализация алгоритма добавления нового элемента в конец списка
     * аргумент head - указатель на начало списка
     * аргумент val - числовое значение для нового элемента */

    if (head == NULL)
        /* Если в качестве первого аргумента был передан указатель на нулевой адрес памяти, вернем 1 */
        return 1;
    node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (node*)malloc(sizeof(node));
    if (current->next == NULL)
        /* Если произошла ошибка при выделении памяти под новый узел вернем 2 */
        return 2;
    current->next->value = val;
    current->next->next = NULL;
    return 0;
}

int formatted_out(node *head)
{
    /* Реализация алгоритма вывода итогового разложения в формате [q_1;(g_2; g_3;...)]
     * аргумент head - указатель на начало списка */

    if (head == NULL)
        /* Если в качестве аргумента был передан указатель на нулевой адрес памяти, вернем 1 */
        return 1;
    node *current = head;
    printf("[%d", current->value);
    current = current->next;
    if (current != NULL)
    {
        printf("; (");
        while (1)
        {
            printf("%d", current->value);
            current = current->next;
            if (current == NULL)
                break;
            printf("; ");
        }
        printf(")");
    }
    printf("]\n");
    return 0;
}

int free_memory(node *head)
{
    /* Реализация алгоритма освобождения памяти, занятой списком
     * аргумент head - указатель на начало списка */

    if (head == NULL)
        /* Если в качестве аргумента был передан указатель на нулевой адрес памяти, вернем 1 */
        return 1;
    node *current = head, *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}