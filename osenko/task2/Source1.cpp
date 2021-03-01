#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int NOD(int a, int b) {
	return b ? NOD(b, a % b) : a;
}

int main() {
	int a, b, c, k, d, l, N;
	cout << "ax + by = c" << endl;
	cout << " Enter your numbers" << endl;
	cin >> a >> b >> c;
	if (a == b) { cout << "Eror NOD"; return 1; }
	N = NOD(a, b);
	cout << endl << N << endl;
	if (NOD(a, b) > 1) {
		a = a / N;
		b = b / N;
		c = c / N;
	}
	if (a > b) {
		d = a - b;
		cout << "d=" << a << "-" << b << endl;
		l = b - d;
		cout << "l=" << b << "-" << d << endl;

		cout << "1=" << b << "-" << d << "=" << b << "-(" << a << "-" << b << ")=" << b << "*2" << "+" << a << "*(-1)" << endl;
		cout << "test ==> " << b << "*2*" << c << "+" << a << "*(-1)*" << c << "=" << b * 2 * c - a * c << endl;
		if (b * 2 * c - a * c != c) { cout << "Mistake" << endl; return 1; }
		cout << "x=" << "-1+" << b << "*k" << endl;
		cout << "y=" << "2-" << a << "*k" << endl;
		cout << "Enter your k" << endl;
		cin >> k;
		cout << "x=" << -1 + b * k << endl;
		cout << "y=" << 2 - a * k << endl;
		cout << " Answer is: " << endl << "x=-1+" << b << "*" << k << endl << "y=2-" << a << "*" << k;

	}
	else {
		d = b - a;
		cout << "d=" << b << "-" << a << endl;
		l = a - d;
		cout << "l=" << a << "-" << d << endl;

		cout << "1=" << a << "-" << d << "=" << a << "-(" << b << "-" << a << ")=" << a << "*2" << "+" << b << "*(-1)" << endl;
		cout << "test ==> " << a << "*2*" << c << "+" << b << "*(-1)*" << c << "=" << a * 2 * c - b * c << endl;
		if (a * 2 * c - b * c != c) { cout << "Mistake" << endl; return 1; }
		cout << "x=" << "-1+" << a << "*k" << endl;
		cout << "y=" << "2-" << b << "*k" << endl;
		cout << "Enter your k" << endl;
		cin >> k;
		cout << "x=" << -1 + a * k << endl;
		cout << "y=" << 2 - b * k << endl;
		cout << " Answer is: " << endl << "x=-1+" << a << "*" << k << endl << "y=2-" << b << "*" << k;
	}


	return 0;
}