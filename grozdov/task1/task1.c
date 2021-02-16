#include <stdio.h>
#include <stdlib.h>

int main()
{ int N, n;
scanf("%d", &N);
int A[N];
for (int i=0;i<N;i++)
    A[i]=i+1;
    A[0]=0;
    n=2;
 while (n*n<N)
 {  printf("%d\n", n);
     for (int i=0;i<N;i++)
        if ((A[i]) % n ==0)
        A[i]=0;
     for (int j=n;j<N;j++)
        if (A[j]!=0)
       {
        n=A[j];
        break;
       }
 }
    for (int i=0;i<N;i++)
        if (A[i]!=0)
        printf("%d\n", A[i]);
    return 0;
}
