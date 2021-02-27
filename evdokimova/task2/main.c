#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int GCD (int a, int b);
int Solution (int n, int m, int c, int k);
int SpecialCases (int gcd, int a, int b, int c);

int main()
{

    setlocale(LC_ALL, "Rus");
    int a, b, c, k;
    int n, m;
    int gcd;

    printf ("ax+by=c\n");
    printf ("Введите значение a:");
    scanf ("%d", &a);
    printf ("Введите значение b:");
    scanf ("%d", &b);
    printf ("Введите значение c:");
    scanf ("%d", &c);

    n = a;
    m = b;

    gcd = GCD (a, b);
    printf ("Наибольший общий делитель a и b = %d\n", gcd);
    SpecialCases (gcd, a, b, c);
    n = n/gcd;
    m = m/gcd;
    c = c/gcd;
    Solution (n, m, c, k);
    return 0;
}

int GCD (int a, int b)
{
    while (a!=b)
    {
        if (a>b) a = a-b;
        else b = b-a;
    }
    return a;
}

int Solution (int n, int m, int c, int k)
{
    int r, q;
    int x [10] = {1, 0};
    int y [10] = {0, 1};
    int CounterXY=1;
    printf ("Ищем частное решение %d*x0+%d*y0 = 1", n, m);
    r = n%m;
    while (r!=0)
    {
        q = n/m;
        CounterXY++;
        n = m;
        m = r;
        x [CounterXY] = x [CounterXY-2] -(q*x[CounterXY-1]);
        y [CounterXY] = y [CounterXY-2] -(q*y[CounterXY-1]);
    }
    printf ("x0 = %d", x[CounterXY]);
    printf ("y0 = %d", y[CounterXY]);

    printf ("Общее решение: %d*(%+d*%+d)+%d*(%+d*%+d)=%d", n,x[CounterXY],c,m,y[CounterXY],c,c);

    return 0;
}

int SpecialCases (int gcd, int a, int b, int c)
{
    if (a==b && a==0 && c!=0)
    {
        printf ("\nРешений нет\n");
    }
    if (a==b && a==0 && c==0)
    {
        printf ("\nРешений бесконечно много\n");
    }
    if (c%gcd != 0)
    {
        printf ("\nРешений нет\n");
    }

    return 0;
}
