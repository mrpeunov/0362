#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, p=2;
    int a*;

    scanf("%d", &n);

    a = (int*)malloc(n * sizeof(int));
    for (i=1; i<=n; i++)
    {
        a[i] = i;
    }
while (p < n)
{
    if (p!= 0)
    {
    for (i=p*p; i<=n; i+=p)
    {
        a[i]=0;
    }
    }
    p++;
}    for (i=1; i<=n; i++)
    {
        if (a[i] != 0) {
        printf("%d\n", a[i]);
    }
    }



    return 0;
}
