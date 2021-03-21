#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int a,b,c=1,x,y;
int a2, M=1, b2, n, M0, s=0;
vector <int> v1, v2,v3, v4;
int du()
{
      int x1=-1;
      float y1=(float)(a*x1-1)/b;
      while  (y1!=ceil(y1))
      {
          x1++;
          y1=(float)(a*x1-1)/b;
      }

      cout<<x1<<" "<<y1<<endl;
      x=(int)x1*c;
      y=y1*c;

      return 0;

}
int vvod ()
{
        cout<<endl<<"Enter a number"<<endl;
        cin>>a2;
        v1.push_back(a2);
        cout<<endl<<"Enter the divisor for the number"<<endl;
        cin>>b2;
        v2.push_back(b2);
        M=M*b2;
        return 0;
}
int china()
{
    for (int i=0; i<n; i++)
    vvod();
    for (int i=0; i<n; i++)
    {
        M0=1;
        for (int j=0; j<n; j++)
        {
            if (i!=j)
            {
                M0=M0*v2[j];
            }
        }
        v3.push_back(M0);
    }
    for (int i=0; i<n; i++)
    {

    a=v3[i];
    b=-v2[i];
    du();
    v4.push_back(x);
    }
    for (int i=0; i<n; i++)
    {
     s=s+(v4[i]*v1[i]*v3[i]);
    }
    return 0;
}
int main()
{
    cout<<endl<<"Enter the number of numbers"<<endl;
    cin>>n;
    china();
    cout<<endl<<s%M<<endl;
    return 0;
}
