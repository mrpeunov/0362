#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
vector <int> v;//двоичный вектор для перебора
vector <char> a;//алфавит
int next ()
{
    int i, n;
    n=v.size();
    i=n-1;
    while (v[i]==1 && i>=0)
    {
        v[i]=0;
        i--;
    }
    v[i]++;
    return 0;
}
int set_of_subsets()
{
    int x, i, n;
    n=a.size();
    for (i=0; i<n; i++) v.push_back(0);
    for (i=0; i<pow(2,n)-1; i++)
    {
        next();
        for(int j=0; j<n; j++)
    {
        if (v[j]==1) cout<<a[j]<<" ";
    }
    cout<<endl;
    }
    cout<<"empty set"<<endl;//пустое множество

    return 0;
}
int set_of_subsets_element(char c)
{
    a.erase(find(a.begin(), a.end(), c));
   int x, i, n;
    n=a.size();
    v.clear();
    for (i=0; i<n; i++) v.push_back(0);
    for (i=0; i<pow(2,n)-1; i++)
    {
        next();
        for(int j=0; j<n; j++)
    {
        if (v[j]==1) cout<<a[j]<<" ";
    }
    cout<<c<<endl;
    }
    cout<<c<<endl;//пустое множество

    return 0;
}
int set_of_subsets_k(int k)
{
    if (k==0)
    {
        cout<<"empty set"<<endl;//пустое множество
        return 0;
    }
    int i, n, s;
    n=a.size();
    v.clear();
    for (i=0; i<n; i++) v.push_back(0);
    for (i=0; i<pow(2,n)-1; i++)
    {
        next();
        s=0;
        for (int j=0; j<n; j++)
            s=s+v[j];
        if (s==k)
        {

        for(int j=0; j<n; j++)
    {
        if (v[j]==1) cout<<a[j]<<" ";
    }
    cout<<endl;
    }
    }

    return 0;
}
int main()
{
    cout<<"enter an alphanumeric character set.not from words"<<endl;//введите алфовит состоящий из символов.не из слов
    char c;
    while (cin>>c)
    {
        a.push_back(c);
        if (cin.get()=='\n')
        break;
    }
    cout<<"======="<<endl;
    set_of_subsets();
    //
    int k;
    cout<<"enter the number of elements in the subset"<<endl;//введите количество элементов в подмножестве
    cin>>k;
    cout<<"======="<<endl;
    set_of_subsets_k(k);
    //
    cout<<"enter one character from the alphabet"<<endl;//введите один символ из алфовита
    cin>>c;
    cout<<"======="<<endl;
    set_of_subsets_element(c);
    return 0;
}
