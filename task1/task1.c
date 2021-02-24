#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, i, j, k, p;
    scanf("%d", &N);
    if (N>=2)
    {
        N=N-1;
        int num[N];
        for (i=0; i<N; i++)
        {
           num[i]=i+2;
        }
        for (i=0; i<N; i++)
        {
            p=num[i];
            for (j=i+1; j<N; j++)
            {
                if (!(num[j]%p))
                {
                    for (k=j; k<N-1; k++)
                    {
                        num[k]=num[k+1];
                    }
                    N--;
                    j--;
                }
            }
        }
        for (i=0; i<N; i++)
        {
            printf("%d\n",num[i]);
        }


    }
    else
        printf("N<2");
    return 0;
}
