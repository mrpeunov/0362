#include <iostream>
#include <vector>
using namespace std;

int GenVariety(vector<char> alphavite,int length)
{
	int i, zxc, j;
	for (i = 0, zxc = 1; i < length; i++)
		zxc *= 2;  
	for (i = 0; i < zxc; i++)
	{
		for (j = 0; j < length; j++)
		{
			if ((i >> j) & 1)
			{
				cout << alphavite[j];
			}
		}
		cout << endl;
	}
	return 0;
}

int GenVarietyKElements(vector<char> alphavite, int length, int k)
{
	int zxc = 1,j,turn = 0;
	for (size_t i = 0; i < length; i++)
	{
		zxc *= 2;
	}
	int* array = new int[zxc];
	for (size_t i = 1; i < zxc; i++)
	{
		j = i;
		turn = 0;
		while (j > 0)
		{
			if (j % 2 != 0)
			{
				turn++;
			}
			j /= 2;
		}
		array[i] = turn;
		if (array[i] == k)
		{
			for (int j = 0; j < length; j++)
			{
				if (i & (1 << j))
				{
					cout << alphavite[j];
				}
			}
			cout << endl;
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int length,k;
	vector<char> alphavite;
	char buffer;
	cout << "Введите длину алфавита!" << endl;
	cin >> length;
	for (size_t i = 0; i < length; i++)
	{
		cout << "Введите " << i + 1 << " член алфавита!" << endl;
		cin >> buffer;
		alphavite.push_back(buffer);
	}
	GenVariety(alphavite, length);
	cout << "Введите какие к-элементные подмножества нужно выводить!" << endl;
	cin >> k;
	GenVarietyKElements(alphavite, length, k);
	return 0;
}