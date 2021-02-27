#include <iostream>
using namespace std;

void function() {//Диофантовы уравнения
    bool turn = true, minus = false, sunim = false;
    int a, b, c, k, d, c1;
    cout << "ax+by=c" << endl;
    cout << "Введите a!" << endl;
    cin >> a;
    cout << "Введите b!" << endl;
    cin >> b;
    cout << "Введите c!" << endl;
    cin >> c;
    cout << a << "x+" << b << "y=" << c << endl;
    for (d = a; d > 0; d--) {
        if (a % d == 0 && b % d == 0) {
            cout << "nod = " << d << endl;
            break;
        }
    }
    c1 = c;
    c = d;
    int x = 0, y = 0;
    if (b < 0)
    {
        b = b * -1;
        minus = true;
    }
    if (a < 0)
    {
        a = a * -1;
        sunim = true;
    }
    while (turn)
    {
        int result = a * x + b * y;
        if (result == c)
        {
            turn = false;
        }
        if (result < c)
        {
            x++;
        }
        if (result > c)
        {
            y--;
        }
    }
    c = c1;
    x = x * c / d;
    y = y * c / d;
    if (sunim == true)
    {
        a = a * -1;
        x = x * -1;
    }
    cout << "x=" << x << endl;
    if (minus == true)
    {
        y = y * -1;
        b = b * -1;
    }
    cout << "y=" << y << endl;
    cout << a << "*(" << x << "+" << b / d << "k" << ")+" << b << "*(" << y << "-" << a / d << "k" << ")=" << c << endl << "Введите k!" << endl;
    cin >> k;
    cout << a << "*(" << x << "+" << b / d << "*" << k << ")+" << b << "*(" << y << "-" << a / d << "*" << k << ")=" << c;
}

int main()
{
    setlocale(LC_ALL, "russian");
    function();
    return 0;
}