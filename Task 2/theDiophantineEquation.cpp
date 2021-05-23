#include <iostream>
#include <cstdlib>

using namespace std;

void euclid(int a, int b, int *gcd, int *x11, int *y11);
int theExistenceOfSolutions(int d, int c);

int main(){

int a, b, c, d, x1, y1, k;

    cout << "Coefficient before x: ";
    cin >> a;
    cout << "Coefficient before y: ";
    cin >> b;
    cout << "Coefficient c: ";
    cin >> c;

    euclid(a, b, &d, &x1, &y1);

    if (theExistenceOfSolutions(d, c) == 0) {
        cout << "The equation has no solutions";
        return 0;
    }

    cout << endl;
    cout << "General solution of the Diophantine equation:"<< endl;
    cout << "x = " << x1 * c / d << showpos << b / d << "k" << endl;
    cout << noshowpos << "y = " << y1 * c / d << showpos << - a / d << "k" << endl;
    cout << noshowpos << "Enter the coefficient k to get a particular solution:";
    cin >> k;
    cout << endl;
    cout << "Particular solution with k = " << k << ":" << endl;
    cout << "x0 = " << x1 * c / d + k * b / d << endl;
    cout << "y0 = " << y1 * c / d - k * a / d;

    return 0;
}

void euclid(int a, int b, int *gcd, int *x11, int *y11) {
    int r[3], q[3], x[3], y[3];

    if (a > b){
        r[0] = a;
        r[1] = b;
        x[0] = 1;
        x[1] = 0;
        y[0] = 0;
        y[1] = 1;
    } else {
        r[0] = b;
        r[1] = a;
        x[0] = 0;
        x[1] = 1;
        y[0] = 1;
        y[1] = 0;
    }
        q[1] = (int) r[0] / r[1];

    while (r[0] % r[1] != 0){
        r[2] = (int) r[0] % r[1];
        q[2] = (int) r[1] / r[2];
        x[2] = x[0] - x[1] * q[1];
        y[2] = y[0] - y[1] * q[1];

    for (size_t i = 0; i < 2; i++){
        r[i] = r[i + 1];
        q[i] = q[i + 1];
        x[i] = x[i + 1];
        y[i] = y[i + 1];
    }
}

        *gcd = r[2];
        *x11 = x[2];
        *y11 = y[2];
}

int theExistenceOfSolutions(int d, int c){
    if (c % d != 0) return 0; else return 1;
}
