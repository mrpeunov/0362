#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector <int> v;
int f;

void Raz(int i)
{
        int e,l, r, a, d;

        l=f;
        r= i-l*l;
        d= f+l;
        a=d/r;
        e=r;
        v.push_back(a);

        do
        {
            l=(a*r-l);
            r= i-l*l;
            if (r%e==0)
            {
                d= f+l;
                 r= i-l*l;
                r=r/e;
                a=d/r;
                e=r;

            }
            else
            {
                d=e*f+e*l;
                r= i-l*l;
                a=d/r;
                e=r;

            }
            v.push_back(a);

        }
        while (l!=f);
}

int main()
{

    int i,n;
    cin>>n;
    for (i=1; i<n+1; i++ )
    {
        f =(int)sqrt((float)i);

        if (i-f*f!=0)
            {
                Raz(i);
                cout<<i<<"=["<<f<<";(";
                vector <int>::iterator it;
                it=v.begin();
                cout<<*it;
                it++;
                for ( ; it!=v.end(); it++)
                cout<<","<<*it;
                cout<<")]"<<endl;
                v.clear();
            }
            else
               {cout<<i<<"=["<<f<<"]"<<endl;}

    }

    return 0;
}
