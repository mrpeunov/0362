#include <iostream>

using namespace std;

int main()
{
    int *a;
    int p = 2, n;

    cout << "Enter size of array " << endl;
    cin >> n;
    cout << "\n";
    n++;

    a = new int[n];

    for (size_t i = 0; i < n; i++)
    {
        a[i] = i;
    }

    for (p = 2; p < n; p++)
    {
        if (a[p] != 0)
        {
            cout << a[p] << endl;
            for (size_t i = p*p; i < n; i+=p)
            {
                a[i] = 0;
            }
        }
    }

    delete a;
    return 0;
}
