#include <stdio.h>
#include <malloc.h>
#include <stddef.h>

int sieve(int* array, int N)
{
    size_t i;
    int current;
    for(i=0;i<(N-1);i++)
    {
        array[i]=i+2;
    }
    for(current=2;current<=N;current++)
    {
        if(array[current-2]!=0)
        {
            for(i=current-1;i<(N-1);i++)
            {
                if(array[i]%current==0)
                {
                    array[i]=0;
                }
            }
        }
    }
    for(i=0;i<(N-1);i++)
    {
        if(array[i]!=0) printf("%d\n",array[i]);
    }
    return 0;
}

int main()
{
    int N;
    int* array;
    scanf("%d",&N);
    array=(int*)malloc((N-1)*sizeof(int));
    sieve(array,N);
    free(array);
    return 0;
}
