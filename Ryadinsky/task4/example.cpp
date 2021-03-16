#include <iostream>
using namespace std;

int diaphantine_equations(int a, int b) {//Диофантовы уравнения
	bool turn = true, minus_b = false, minus_a = false;
	if (a == b && a != 1 || a/b==0)
	{
		cout << "Решения нет!";
		return 1;
	}
	int x = 0, y = 0;
	if (b < 0)
	{
		b = b * -1;
		minus_b = true;
	}
	if (a < 0)
	{
		a = a * -1;
		minus_a = true;
	}
	while (turn)
	{
		int result = a * x + b * y;
		if (result == 1)
		{
			turn = false;
		}
		if (result < 1)
		{
			x++;
		}
		if (result > 1)
		{
			y--;
		}
	}
	if (minus_a == true)
	{
		a = a * -1;
		x = x * -1;
	}
	return x;
}

int china_th_ost(int n)
{
	int* array_c;
	int* array_m;
	int* array_M;
	int* array_x;
	int x = 0, nod, M = 1, q;
	size_t i;
	array_c = new int[n];
	array_m = new int[n];
	array_M = new int[n];
	array_x = new int[n];
	setlocale(LC_ALL, "rus");
	for (i = 0; i < n; i++)
	{
		cout << "Введите с" << i + 1 << endl;
		cin >> array_c[i];
	}
	for (i = 0; i < n; i++)
	{
		cout << "Введите m" << i + 1 << endl;
		cin >> array_m[i];
	}
	for (i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			for (nod = array_m[i]; nod > 0; nod--)
			{
				if (array_m[i] % nod == 0 && array_m[i + 1] % nod == 0)
				{
					if (nod != 1)
					{
						cout << "nod!=1(" << array_m[i] << "," << array_m[i + 1] << ")";
						return 1;
					}
				}
			}
		}

		if (i != n - 2 && i != n - 1)
		{
			for (nod = array_m[i]; nod > 0; nod--)
			{
				if (array_m[i] % nod == 0 && array_m[i + 2] % nod == 0)
				{
					if (nod != 1)
					{
						cout << "nod!=1(" << array_m[i] << "," << array_m[i + 2] << ")";
						return 2;
					}
				}
			}
		}

		M = M * array_m[i];
	}

	for (i = 0; i < n; i++)
	{
		array_M[i] = M / array_m[i];
	}
	for (i = 0; i < n; i++)
	{
		array_x[i] = diaphantine_equations(array_M[i], array_m[i]);
	}

	for (i = 0; i < n; i++)
	{
		x = x + array_M[i] * array_c[i] * array_x[i];
	}
	q = x % M;
	cout << x << "mod" << M << endl;
	cout << q << "mod" << M;
	delete[]array_c;
	delete[]array_m;
	delete[]array_M;
	delete[]array_x;
	return 0;
}


int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите кол-во сравнений!" << endl;
	cin >> n;
	china_th_ost(n);
	return 0;
}