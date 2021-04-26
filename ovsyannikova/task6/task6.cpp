#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void allSubsets(char [], int, int, char *);

void kElementSubsets(int, int, char *, int [], int);

void subsetsWithKElement(int, int, char *, int [], char);

int fact(int N);

int main() {
    int choice, pwr;

    cout << "Choose operation:\n" << endl;
    cout << "1 - Generation all subsets" << endl;
    cout << "2 - Generation k - element subsets" << endl;
    cout << "3 - Generation all subsets containing a particular element" << endl;
    cin >> choice;

    cout << "Enter a power of set: ";
    cin >> pwr;
    char set[pwr];
    int subpwr = pow(2, pwr);
    char c[subpwr][pwr];
    cout << "Enter the elements of set one by one using \"Enter\": " << endl;
    for (int i = 0; i < pwr; i++) {
        cin >> set[i];
    }

    allSubsets(set, pwr, subpwr, &c[0][0]);

    switch (choice) {
        case 1 : {
            cout << endl;
            cout << "All subsets generation:" << endl;
            cout << "Empty subset" << endl;
            for (int i = 1; i < subpwr; i++) {
                for (int j = 0; j < pwr; j++) {
                    if (c[i][j] != '_') cout << c[i][j];
                }
                cout << endl;
            }
            break;
        }
        case 2 : {
            int n;
            cout << "Enter size of subsets: ";
            cin >> n;
            int flag[fact(pwr) / (fact(n) * fact(pwr - n))];
            kElementSubsets(pwr, subpwr, &c[0][0], flag, n);
            cout << endl;
            cout << "Subsets of size " << n << ":" << endl;
            for (int i = 0; i < fact(pwr) / (fact(n) * fact(pwr - n)); i++) {
                for (int j = 0; j < pwr; j++) {
                    if (c[flag[i]][j] != '_') cout << c[flag[i]][j];
                }
                cout << endl;
            }

            break;
        }
        case 3 : {
            char n;
            cout << "Enter particular element: ";
            cin >> n;
            int flag[subpwr] = {0};
            subsetsWithKElement(pwr, subpwr, &c[0][0], flag, n);
            cout << endl;
            cout << "Subsets containing element " << n << ":" << endl;
            for (int i = 0; i < subpwr; i++) {
                if (flag[i] != 0) {
                    for (int j = 0; j < pwr; j++) {
                        if (c[i][j] != '_') cout << c[i][j];
                    }
                    cout << endl;
                }
            }

            break;
        }
        default: {
            cout << "Invalid value" << endl;
            break;
        }
    }

    return 0;
}

/* Реализация алгоритма генерации всех подмножеств
 * set[] - массив элементов множества
 * pwr - мощность множества
 * subpwr - число подмножеств
 * c - двумерный массив для хранения подмножеств.
 * return всевозможные подмножества
 */
void allSubsets(char set[], int pwr, int subpwr, char *c) {
    int bin;
    for (int i = 0; i < subpwr; i++) {
        bin = i;
        for (int j = 0; j < pwr; j++) {
            int k = pow(2, j + 1);
            if ((bin % k) % 2 != 0) c[i * pwr + pwr - 1 - j] = set[pwr - 1 - j];
            else c[i * pwr + pwr - 1 - j] = '_';
            bin /= 2;
        }
    }

}

/* Реализация алгоритма генерации подмножеств определенного размера
 * pwr - мощность множества
 * subpwr - число подмножеств
 * c - двумерный массив для хранения подмножеств
 * flag - массив, в котором единицей отмечаются подмножества нужного размера
 * n - заданный размер
 * return подмножества заданного размера
 */
void kElementSubsets(int pwr, int subpwr, char *c, int flag[], int n) {
    int counter2 = -1;
    for (int i = 0; i < subpwr; i++) {
        int counter = 0;
        for (int j = 0; j < pwr; j++) {
            if (c[i * pwr + j] != '_') counter++;
        }
        if (counter == n) {
            counter2++;
            flag[counter2] = i;
        }

    }
}

/* Реализация алгоритма генерации подмножеств, содержащих определенный элемент
 * pwr - мощность множества
 * subpwr - число подмножеств
 * c - двумерный массив для хранения подмножеств
 * flag - массив, в котором единицей отмечаются подмножества, содержащие нужный элемент
 * n - заданный элемент
 * return подмножества, содержащие  заданный элемент
 */
void subsetsWithKElement(int pwr, int subpwr, char *c, int flag[], char n) {
    for (int i = 0; i < subpwr; i++) {
        for (int j = 0; j < pwr; j++) {
            if (c[i * pwr + j] == n) flag[i] = 1;
        }
    }
}

//return факториал числа
int fact(int N) {
    if (N < 0) return 0;
    if (N == 0) return 1;
    else return N * fact(N - 1);
}


