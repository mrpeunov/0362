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

size_t to_factorial(int);
size_t from_factorial(int);
int *get_next_permutation(int*,int);
int get_num_by_permutation(int*, int);
int *get_permutation_by_num(int, int);
int output_permutation(int*, int);
int get_item_by_num(node*, int);
int *input_permutation(int);
node *delete_item(node*, int);
int *create_alphabet(int);
int add_item(node*, int);
int get_len(int);
void hint();

int main()
{
    int command, num, res, perm_len;
    size_t result;
    int *permutation, *alphabet;
    res = SetConsoleOutputCP(CP_UTF8);
    if (res == 0)
        return 1;
    hint();
    while (1)
    {
        printf("Введите команду: ");
        scanf ("%d", &command);
        if (command < 0 || command > 5)
        {
            printf("Вы ввели что-то не то, попробуйте еще раз: ");
            scanf("%d", &command);
        }
        if (command == 0)
            return 0;
        else if (command == 1)
        {
            printf("Введите положительное число: ");
            scanf("%d", &num);
            result = to_factorial(num);
            while (result == -1)
            {
                printf("Число должно быть положительным!\n Давай по новой: ");
                scanf("%d", &num);
                result = to_factorial(num);
            }
            printf("Результат перевода: %zu\n", result);
        }
        else if (command == 2)
        {
            printf("Введите положительное число: ");
            scanf("%d", &num);
            result = from_factorial(num);
            while (result == -1)
            {
                printf("Число должно быть положительным!\n Давай по новой: ");
                scanf("%d", &num);
                result = from_factorial(num);
            }
            printf("Результат перевода: %zu\n", result);
        }
        else if (command == 3)
        {
            printf("Введите длину перестановки: ");
            scanf("%d", &perm_len);
            printf("Введите вашу перестановку: ");
            permutation = input_permutation(perm_len);
            if (permutation == NULL)
            {
                printf("Произошла ошибка!\n");
                return 2;
            }
            system("cls");
            hint();
            alphabet = create_alphabet(perm_len);
            if (alphabet == NULL)
            {
                printf("Произошла ошибка!\n");
                return 3;
            }
            printf("Алфавит для перестановок длины %d: (", perm_len);
            res = output_permutation(alphabet, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 4;
            }
            printf(")\n");
            printf("Ваша перестановка: ");
            res = output_permutation(permutation, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 5;
            }
            permutation = get_next_permutation(permutation, perm_len);
            if (permutation == NULL)
            {
                printf("Произошла ошибка!\n");
                return 6;
            }
            printf("\nПерестановка, следующая за вашей: ");
            res = output_permutation(permutation, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 7;
            }
            printf("\n");
        }
        else if (command == 4)
        {
            printf("Введите количество элементов вашей перестановки: ");
            scanf("%d", &perm_len);
            printf("Введите вашу перестановку: ");
            permutation = input_permutation(perm_len);
            if (permutation == NULL)
                return 6;
            system("cls");
            hint();
            printf("Введенная вами перестановка: ");
            res = output_permutation(permutation, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 7;
            }
            printf("\n");
            res = get_num_by_permutation(permutation, perm_len);
            printf("Номер вашей перестановки: %d\n", res);
        }
        else if (command == 5)
        {
            printf("Введите мощность алфавита: ");
            scanf("%d", &perm_len);
            if (perm_len <= 1)
            {
                printf("С таким алфавитом работать не интересно\n");
                continue;
            }
            alphabet = create_alphabet(perm_len);
            if (alphabet == NULL)
            {
                printf("Произошла ошибка!\n");
                return 8;
            }
            printf("Алфавит заданной мощности: (");
            res = output_permutation(alphabet, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 9;
            }
            printf(")\n");
            printf("Введите номер перестановки для поиска: ");
            scanf("%d", &num);
            permutation = get_permutation_by_num(num, perm_len);
            if (permutation == NULL)
            {
                return 10;
            }
            printf("Перестановка с заданным номером: ");
            res = output_permutation(permutation, perm_len);
            if (res != 0)
            {
                printf("Произошла ошибка!\n");
                return 11;
            }
            printf("\n");
        }
        else
        {
            while (command < 0 || command > 5)
            {
                printf("Таких кодов команд я не припомню, попробуешь еще разок?: ");
                scanf("%d", &command);
            }
        }
    }
}

int *get_next_permutation(int *permutation, int length)
{
    int *perm, current;
    current = get_num_by_permutation(permutation, length);
    if (current < 0)
        return NULL;
    perm = get_permutation_by_num(current + 1, length);
    if (perm == NULL)
        return NULL;
    return perm;
}

size_t from_factorial(int number)
{
    size_t result = 0, i;
    size_t factorial = 1;
    int len;
    if (number < 0)
        return -1;
    len = get_len(number);
    if (len < 0)
        return -2;
    for (i = 1; i <= len; i++)
    {
        factorial *= i;
        result += (number % 10) * factorial;
        number = number / 10;
    }
    return result;
}

size_t to_factorial(int number)
{
    size_t factorial = 1, step = 1, result = 0, remainder = number, i;
    if (number < 0)
        return -1;
    if (number == 1)
        return 1;
    while (factorial <= number)
    {
        factorial *= step + 1;
        step++;
    }
    factorial /= step;
    step--;
    for (i = step; i > 0; i--)
    {
        result += (size_t)(remainder / factorial) * pow(10, i - 1);
        remainder = remainder % factorial;
        factorial /= i;
    }
    return result;
}

int *get_permutation_by_num(int number, int length)
{
    int *permutation, num, result, index[length];
    node *list;
    num = to_factorial(number - 1);
    for (int i = length - 2; i >= 0; --i)
    {
        index[i] = num % 10;
        num /= 10;
    }
    index[length - 1] = index[length - 2];
    if (num < 0)
        return NULL;
    list = (node*)malloc(sizeof(node));
    if (list == NULL)
        return NULL;
    list->next = NULL;
    list->value = 1;
    for (int i = 1; i < length; i++)
    {
        result = add_item(list, i + 1);
        if (result != 0)
            return NULL;
    }
    permutation = (int*)malloc(sizeof(int) * length);

    if (permutation == NULL)
        return NULL;

    for (int i = 0; i < length; i++)
    {
        permutation[i] = get_item_by_num(list, index[i]);
        list = delete_item(list, permutation[i]);
        if (result != 0)
            return NULL;
    }
    return permutation;
}

int get_item_by_num(node *head, int index)
{
    node *current = head;
    int counter = 0;
    if (head == NULL)
        return -1;
    while (counter != index)
    {
        if (current->next == NULL)
            return current->value;
        counter++;
        current = current->next;
    }
    return current->value;
}

int get_num_by_permutation(int *permutation, int length)
{
    if (permutation == NULL)
        return -1;
    int factorial = 1, num = 0, position;
    for (int i = length - 2; i >= 0; i--)
    {
        factorial *= length - i - 1;
        position = permutation[i] - 1;
        for (int j = 0; j < i; j++)
            if (permutation[j] < permutation[i])
                position--;
        num += position * factorial;
    }
    return num + 1;
}

int get_len(int number)
{
    if (number < 0)
        return -1;
    int len = 1;
    while ((number /= 10) > 0)
        len++;
    return len;
}

int *create_alphabet(int length)
{
    int *alphabet = (int*)malloc(sizeof(int) * length);
    if (alphabet == NULL)
        return NULL;
    for (int i = 0; i < length; i++)
        alphabet[i] = i + 1;
    return alphabet;
}

int *input_permutation(int length)
{
    int *permutation = (int*)malloc(sizeof(int) * length);
    if (permutation == NULL)
        return NULL;
    for (size_t i = 0; i < length; i++)
    {
        printf("Введите %zu-й элемент: ", i + 1);
        scanf("%d", &permutation[i]);
    }
    return permutation;
}

int output_permutation(int *permutation, int length)
{
    if (permutation == NULL)
        return -1;
    printf("%d", permutation[0]);
    for (size_t i = 1; i < length; i++)
        printf(" %d", permutation[i]);
    return 0;
}

int add_item(node *head, int value)
{
    node *current = head;
    if (head == NULL)
        return -1;
    while (current->next != NULL)
        current = current->next;
    current->next = (node*)malloc(sizeof(node));
    if (current->next == NULL)
        return -2;
    current->next->value = value;
    current->next->next = NULL;
    return 0;
}

node *delete_item(node *head, int value)
{
    node *current = head, *temp = head;
    if (head == NULL)
        return 0;
    while(current->value != value)
    {
        temp = current;
        current = current->next;
    }
    if (current->next == NULL)
    {
        temp->next = NULL;
        free(current);
    }
    else if (current == head)
    {
        head = head->next;
        free(current);
    }
    else
    {
        temp->next = current->next;
        free(current);
    }
    return head;
}

void hint()
{
    printf("Команды, которые программа принимает на вход:\n");
    printf("\tВыйти: 0\n");
    printf("\tПеревести из десятичной СС в факториальную: 1\n");
    printf("\tПеревести из факториальной СС в десятичную: 2\n");
    printf("\tПолучить следующую перестановку по текущей: 3\n");
    printf("\tПолучить номер по перестановке и алфавиту:  4\n");
    printf("\tПолучить перестановку по алфавиту и номеру: 5\n");
}