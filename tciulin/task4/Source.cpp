#include<iostream>

using namespace::std;
int proverka(int N, int *m)
{
	int b = 2;
	for (int i = 0; i < N-1; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			while ((b <= m[i])||(b<=m[j]))
			{
				if (((m[i] % b) == 0 )&& ((m[j] % b) == 0))
					return 1;
				else b++;
			}
			b = 2;
		}
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int N;
	cout << "Chinese Remainder Theorem!" << endl;
	cout << "enter the number of numbers:";
	cin >> N;
	
	int* a = new int[N];
	int* m = new int[N];
	int* mi = new int[N];
	int* y = new int[N];
	int X=0,M = 1, f = 0,z=1;
	
	TryAgain:
	for (int i = 0; i < N; i++)
	{

		cout << "Enter the remainder of a and the divisor of m:\n ";
		cout << "a =";
		cin >> a[i];
		cout << " m =";
		cin >> m[i];
		
		M = M * m[i];
	}
	
	if (proverka(N, m) == 1)
	{
		cout << "You entered the wrong divisors(they are not mutually prime numbers), try again:\n";
		goto TryAgain;
	}
	cout << "You entered:\n";
	
	for (int i = 0; i < N; i++)
	{
		cout << "x = " << a[i] << " mod " << m[i] << endl;
		mi[i] = M / m[i];
	}
	for (int i = 0; i < N; i++)
	{
		if (mi[i] > m[i])
			f = mi[i] / m[i];
		y[i] = mi[i] - (f*m[i]);
		while (((y[i]*z) % m[i] )!= a[i])
		{
			z++;
		}
		y[i] = z;
		z = 1;
		f = 0;
	}
	for (int i = 0; i < N; i++)
	{
		X = X + mi[i] * y[i];
	}
	cout << "\nanswer: ";
	cout << "X = "<<X;
	delete[]a;
	delete[]m;
	delete[]mi;
	delete[]y;
	return 0;
}
