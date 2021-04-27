#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *next;
}node;

node **generate_all_subsets(int*, int, int*);
int output_k_element_subsets(int*, int, int, node**, int count);
int output_subsets_with_element(int*, int, int, node**, int count);
bool contains_element(node*, int);
int output_set(int*, int);
int output_subsets(node**, int);
int *create_set(int);
int get_length(node*);
node *add_item(node*, int);
void hint();

int main()
{
    int *set = NULL, length, result, command, k, count_of_subsets, element;
    node **subsets = NULL;
    result = SetConsoleOutputCP(CP_UTF8);
    if (result == 0)
    {
        printf("An error occurred while setting language\n");
        return 1;
    }
    hint();
    printf("Введите мощность вашего множества: ");
    scanf("%d", &length);
    while (length < 0)
    {
        printf("Мощность должна быть положительным числом!\nДавайте по новой: ");
        scanf("%d", &length);
    }
    set = create_set(length);
    if (set == NULL)
    {
        printf("Произошла ошибка!\n");
        return 2;
    }
    system("cls");
    hint();
    printf("Ваше множество: ");
    result = output_set(set, length);
    if (result != 0)
    {
        printf("Произошла ошибка!\n");
        return 3;
    }
    printf("Введите команду: ");
    scanf("%d", &command);
    switch (command)
    {
        case 0:
            return 0;
        case 1:
        {
            printf("Введите мощность генерируемых множеств: ");
            scanf("%d", &k);
            output_k_element_subsets(set, length, k, subsets, count_of_subsets);
            break;
        }
        case 2:
        {
            printf("Подмножества вашего множества:\n");
            subsets = generate_all_subsets(set, length, &count_of_subsets);
            if (subsets == NULL)
                return 5;
            output_subsets(subsets, count_of_subsets);
            break;
        }
        case 3:
        {
            printf("Введите элемент: ");
            scanf("%d", &element);
            printf("Подмножества, содержащие этот элемент:\n");
            output_subsets_with_element(set, length, element, subsets, count_of_subsets);
            break;
        }
        default:
        {
            printf("Таких команд я не знаю =(");
            return 0;
        }
    }
    return 0;
}

int output_subsets_with_element(int *set, int length, int element, node **subsets, int count)
{
    /* Realisation of algorithm, which outputs subsets with entered element
    * argument set - set (array of integers)
    * argument length - length of set array
    * argument element - entered element
    * argument subsets - array of lists with subsets
    * argument count - count of all subsets
    * Upon successful completion function shall output all subsets with entered element */

    node *current;
    if (set == NULL || subsets == NULL)
        subsets = generate_all_subsets(set, length, &count);
    for (size_t i = 0; i < count; i++)
    {
        if (contains_element(subsets[i], element))
        {
            current = subsets[i];
            printf("{ ");
            while (current != NULL)
            {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("}\n");
        }
    }
}

int output_k_element_subsets(int *set, int length, int k, node **subsets, int count)
{
    /* Realisation of algorithm, which outputs subsets with k elements
     * argument set - set (array of integers)
     * argument length - length of set array
     * argument k - length of generating subsets
     * argument subsets - array of lists with subsets
     * argument count - count of all subsets
     * Upon successful completion function shall output all subsets with k elements
     * Otherwise, a NULL pointer shall be returned */

    node *current;
    if (set == NULL || subsets == NULL)
        subsets = generate_all_subsets(set, length, &count);
    for (size_t i = 0; i < count; i++)
    {
        if (get_length(subsets[i]) == k)
        {
            current = subsets[i];
            if ((current->value == 0) &&  k == 1)
                continue;
            printf("{ ");
            while (current != NULL)
            {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("}\n");
        }
    }
    return 0;
}

node **generate_all_subsets(int *set, int length, int *count)
{
    /* Realisation of algorithm, which generates all subsets of set
     * argument set - set, array of integers
     * argument length - length of array (set)
     * argument count - pointer to return count of subsets
     * Upon successful completion function shall return array of lists with all subsets
     * Otherwise, NULL shall be returned */

    if (set == NULL)
        return NULL;
    if (length < 0)
        return NULL;
    *count = (int)pow(2, length);
    node **list_of_subsets = (node**)malloc(sizeof(node*) * (*count));
    for (size_t i = 0; i < *count; i++)
    {
        list_of_subsets[i] = NULL;
        for (size_t j = 0; j < *count; j++)
            if (i & (1 << j))
                list_of_subsets[i] = add_item(list_of_subsets[i], set[j]);
        if (list_of_subsets[i] == NULL)
        {
            list_of_subsets[i] = (node*)malloc(sizeof(node));
            list_of_subsets[i]->value = 0;
            list_of_subsets[i]->next = NULL;
        }
    }
    return list_of_subsets;
}

int output_subsets(node **subsets, int count)
{
    /* Realisation of algorithm, outputs all subsets of set
     * argument subsets - array of lists with all subsets
     * Upon successful completion function shall return 0
     * If argument subsets is NULL-pointer, 1 shall be returned */

    node *current;
    if (subsets == NULL)
        return 1;
    for (size_t i = 0; i < count; i++)
    {
        current = subsets[i];
        printf("{ ");
        if (current == NULL)
        {
            printf("}\n");
            continue;
        }
        while (current != NULL)
        {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("}\n");
    }
    return 0;
}

int *create_set(int length)
{
    /* Realisation of algorithm, which creates set
     * argument length - count of set elements
     * Upon successful completion function shall return set (array of integers)
     * If an error occurred  while allocating memory, NULL shall be returned */
    int *set = (int*)malloc(sizeof(int) * length);
    if (set == NULL)
        return NULL;
    for (int i = 0; i < length; i++)
        set[i] = i + 1;
    system("cls");
    return set;
}

int output_set(int *set, int length)
{
    /* Realisation of formatted set output
     * argument set - array of set elements
     * argument length - array length
     * Upon successful completion function shall return 0
     * If argument set is NULL-pointer, 1 shall be returned
     * If argument length <= 0, 2 shall be returned */

    if (set == NULL)
        return 1;
    if (length <= 0)
        return 2;
    printf("{%d", set[0]);
    for (size_t i = 1; i < length; i++)
        printf(", %d", set[i]);
    printf("}\n");
    return 0;
}

int get_length(node *head)
{
    /* Realisation of algorithm, which gets list length
     * argument head - pointer to first node
     * Upon successful completion function shall return length of list
     * If argument head is NULL-pointer, -1 shall be returned */
    if (head == NULL)
        return -1;
    int length = 0;
    node *current = head;
    do
    {
        length++;
        current = current->next;
    }
    while (current != NULL);
    return length;
}

bool contains_element(node *head, int element)
{
    /* Realisation of algorithm, checking if list contains element
     * argument head - pointer on first node
     * argument element - searching element
     * Upon successful completion function shall return true if list contains element, otherwise, false shall be returned */

    node *current = head;
    while (current != NULL)
    {
        if (current->value == element)
            return true;
        current = current->next;
    }
    return false;
}

void hint()
{
    /* Hint for user
     * void-type function, no returning value*/
    printf("\tГенерация k-элементных подмножеств: 1\n");
    printf("\tГенерация всех подмножеств для заданного: 2\n");
    printf("\tГенерация всех подмножеств, содержащих заданный элемент: 3\n");
}

node *add_item(node *head, int value)
{
    /* Realisation of algorithm, which add new node to the end of list
     * argument head - pointer to first node
     * argument value - integer value of node
     * Upon successful completion function shall return pointer on head element of changed list */

    node *current = head;
    if (current == NULL)
    {
        head = (node*)malloc(sizeof(node));
        head->value = value;
        head->next = NULL;
        return head;
    }
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (node*)malloc(sizeof(node));
    current->next->value = value;
    current->next->next = NULL;
    return head;
}