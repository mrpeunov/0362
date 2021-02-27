#include <iostream>
#include <vector>

using namespace std;

vector <int> Solve_Equation(int i_First_Number, int i_Second_Number, int i_Third_Number, int k)
{
	int i_Division_Result, i_Division_Remainder, i_temp;

	bool First_Negative = 0, Second_Negative = 0;
	
	if (i_First_Number < 0)
	{
		i_First_Number = -i_First_Number;
		First_Negative = 1;
	}

	if (i_Second_Number < 0)
	{
		i_Second_Number = -i_Second_Number;
		Second_Negative = 1;
	}

	if (i_First_Number > i_Second_Number)
	{
		i_Division_Remainder = i_First_Number;
		i_temp = i_Second_Number;
	}
	else
	{
		i_Division_Remainder = i_Second_Number;
		i_temp = i_First_Number;
	}

	vector <int> euclid_x = {1, 0};
	vector <int> euclid_y = {0, 1};

	while (i_temp != 0)
	{
		i_Division_Result = i_Division_Remainder / i_temp;
		i_Division_Remainder %= i_temp;

		i_Division_Remainder += i_temp;
		i_temp = i_Division_Remainder - i_temp;
		i_Division_Remainder = i_Division_Remainder - i_temp;

		euclid_x.push_back(euclid_x[0] - euclid_x[1] * i_Division_Result);
		euclid_x.erase(euclid_x.begin());

		euclid_y.push_back(euclid_y[0] - euclid_y[1] * i_Division_Result);
		euclid_y.erase(euclid_y.begin());
	}

	int temp_x = euclid_x[0];

	if (i_First_Number > i_Second_Number) euclid_x[0] *= (i_Third_Number / i_Division_Remainder);
	else euclid_x[0] = euclid_y[0] * (i_Third_Number / i_Division_Remainder);
	euclid_x[1] = i_Second_Number / i_Division_Remainder;

	if (i_First_Number > i_Second_Number) euclid_y[0] *= (i_Third_Number / i_Division_Remainder);
	else euclid_y[0] = temp_x * (i_Third_Number / i_Division_Remainder);
	euclid_y[1] = i_First_Number / i_Division_Remainder;

	if (First_Negative)
	{
		euclid_x[0] = -euclid_x[0];
		euclid_y[1] = -euclid_y[1];
	}

	if (Second_Negative)
	{
		euclid_x[1] = -euclid_x[1];
		euclid_y[0] = -euclid_y[0];
	}

	vector <int> result;

	result.push_back(euclid_x[0] + euclid_x[1] * k);
	result.push_back(euclid_y[0] - euclid_y[1] * k);

	return result;
}

int main()
{
	int i_First_Number, i_Second_Number, i_Third_Number, k;
	cin >> i_First_Number >> i_Second_Number >> i_Third_Number >> k;

	vector <int> result = Solve_Equation(i_First_Number, i_Second_Number, i_Third_Number, k);

	cout << "x = " << result[0] << ", y = " << result[1];

	return 0;
}