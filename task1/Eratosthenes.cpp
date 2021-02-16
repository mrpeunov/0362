#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int a[n + 1];

	for (int i = 0; i < n + 1; i++)
	{
		a[i] = i;
	}

	for (int i = 2; i < n + 1; i++)
	{
		if (a[i] != 0)
		{
			cout << a[i] << ", ";
			for (int j = i * i; j < n + 1; j += i)
			{
				if (a[j] % i == 0)
				{
					a[j] = 0;
				}
			}
		}
	}

	return 0;
}