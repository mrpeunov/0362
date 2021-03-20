#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct modular_arithmetic
{
    size_t remainder;
    size_t module;
} modular_arithmetic;

int DiophantForChineseTheorem(int a, int b)
{
    int X[3];
    int Y[3];
    int q, z;
    size_t i;
    int r[2];

    if(a > b)
    {
        r[0] = a;
        r[1] = b;
        X[0] = 1;
        X[1] = 0;
        Y[0] = 0;
        Y[1] = 1;
    }
    else
    {
        r[0] = b;
        r[1] = a;
        X[0] = 0;
        X[1] = 1;
        Y[0] = 1;
        Y[1] = 0;
    };
    while(1)
    {
        q = r[0] / r[1];
        z = r[1];
        r[1] = r[0] % r[1];
        r[0] = z;
        if(r[1] == 0)
        {
            break;
        };

        X[2] = X[0] - X[1] * q;
        Y[2] = Y[0] - Y[1] * q;

        for(i=0; i<2; i++)
        {
            X[i] = X[i + 1];
            Y[i] = Y[i + 1];
        };
    };

    return X[2];
};

size_t gcd(size_t a, size_t b)
{
    size_t z;
    if(a < b)
    {
        z = a;
        a = b;
        b = z;
    };
    while(a % b != 0)
    {
        z = a % b;
        a = b;
        b = z;
    };
    return b;
}

int ChineseRemainderTheorem(size_t N, size_t* Mxc_summ, size_t* M_main, modular_arithmetic* designation)
{
    size_t i, t, *M,x_i;

    for(i = 0; i < N; i++)
    {
        for(t = 0; t<N; t++)
        {
            if(t == i)
            {
                continue;
            };
            if(gcd(designation[i].module, designation[t].module) != 1)
            {
                return 1;
            };
        };

    };

    for(i = 0; i < N; i++)
    {
        (*M_main) *= designation[i].module;
    };
    M = (size_t*) malloc(N * sizeof(size_t));
    if(M == NULL)
    {
        return 2;
    };
    for(i = 0; i<N; i++)
    {
        M[i] = (*M_main) / designation[i].module;
        if(DiophantForChineseTheorem(M[i], designation[i].module)<0)
        {
            x_i = designation[i].module+DiophantForChineseTheorem(M[i], designation[i].module);
        }
        else
        {
            x_i = DiophantForChineseTheorem(M[i], designation[i].module);
        };
        M[i] *= x_i * designation[i].remainder;
        (*Mxc_summ) += M[i];
    };
    if((*Mxc_summ) > (*M_main))
    {
        (*Mxc_summ) %= (*M_main);
    };
    free(M);
    return 0;
};

int main()
{
    size_t M_main = 1, Mxc_summ = 0, N, i;
    int result;
    modular_arithmetic* designation;

    scanf("%zu",&N);
    printf("\n");
    designation = (modular_arithmetic*)malloc(N * sizeof(modular_arithmetic));
    if(designation == NULL)
    {
        printf("Error\n");
        return 1;
    };

    for(i = 0; i < N; i++)
    {
        scanf("%zu",&designation[i].remainder);
        scanf("%zu",&designation[i].module);
        printf("\n");
    };

    result=ChineseRemainderTheorem(N, &Mxc_summ, &M_main,designation);
    if (result != 0)
    {
        printf("Error\n");
        return 1;
    };

    printf("x = %zu mod %zu\n", Mxc_summ, M_main);

    free(designation);
    return 0;
};
