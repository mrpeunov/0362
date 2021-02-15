#include <iostream>

using namespace std;

int main()
{
    int n,i,a[100000];
    cin>>n;
    for ( int i=2; i<n+1; i++)
    {
       a[i]=1 ;
    }
    for ( i=2; i<n; i++)
    {
      for ( int j=2*i; j<n+1; j++)
      {
            if (j%i==0)
                a[j]=0;
       }
    }
    for ( i=2; i<n+1; i++)
    {
        if(a[i]==1)
            cout<<i<<" ";
    }

    return 0;
}

