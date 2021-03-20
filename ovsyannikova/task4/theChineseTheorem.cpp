#include <iostream>
#include <cstdlib>

using namespace std;

int theChineseTheorem(int n, int * m, int * c);
void euclid(int a, int b, int * x11);

int main(){
	int N, result;
	cout << "Enter the number of conditions: ";
	cin >> N;
	//создание массива модулей и массива остатков
	int m[N], c[N]; 
	// заполнение массивов исходными данными
	for (size_t i = 0; i < N; i++){
		cout << "Ender remain №" << i + 1 << ": ";
		cin >> c[i];
		cout << "Ender module №" << i + 1 << ": ";
		cin >> m[i];
	}
	result = theChineseTheorem(N, m, c);
	cout << "Result: " << result;

	return 0;
}

// основной алгоритм
int theChineseTheorem(int n, int * m, int * c){
	int M[n], M0 = 1, x[n], k = 0;
	// находим M0  - общий модуль, равный произведению всех исходных модулей
	for (size_t i = 0; i < n; i++) M0 *= m[i];
	for (size_t i = 0; i < n; i++){
		M[i] = 1;
		// вычисляем модуль, равный произведению исходных модулей без соответствующего
		for (size_t j = 0; j < n; j++) if (i != j) M[i] *= m[j];
		// применяем общий алгоритм Евклида для нахождения соответствующего x
		euclid(M[i], m[i], &x[i]);
		// в переменной k считаем остаток по модулю M0
		k += M[i] * x[i] * c[i];
	} 

	return (int) k % M0;
}

// алгоритм Евклида из task2 без лишних переменных
void euclid(int a, int b, int * x11) {
int r[3], q[3], x[3];

	if (a > b){
	r[0] = a;
	r[1] = b;
	x[0] = 1;
	x[1] = 0;
} else {
	r[0] = b;
	r[1] = a;
	x[0] = 0;
	x[1] = 1;
}
	q[1] = (int) r[0] / r[1];

	while (r[0] % r[1] != 0){
		r[2] = (int) r[0] % r[1];
		q[2] = (int) r[1] / r[2];
		x[2] = x[0] - x[1] * q[1];

		for (size_t i = 0; i < 2; i++){
			r[i] = r[i + 1];
			q[i] = q[i + 1];
			x[i] = x[i + 1];
		}
	}

	*x11 = x[2];
}
