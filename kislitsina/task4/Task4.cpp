#include <iostream>
#include <locale>

using namespace std;

int first(int Num, int* a, int* m, int* M, int b)
{
    cout << "X = a(mod m)" << endl;
    for (int i = 0; i < Num; i++)
    {
        cout << "Пожалуйста, введите значение а для " << i + 1 << " уравнения: ";
        cin >> a[i];
        cout << "Пожалуйста, введите значение m для " << i + 1 << " уравнения: ";
        cin >> m[i];
        b = b*m[i];
    }
    for (int i = 0; i < Num; i++) {M[i] = b/m[i];}
    return b;
}

int third(int cm, int cM)
{
    int res = 0, q = 0;
    int x[3], p[3];
    if (cM > cm)
    {
        x[0] = 1;
        x[1] = 0;
        p[0] = cM;
        p[1] = cm;
    }
    else
    {
        x[0] = 0;
        x[1] = 1;
        p[0] = cm;
        p[1] = cM;
    }
    while (p[0]%p[1] != 0)
    {
        p[2] = p[0]%p[1];
        q = p[0]/p[1];
        x[2] = x[0] - x[1]*q;
        for (size_t i = 0; i < 2; i++)
        {
            p[i] = p[i+1];
            x[i] = x[i+1];
        }
    }
    res = x[2];
    return res;
}

int second(int Num, int* a, int* m, int* M, int d)
{
    int X = 0;
    int c;
    for (int i = 0; i < Num; i++)
    {
        c = third(m[i], M[i]);
        X += a[i]*M[i]*c;
    }
    X = X % d;
    while (X < 0) {X = X + d;}
    return X;
}

int main ()
{
    setlocale (LC_ALL, "Rus");
    int N, m0 = 1, M0, result;
    cout << "Пожалуйста, введите количество уравнений" << endl;
    cin >> N;
    int* a = new int[N];
    int* m = new int[N];
    int* M = new int[N];
    M0 = first(N, a, m, M, m0);
    result = second(N, a, m, M, M0);
    cout << "X" << "=" << result << "(mod " << M0 << ")" <<endl;
    delete a; delete m; delete M;
    return 0;
}
