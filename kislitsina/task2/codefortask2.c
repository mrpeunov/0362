#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, k;
    int NOD, sol;

    printf("Please, enter parameter values of a, b, c:\n");
    scanf("%d %d %d", &a, &b, &c);
    printf("Your equation is %dX %+dY = %d\n", a, b, c);
    NOD = findingNOD(a, b);
    printf("NOD is %d\n", NOD);
    findingsolution(a, b, c, NOD, k);
    return 0;
}

int findingNOD(int m, int n)
{
    int d;
    m = abs(m);
    n = abs(n);
    while (m != 0 && n != 0)
    {
        if (m > n) m = m % n;
        else n = n % m;
    }
    if (m == 0) d = n;
    else d = m;
    return d;
}

int findingsolution(int m, int n, int p, int d, int s)
{
    int x = 0, y = 0;
    if (abs(p) % d != 0) printf("There isn't any solution\n");
    else
    {
        m /= d;
        n /= d;
        p /= d;
    }
    if (abs(m) >= abs(n))
    {
        do
        {
            x++;
        } while ((p - m*x)%n != 0);
        y = (p - m*x)/n;
    }
    else if (abs(n) > abs(m))
    {
        do
        {
            y++;
        } while ((p - n*y)%m != 0);
        x = (p - n*y)/m;
    }
    printf("The shift solution was found: X is %d; Y is %d\n\n", x, y);
    printf("The common solution is ...\n");
    if (m < 0) m = -m;
    else if (n < 0) n =-n;
    else if (m*n > 0 || p < 0) n = -n;

    printf("X = %d %+dS\n", x, n);
    printf("Y = %d %+dS\n\n", y, m);
    printf("Please, enter parameter value of S\n");
    scanf("%d", &s);

    x = x + n*s;
    y = y + m*s;
    printf("The solution was found: X is %d; Y is %d\n", x, y);
    return 0;
}
