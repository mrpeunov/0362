#include <iostream>
#include <cmath>
using namespace std;

int continued_fraction(int number)//сделал как смог
{
    int array[10];
    float x, y, n;
    size_t i, j;
    for (i = 1; i <= number; i++)
    {
        n = sqrt(i);
        y = modf(n, &x);
        if (y != 0)
        {
            cout << i << ":  " << "[" << x << ";";
            for (j = 0; j < 10; j++)
            {
                n = 1 / y;
                y = modf(n, &x);
                array[j] = x;
            }
            if (array[0] == array[1] && array[1] == array[2] && array[2] == array[3])
            {
                cout << "(" << array[0];
            }
            else if (array[0] == array[2] && array[1] == array[3])
            {
                cout << "(" << array[0] << "," << array[1];
            }
            else if (array[0] == array[3] && array[1] == array[4] && array[2] == array[5])
            {
                cout << "(" << array[0] << "," << array[1] << "," << array[2];
            }
            else if (array[0] == array[4] && array[1] == array[5] && array[2] == array[6] && array[3] == array[7])
            {
                cout << "(" << array[0] << "," << array[1] << "," << array[2] << "," << array[3];
            }
            else if (array[0] == array[5] && array[1] == array[6] && array[2] == array[7] && array[3] == array[8] && array[4] == array[9])
            {
                cout << "(" << array[0] << "," << array[1] << "," << array[2] << "," << array[3] << "," << array[4];
            }
            else
            {
                cout << "(";
                for (int j = 0; j < 10; j++)
                {
                    cout << array[j] << ",";
                }
            }
            cout << ")" << "]" << endl;
        }
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int number;
    cout << "Введите число до которого нужно выводить цепную дробь!"<<endl;
    cin >> number;
    continued_fraction(number);
    return 0;
}