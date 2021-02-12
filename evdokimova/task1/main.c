#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    int N;
    size_t i;
    setlocale(LC_ALL, "Rus");
    printf("Введите число, до которого надо выписать простые числа:\n");
    printf("N= ");
    scanf ("%d", &N);

    int All [N];
    for (i=0; i<N; i++)
    {
        All[i]=i;
        All[i]+=1;
    }

    printf("\nПростые числа:\n");

    for (i=0; i<N; i++)
    {
        if (All[i]==2 || All[i]==3 || All[i]==5 || All[i]==7)
        {
            printf("%d, ", All[i]);
        }
        else if (All[i]%2!=0 && All[i]%3!=0 && All[i]%5!=0 && All[i]%7!=0 && All[i]!=1)
        {
            printf("%d, ", All[i]);
        }
    }


    return 0;
}
