#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>

int output_system(int*, int*, int);
int system_solution(int*, int*, int, int*, int*);
int gcd(int, int, int*, int*);
int dio_solution(int, int, int, int*, int*);

int main()
{
    int result, comparisons_count, solution, mod, *remainders, *modules;
    size_t i;
    result = SetConsoleOutputCP(CP_UTF8);
    if (result == 0)
    {
        printf("An error occurred while setting language\n");
        return 1;
    }
    printf("Ввод производится в следующем формате: x = c[k] mod m[k]\n");
    printf("Введите количество сравнений в системе(k):");
    scanf("%d", &comparisons_count);
    if (comparisons_count <= 0)
    {
        printf("Количество сравнений должно быть больше 0\n");
        return 0;
    }
    remainders = (int*)malloc(sizeof(int) * comparisons_count);
    if (remainders == NULL)
    {
        printf("Произошла ошибка!\n");
        return 2;
    }
    modules = (int*)malloc(sizeof(int) * comparisons_count);
    if (modules == NULL)
    {
        printf("Произошла ошибка!\n");
        return 3;
    }
    for (i = 0; i < comparisons_count; i++)
    {
        printf("Введите c[%zu]:", i+1);
        scanf("%d", &remainders[i]);
        printf("Введите m[%zu]:", i+1);
        scanf("%d", &modules[i]);
        while (modules[i] <= 0)
        {
            printf("Модуль должен быть натуральным числом! Повторите ввод:");
            scanf("%d", &modules[i]);
        }
    }
    printf("Ваша система сравнений:\n");
    result = output_system(remainders, modules, comparisons_count);
    if (result != 0)
    {
        printf("Произошла ошибка!\n");
        return 4;
    }
    result = system_solution(remainders, modules, comparisons_count, &solution, &mod);
    if (result != 0)
    {
        if (result == 2)
        {
            printf("Модули попарно не взаимно просты, условие теоремы не выполняется!\n");
            return 0;
        }
        else
        {
            printf("Произошла ошибка!\n");
            return 6;
        }
    }
    printf("Ответ: x = %d mod %d", solution, mod);
    free(remainders);
    free(modules);
    return 0;
}

int system_solution(int *remainders, int *modules, int count, int *solution, int *M)
{
    /* Realisation of Chinese Theorem solving algorithm
     * argument remainders - pointer to integer array with remainders from comparisons system
     * argument modules - pointer to integer array with modules from comparisons system
     * argument count - integer value, contains number of comparisons in system
     * argument solution - pointer to integer value, which will contain "x" solution after algorithm execution
     * argument M - pointer to integer value, which will contain module for solved system
     * Upon successful completion function shall return 0
     * If one of pointers-arguments has value "NULL", function shall return 1
     * If modules aren't coprime in pairs, function shall return 2
     * If an error occurred, while allocating memory using malloc() for array with modules compositions, function shall return 3
     * If an error occurred in dio_solution - function, value "4" shall be returned */

    int result = 1, x, y, *M_compositions;
    size_t i, j;
    *solution = 0;
    if (remainders == NULL || modules == NULL || M == NULL)
        return 1;
    for (i = 0; i < count - 1; i++)
        for (j = i + 1; j < count; j++)
            result *= gcd(modules[i], modules[j], &x, &y);
    if (result != 1)
        return 2;
    M_compositions = (int*)malloc(sizeof(int) * (count + 1));
    if (M_compositions == NULL)
        return 3;
    M_compositions[0] = 1;
    for (i = 0; i < count; i++)
    {
        M_compositions[i + 1] = 1;
        for (j = 0; j < count; j++)
        {
            M_compositions[i + 1] *= modules[j];
        }
        M_compositions[i + 1] /= modules[i];
        M_compositions[0] *= modules[i];
        result = dio_solution(M_compositions[i+1], modules[i], 1, &x, &y);
        if (result != 0)
            return 4;
        if (x < 0)
            x = modules[i] + x;
        *solution += M_compositions[i+1] * x * remainders[i];
    }
    *solution = *solution % M_compositions[0];
    *M = M_compositions[0];
    free(M_compositions);
    return 0;
}

int dio_solution(int a, int b, int c, int *x, int *y)
{
    /* Realisation of linear Diophantine equation solving algorithm
     * argument a - integer value, first coefficient in equation
     * argument b - integer value, second coefficient in equation
     * argument c - integer value, right-part coefficient in equation
     * Upon successful completion function shall return 0
     * If one of pointers-arguments has value "NULL", function shall return 1
     * If an error occurred in gcd - function, value "2" shall be returned */

    int d;
    *x = *y = 0;
    if (x == NULL || y == NULL)
        return 1;
    d = gcd(abs(a), abs(b), x, y);
    if (d < 0)
        return 2;
    *x *= c / d;
    *y *= c / d;
    if (a < 0)
        *x *= -1;
    if (b < 0)
        *y *= -1;
    return 0;
}

int gcd(int a, int b, int *x, int *y)
{
    /* Realisation of Euclid extended algorithm
     * argument a - integer value, first parameter
     * argument b - integer value, second parameter
     * argument x - pointer to integer value, which will contain first Bezout coefficient
     * argument y - pointer to integer value, which will contain second Bezout coefficient
     * Upon successful completion function shall return greatest common divisor of values a and b
     * If one of pointers-arguments has value "NULL", function shall return -1 */

    int result, temp_x, temp_y;
    if (x == NULL || y == NULL)
        return -1;
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    result = gcd(b % a, a, &temp_x, &temp_y);
    *x = temp_y - (b / a) * temp_x;
    *y = temp_x;
    return result;
}

int output_system(int *remainders, int *modules, int count)
{
    /* Realisation of algorithm, which output system of comparisons in format: x = remainders[i] mod modules[i] for each i < count
     * argument remainders - pointer to integer array with remainders from comparisons system
     * argument modules - pointer to integer array with modules from comparisons system
     * argument count - integer value, contains number of comparisons in system
     * Upon successful completion function shall return 0
     * If one of pointers-arguments has value "NULL", function shall return 1 */

    if (remainders == NULL || modules == NULL)
        return 1;
    for (size_t i = 0; i < count; i ++)
        printf("x = %d mod %d\n", remainders[i], modules[i]);
    return 0;
}