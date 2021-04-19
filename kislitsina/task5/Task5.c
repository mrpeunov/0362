#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

void menu();//просто меню
int TenToFact();//перевод из 10 СС в факториальную
int FactToTen();//перевод из факториальной СС в 10-ую
int GetNumOfTransp();//получение номера перестановки по данной и алфавиту
int GetTranspByNum();//получение персетановки по номеру и алфавиту
int GetNextTransp();//получение следующей перестановки по текущей
int GetFactorial();//вычисление факториала числа

int main()
{
    setlocale(LC_ALL, "Rus");
    int choice;
    int a, b;
    system("cls");
    menu();
    A: scanf("%d", &choice);//выбор действия
    switch (choice){
case 1: printf("Введите число, которое нужно перевести\n"); scanf("%d", &a);
        printf("Число в факториальной системе счисления: %d\n", TenToFact(a)); break;
case 2: printf("Введите число, которое нужно перевести\n"); scanf("%d", &a);
        printf("Число в десятичной системе счисления: %d", FactToTen(a)); break;
case 3: printf("Пожалуйста, введите количество элементов в перестановке\n"); scanf("%d", &a); GetNextTransp(a); break;
case 4: printf("Пожалуйста, введите количество элементов в перестановке\n"); scanf("%d", &a); GetNumOfTransp(a); break;
case 5: printf("Пожалуйста, введите количество элементов в алфавите\n"); scanf("%d", &a); GetTranspByNum(a); break;
default: printf("Было введено неверное число. Попробуйте снова\n"); goto A;
    }
    return 0;
}

void menu()
{
    printf("\t\tПожалуйста, выберите необходимое действие:\n\n");
    printf("1 - перевод из 10 СС в факториальную\t\t 2 - перевод из факториальной в 10 СС\n");
    printf("3 - получение следующей перестановки по текущей\t 4 - получение номера по перестановке и алфавиту\n");
    printf("5 - получение перестановки по номеру и алфавиту\n");
}

int GetFactorial(int count)
{
    int res = 1;
    for (size_t j = 1; j <= count; j++)
    {
        res = res*j;
    }
    return res;
}

int TenToFact(int num)
{
    int p = 0, i = 2, k = 0;
    float deg;
    do
    {
       deg = pow(10, k);//возводим 10 в соответствующую степень для получения разрядов числа
       p += (num%i)*deg;
       num = num/i;
       k++;
       i++;
    } while(num != 0);
    return p;
}

int FactToTen(int num)
{
    int result = 0, i = 1, ost = 0, f = 0;
    do
    {
        ost = num % 10;
        num = num / 10;
        f = GetFactorial(i);
        result += ost*f;
        i++;
    } while (num != 0);
    return result;
}

int GetNextTransp(int size)
{
    int *t;
    int m = size - 2, q = size - 1, p;
    t = (int*)malloc(size*sizeof(int));
    printf("Введите перестановку\n");
    for(size_t i = 0; i < size; i++)
    {
        scanf("%d", &t[i]);
    }
    while (m != -1 && t[m] >= t[m+1])//ищем точку поворота
    {
        m--;
    }
    if (m == -1)
    {
        printf("Перестановок больше нет\n");
    }
    while (t[q] <= t[m]) q--;//ищем суффикс
    p = t[m];//здесь начинаем менять местами наименьший элемент суффикса и точку поворота
    t[m] = t[q];
    t[q] = p;
    m = m + 1;
    q = size - 1;
    while (m < q)//сортируем элементы суффикса
    {
        p = t[m+1];
        t[m+1] = t[q-1];
        t[q-1] = p;
    }
    printf("Следующая транспозиция: \n");
    for (size_t i = 0; i < size; i++) printf("%d", t[i]);
    free(t);
    return 0;
}

int GetNumOfTransp(int size)
{
    int *t, *f, *inv;
    int number = 0;
    t = (int*)malloc(size*sizeof(int));
    printf("Введите перестановку\n");
    for(size_t i = 1; i <= size; i++)
    {
        scanf("%d", &t[i]);//перестановка
    }
    f = (int*)malloc(size*sizeof(int));
    inv = (int*)malloc(size*sizeof(int));
    for (size_t i = 1; i <= size; i++) inv[i] = 0;//массив инверсий
    f[0] = 1;
    for (size_t i = 1; i <= size; i++) f[i] = f[i-1]*i;//массив факториалов
    for (size_t i = 1; i <= size; i++)
    {
        for (size_t j = i+1; j <= size; j++)
        if (t[i]>t[j]) inv[i] += 1;
        number += inv[i]*f[size - i];//номер перестановки = количество инверсий для данного числа * соответсвующий факториал(начиная с числа 2)
    }
    printf("Номер перестановки: %d\n", number+1);
    free(t);
    free(f);
    free(inv);
    return 0;
}

int GetTranspByNum(int size)
{
    int *t, *ost, *ans;
    int number, m;
    float q;
    t = (int*)malloc(size*sizeof(int));
    ans = (int*)malloc(size*sizeof(int));
    printf("Введите алфавит (под алфавитом понимается набор различных упорядоченных чисел)\n");
    for(size_t i = 0; i < size; i++)
    {
        scanf("%d", &t[i]);
        ans[i] = 0;
    }
    printf("Введите номер искомой перестановки:\n");
    A: scanf("%d", &number);
    m = GetFactorial(size);//находим факториал числа элементов в алфавите
    if (number > m) {printf("Введите число меньшее, чем %d\n", m); goto A;}//номер перестановки не должен превышать факториала числа элементов в алфавите
    number = TenToFact(number-1);
    ost = (int*)malloc(size*sizeof(int));//массив из чисел, из которых представлено number
    for(int i = 0; i < size; i++)
    {
        q = pow(10, size - i - 2);//получаем 10 в соответсвующей степени
        ost[i] = number/q;//получаем числа поразрядно (начиная с самого большого разряда)
        number -= ost[i]*q;//переходим к следующему разряду
    }
    for (int i = 0; i < size; i++)//индексы для ost
    {
        for (int j = 0; j < size; j++)//индексы для t(алфавит)
        {
            if (ost[i] == j)//при совпадении индексов будут выполняться следующие действия
            {
                ans[i] = t[j];
                for (int l = j; l < size - 1; l++) t[l] = t[l + 1];//переставляем числа
                t[size - 1] = 0;
            }
        }
    }
    printf("Искомая перестановка\n");
    for(size_t i = 0; i < size; i++)
    {
        printf("%d", ans[i]);
    }
    free(t);
    free(ost);
    return 0;
}

