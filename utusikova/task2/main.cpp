#include <iostream>
#include <cmath>
using namespace std;
int a,b,c,x,y;
int nod(int a, int b)
{
    int r;
    if (b>a)
    {
        int c=a;
        a=b;
        b=c;
    }
    while (b!=0)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}
bool du(int *aa,int *bb,int *cc, int *x,int *y)
{
    int a=*aa;
    int b=*bb;
    int c=*cc;
    cout<<"a, b, c ="<<a<<" "<<b<<" "<<c<<endl;
    int q=nod(a,b);
    if (c%q==0)
    {
      a=a/q;
      b=b/q;
      c=c/q;
      q=1;
      int y1=-(a+b+c);
      float x1=(float)(q-b*y1)/a;
      while  (x1!=ceil(x1))
      {
          y1++;
          x1=(float)(q-b*y1)/a;

      }

      cout<<x1<<" "<<y1<<endl;
      *x=(int)x1*c/q;
      *y=y1*c/q;
      *bb=b/q;
      *aa=a/q;
      *cc=c;
      return true;
    }
    else
        return false;

}

int main()
{

    cin>>a;
    cin>>b;
    cin>>c;
    int q=nod(a,b);
    if (du(&a,&b,&c,&x,&y)==true)
    {

      cout<<endl<<"x="<<x<<"+"<<b<<"k"<<endl;
      cout<<endl<<"y="<<y<<"-"<<a<<"k"<<endl;
      cout<<endl<<"k="<<endl;
      int k;
      cin>>k;
      x=x+b*k;
      y=y-a*k;
      cout<<endl<<x<<" "<<y<<endl;
    }
    else
        cout<<endl<<"No solution"<<endl;
    return 0;
}
