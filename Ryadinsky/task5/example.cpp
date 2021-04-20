#include <iostream>
#include <vector>
using namespace std;

int in_factorial(int n)
{
	int num=1, turn = 1,zxc,t,N;
	zxc = n;
	int* array;
	while (n > num)
	{
		num = num * turn;
		turn++;
	}
	turn=turn-2;
	N = turn;
	array = new int[N];
	num = 1;
	for (int i = 1; i < N+1; i++)
	{
		num = num * i;

	}
	for (int i = 0; i < N; i++)
	{
		t = zxc / num;
		array[i] = t;
		if (t != 0)
		{
			zxc = zxc - (num*t);
		}
		num = num / turn;
		turn--;
	}
	
	for (int i = 0; i < N; i++)
	{
		cout << array[i];
	}
	cout << endl;
	delete[] array;
	return 0;
}

int in_desat(int *array,int number)
{
	int num=0,turn=number,x=1;
	for (size_t i = 0; i < number; i++)
	{
		for (size_t i = 1; i <= turn; i++)
		{
			x = x * i;
		}
		num =num + array[i] * x;
		turn--;
		x = 1;
	}
	cout << num << endl;
	return 0;
}

int perest_nom(vector<int> array,int number,int n)
{
	n = n - 1;
	int fact = 2,c;
	int* mas = new int[number];
	int* result = new int[number];
	for (size_t i = 1; i < number; i++)
	{
		mas[i] = n % fact;
		n = n / fact;
		fact++;
	}
	for (int i = 0; i < (number / 2); i++) {
		c = mas[i];
		mas[i] = mas[number - 1 - i];
		mas[number - 1 - i] = c;
	}
	mas[number - 1] = 0;

	for (size_t i = 0; i < number; i++)
	{
		result[i] = array[mas[i]];
		array.erase(array.begin() + mas[i]);
	}
	for (size_t i = 0; i < number; i++)
	{
		cout << result[i];
	}
	cout << endl;
	return 0;
}


int main()
{
	setlocale(LC_ALL, "rus");
	int number,n;
	cout << "1)Введите число которое надо перевести из десятичной в факториальную СС!" << endl;
	cin >> number;
	in_factorial(number);

	cout << "2)Введите сколько значений у вашего числа!"<<endl;
	cin >> number;
	int* array = new int[number];
	cout << "2)Введите посимвольно число которое надо перевести из факториальной СС в десятичную!" << endl;
	for (size_t i = 0; i < number; i++)
	{
		cin>>array[i];
	}
	in_desat(array, number);
	delete[] array;

	cout << "5)Введите длину алфавита!" << endl;
	cin >> number;
	vector<int>array_1;
	cout << "5)Введите алфавит в лексикографическом порядке!" << endl;
	for (size_t i = 0; i < number; i++)
	{
		cin >> n;
		array_1.push_back(n);
	}
	cout << "5)Введите номер перестановки" << endl;
	cin >> n;
	perest_nom(array_1,number,n);

	return 0;
}