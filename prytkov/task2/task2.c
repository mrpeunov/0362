#include <stdio.h>
#include <stddef.h>
#include <windows.h>

int gcd(int, int, int*, int*);
int partial_solution(int, int, int,int, int*, int*);
int dio_solution(int, int, int, int*, int*, int*, int*, int*);
void output_dio(int, int, int, int);

int main()
{
    int res, a, b, c, d, k, x, y, C_1, C_2;
    res = SetConsoleOutputCP(CP_UTF8);
    if (res == 0)
    {
        printf("Ошибка!\n");
        return 1;
    }
    printf("Введите коэфффициент a:");
    scanf("%d", &a);
    printf("Введите коэфициент b:");
    scanf("%d", &b);
    if (a == 0 && b == 0)
    {
        printf("Уравнение с такими коэффициентами решать не интересно\n");
        return 0;
    }
    printf("Введите коэффициент c:");
    scanf("%d", &c);
    res = dio_solution(a, b, c, &d, &x, &y, &C_1, &C_2);
    if (res != 0)
    {
        if (res == -2)
        {
            printf("Уравнение не разрешимо\n");
            return 0;
        }
        else
        {
            printf("Ошибка!\n");
            return 2;
        }
    }
    output_dio(x, y, C_1, C_2);
    printf("Введите значение k, чтобы получить частное решение:");
    scanf("%d", &k);
    res = partial_solution(k, a, b, d, &x, &y);
    if (res != 0)
    {
        printf("Ошибка!\n");
        return 3;
    }
    printf("Частное решение при k = %d: x = %d, y = %d", k, x, y);
    return 0;
}

int dio_solution(int a, int b, int c, int *d, int *x, int *y, int *C_1, int *C_2)
{
    if (d == NULL || x == NULL || y == NULL || y == NULL || C_1 == NULL || C_2 == NULL)
        return -1;
    *d = gcd(abs(a), abs(b), x, y);
    if (d < 0)
        return 2;
    if (c % *d == 0)
    {
        *x *= c / *d;
        *y *= c / *d;
        *C_1= b / *d;
        *C_2= a / *d;
        if (a < 0)
        {
            *x *= -1;
        }
        if (b < 0)
        {
            *y *= -1;
        }
    }
    else return -2;
    return 0;
}

int partial_solution(int k, int a, int b, int d, int *x, int *y)
{
    if (x == NULL || y == NULL)
        return 1;
    *x += k * b / d;
    *y -= k * a / d;
    return 0;
}

int gcd(int a, int b, int *x, int *y)
{
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

void output_dio(int x, int y, int C_1, int C_2)
{
    if (C_1 < 0 && C_2 < 0)
        printf("Общее решение имеет вид:\nx = %d - %d*k\ny = %d + %d*k\n", x, abs(C_1), y, abs(C_2));
    else if (C_1 < 0)
        printf("Общее решение имеет вид:\nx = %d - %d*k\ny = %d - %d*k\n", x, abs(C_1), y, C_2);
    else if (C_2 < 0)
        printf("Общее решение имеет вид:\nx = %d + %d*k\ny = %d + %d*k\n", x, C_1, y, abs(C_2));
    else
        printf("Общее решение имеет вид:\nx = %d + %d*k\ny = %d - %d*k\n", x, C_1, y, C_2);
}