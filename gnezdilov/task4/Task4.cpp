
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>


int dioffan(int a2,int b2)
{
    int q, r, x_2, b;
    int x_0 = 1;
    int x_1 = 0;
    b = b2;
    r = a2 % b2;
    q = a2 / b2;
    x_2 = x_0 - q * x_1;
    while (r != 1) {
        a2 = b2;
        b2 = r;
        r = a2 % b2;
        q = a2 / b2;
        x_0 = x_1;
        x_1 = x_2;
        x_2 = x_0 - q * x_1;
    }
    if (x_2 < 0) x_2 = x_2 + b;
    return x_2;
}

int china_teor(int p,int *pM) {
    int **a;
    int x = 0;
    int x_0;
    a = (int**)malloc(p * sizeof(int));
    printf("\nВведите сравнение (сначала число, потом остаток):\n");
    for (int i = 0; i < p; i++) {
        a[i] = (int*)malloc(4 * sizeof(int));
        printf("x = ");
        for (int j = 0; j < 2; j++) {
            scanf("%d", &a[i][j]);
        }
        printf("\n");
    }

    for (int z = 0; z < p; z++) {
        *pM *= a[z][1];
    }
    for (int i = 0; i<p; i++){
        a[i][2] = 1;
        for (int  z = 0; z < p; z++) {
                if (i != z) { 
                   a[i][2] *= a[z][1];
                }
        }
        a[i][3] = dioffan(a[i][2], a[i][1]);
        x_0 = a[i][2] * a[i][3]*a[i][0];
        x += x_0;
        }
    return x;
}


int main()
{
    int n,R,B;
    int M = 1;
    setlocale(LC_ALL, "Rus");
    printf("Введите количество сравнений в системе: ");
    scanf("%d", &n);
    if (n <= 1) {
        printf("\nПридумай что-нибудь поинтереснее =)");
        do {
            printf("Введите количество сравнений в системе: ");
            scanf("%d", &n);
        } while (n <= 1);
        }
    R = china_teor(n, &M);
    B = R % M;
    printf("x = %d", B);
    return 0;
} 