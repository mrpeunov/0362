#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int Solution (int N);
int SearchX (int M, int m);

int main()
{
    setlocale(LC_ALL, "Rus");
    int N, Result;
    printf("Введите количество сравнений: ");
    scanf("%d", &N);
    Result=Solution (N);
    printf("Ответ: %d", Result);
    return 0;
}

int Solution (int N)
{
    size_t i, j;
    int check1, check2, X;
    int* c = NULL;
    int* module = NULL;
    int* M = NULL;
    int* x = NULL;
    c=(int*)malloc(N*sizeof(int*));
    module=(int*)malloc(N*sizeof(int*));
    x=(int*)malloc(N*sizeof(int*));
    M=(int*)malloc((N+1)*sizeof(int*));
    printf("Вводите через нажатие Enter число, а затем модуль, по которому оно берётся\n");
    i=0;
    while (i<N)
    {
        scanf("%d", &c[i]);
        scanf("%d", &module[i]);
        i++;
    }
    // Заполнение массива М
    M[N]=1;
    for (i=0; i<N; i++)
    {
        M[N]=M[N]*module[i];
    }
    for (i=0; i<N; i++)
    {
        M[i]=1;
        for (j=0; j<N; j++)
        {
            if (i!=j) M[i]=M[i]*module[j];
        }
    }
    // Заполнение массива х
    for (i=0; i<N; i++)
    {
        check1=M[i];
        check2=module[i];
        x[i]=SearchX ( check1, check2);
    }

    // Ищем итоговый ответ
    X=0;
    for (i=0; i<N; i++)
    {
        X=X+(M[i]*x[i]*c[i]);
    }
    X=X%M[N];
    free(c);
    free(M);
    free(x);
    free(module);
    return X;
}

int SearchX (int M, int m)
{
    int r, q, mod = m, result;
    int x [10] = {1, 0};
    int CounterXY = 2;
    q = M/m;
    while (M%m!=1)
    {
        r = M%m;
        x [CounterXY] = x [CounterXY-2] -(q*x[CounterXY-1]);
        q = m/r;
        M = m;
        m = r;
        CounterXY++;
    }
    result = x [CounterXY-2] -(q*x[CounterXY-1]);
    if (result < 0) result = mod + result;
    return result;
}
