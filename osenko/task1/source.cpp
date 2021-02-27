#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	setlocale(LC_ALL, "ru");
	size_t g;
	int k;
	cin >> k;
	if (k < 0) { return 1; }
	if (k <= 2) { cout << "net"; return 2; }
	for (g = 2; g < k+1; g++) {
		if ((g % 2 != 0) && (g % 3 != 0) && (g % 5 != 0) && (g % 7 != 0)) {
			cout << g << " ";
			
		}
		if (g == 2 || g == 3 || g == 5 || g == 7) { cout << g << " "; }
	}
	return 0;
}
