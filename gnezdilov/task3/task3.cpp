#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector <int> vec;
int N;   

void continuedFraction(int i) 
{
    int e, l, r, a, d;

    l = N;
    r = i - l * l;
    d = N + l;
    a = d / r;
    e = r;
    vec.push_back(a); 
    do
    {
        l = (a * r - l);
        r = i - l * l;
        if (r % e == 0)
        {
            d = N + l;
            r = i - l * l;
            r = r / e;
            a = d / r;
            e = r;

        }
        else
        {
            d = e * N + e * l;
            r = i - l * l;
            a = d / r;
            e = r;

        }
        vec.push_back(a); 

    }         while (l != N);
}

int main()
{

    int i, n;
    cin >> n;
    for (i = 1; i < n + 1; i++)
    {
        N = (int)sqrt((float)i);

        if (i - N * N != 0)
        {
            continuedFraction(i);
            cout << i << "=[" << N << ";(";
            vector <int>::iterator iter;
            iter = vec.begin();
            cout << *iter;
            iter++;
            for (; iter != vec.end(); iter++)
                cout << "," << *iter;
            cout << ")]" << endl;
            vec.clear();
        }
        else
        {
            cout << i << "=[" << N << "]" << endl;
        }

    }

    return 0;
}