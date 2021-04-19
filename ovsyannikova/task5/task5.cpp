#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int toFactorialNumberSystem(int N);
int fromFactorialNumberSystem(int N);
int factorize(int N);

int nextPermByTheCurrent(int[], int);

int numFromPermAndAB(int[], int, int (*fromFact)(int));
int permFromNumAndAB(int, int pwr, int (*toFact)(int));

/* Программа работает только с алфавитом в виде последовательных десятичных цифр в промежутке [1, n], где n - введенная пользователем мощность алфавита.
 *
*/

int main() {
    int choice, result, N;
    cout << "Choose operation:" << endl;
    cout << "1 - converting from decimal to factorial notation" << endl;
    cout << "2 - converting from factorial to decimal notation" << endl;
    cout << "3 - getting the next permutation from the current one" << endl;
    cout << "4 - getting a number by permutation and alphabet" << endl;
    cout << "5 - getting a permutation by number and alphabet" << endl;
    cin >> choice;

    switch(choice){
        case 1: {
            cout << "Enter a number in decimal notation: ";
            cin >> N;
            result = toFactorialNumberSystem(N);
            break;
        }
        case 2: {
            cout << "Enter a number in factorial notation: ";
            cin >> N;
            result = fromFactorialNumberSystem(N);
            break;
        }
        case 3: {
            int n;
            cout << "Enter a number of elements in permutation: ";
            cin >> n;
            int a[n];
            cout << "Enter a permutation of one digit per line using \"Enter\": " << endl;
            for (int i = 0; i < n; i++){
                cin >> a[i];
            }
            result = nextPermByTheCurrent(a, n);
            break;
        }
        case 4: {
            int pwr;
            int (*fromFact)(int) = &fromFactorialNumberSystem;
            cout << "Enter an alphabet power: " << endl;
            cin >> pwr;
            int perm[pwr];
            cout << "Enter a permutation of one digit per line using \"Enter\": " << endl;
            for (int i = 0; i < pwr; i++){
                cin >> perm[i];
            }
            result = numFromPermAndAB(perm, pwr, fromFact);
            break;
        }
        case 5: {
            int num, pwr;
            int (*toFact)(int) = &toFactorialNumberSystem;
            cout << "Enter a number of permutation: " << endl;
            cin >> num;
            cout << "Enter an alphabet power: " << endl;
            cin >> pwr;
            result = permFromNumAndAB(num, pwr, toFact);
            break;
        }
        default: {
            cout << "Invalid value" << endl;
            result = 0;
            break;
        }
    }

    if (result != 0) cout << "Result: " << result << endl;

    return 0;
}

/* Функция toFactorialNumberSystem(int N)
 * На вход принимается N - значение числа в десятичной системе счисления.
 * Функция возвращает результат перевода числа в факториальную систему счисления.
 */
int toFactorialNumberSystem(int N){
    int result = 0;

    int ilast;
    for (int i = 2; i < N; i++){
        result += (int) (N % i) * pow(10, i - 2);
        N /= i;
        ilast = i;
    }

    result += N * pow(10, ilast - 1);

    return result;
}

/* Функция fromFactorialNumberSystem(int N)
 * На вход принимается N - значение числа в факториальной системе счисления.
 * Функция возвращает результат перевода числа в десятичную систему счисления.
 */
int fromFactorialNumberSystem(int N){
    int result = 0;

    for(int i = 0; N > 0; i++){
        result += (int)(N % 10) * factorize(i + 1);
        N /= 10;
    }

    return result;
}

/* Функция factorize(int N)
 * На вход принимается N - число, факториал, которого нужно рассчитать.
 * Функция возвращает результат факторизации числа.
 */
int factorize(int N){
    if (N < 0) return 0;
    if (N == 0) return 1;
    else return N * factorize(N - 1);
}

/* Функция nextPermByTheCurrent(int a[], int n)
 * На вход принимается a[] - массив элементов перестановки, n - количество элементов в перестановке.
 * Функция возвращает следующую перестановку, используя алгоритм Нарайаны.
 */
int nextPermByTheCurrent(int a[], int n){
    int result = 0, min;

    for (int i = n - 2; i >= 0; i--) {       // обходим перестановку справа, начиная с предпоследнего элемента
        if (a[i] < a[i + 1]){                  // ищем первый элемент, сосед которого справа больше
             min = i + 1;                      // запоминаем соседа справа
            for (int j = i + 2; j < n; j++) {    // находим такой номер j,что число a_j является наименьшим среди чисел с индексами [i + 1, n], превосходящим a_i.
                if (a[i] < a[j] && a[j] < a[min]) min = j;
            }

            swap(a[i], a[min]);     // меняем местами a_i и a_j
            reverse(&a[i+1], &a[n]); // изменяем порядок элементов, занимающих места [i + 1, n], на противоположный.

            break;
        }
        if (i == 0) reverse(&a[i], &a[n]); // тождественная перестановка является следующей для обратной.
    }

    for (int i = 0; i < n; i++){
        result += a[i] * pow(10, n - i - 1);
    }

    return result;
}

/* Функция numFromPermAndAB(int res[], int pwr, int (*fromFact)(int))
 * На вход принимается res[] - массив элементов перестановки, pwr - мощность алфавита, указатель на функцию fromFactorialNumberSystem(int N).
 * Функция возвращает номер перестановки по перестановке и алфавиту(его мощности).
 */
int numFromPermAndAB(int res[], int pwr, int (*fromFact)(int)){
    int number[pwr], fact[pwr], num = 0;

    for (int i = 0; i < pwr; i++) number[i] = i + 1;

    for (int i = 0; i < pwr; i++){
        for (int j = 0; j < pwr; j++){
            if (res[i] == number[j]){
                fact[i] = j;
                for (int k = j; k < pwr - 1; k++){
                    number[k] = number[k + 1];
                }
                number[pwr - 1] = 0;
            }
        }
    }

    for (int i = 0; i < pwr - 1; i++){
        num += fact[i] * pow(10, pwr - i - 2);
    }

    num = fromFact(num);
    num++;

    return num;
}

/* Функция permFromNumAndAB(int num, int pwr, int (*toFact)(int))
 * На вход принимается num - номер перестановки, pwr - мощность алфавита, указатель на функцию toFactorialNumberSystem(int N).
 * Функция возвращает перестановку по номеру и алфавиту(его мощности).
 */
int permFromNumAndAB(int num, int pwr, int (*toFact)(int)){
    int result = 0, number[pwr], fact[pwr], res[pwr];

    num--;
    num = toFact(num);

    for (int i = 0; i < pwr; i++){
        fact[i] = (int) num / pow(10,  pwr - 2 - i);
        num -= fact[i] * pow(10, pwr - 2 - i);
    }
    fact[pwr] = 0;

    for (int i = 0; i < pwr; i++) number[i] = i + 1;

    for (int i = 0; i < pwr; i++){
        for (int j = 0; j < pwr; j++){
            if (fact[i] == j){
                res[i] = number[j];
                for (int k = j; k < pwr - 1; k++){
                    number[k] = number[k + 1];
                }
                number[pwr - 1] = 0;
            }
        }
    }

    for (int i = 0; i < pwr; i++){
        result += res[i] * pow(10, pwr - i - 1);
    }

    return result;

}




