/*
  P.S 
  К сожалению, программа плохо работает для больших чисел, так как проверка совпадения текущей дроби с "top" плохо продумана, 
  основная функция не возвращает значения, а просто их выводит. Сделала, как смогла.
  
*/
#include <iostream>

#include <cmath>

#include <cstddef>

using namespace std;

void continuedFraction(int l);

//создадим двусвязный список
// после каждого шага будем сохранять данные в структуру
struct i {
   float num; // дробь
   int wp;    // ее целая часть
   i * next;
   i * prev;
};

int main() {
   int N;
   size_t j;
   cin >> N;
   for (j = 1; j * j <= N; j++) continuedFraction(j);

   return 0;
}

void continuedFraction(int l){
   i * back, * top;
   int flag = 0;  //для того, чтобы пропустить сравнение дроби в top с самой собой

// создание и заполнение первого узла двусвязного списка, создание второго
      top = new i;
      back = top;
      back -> prev = 0;
      back -> num = sqrt(l);
      back -> wp = (int) sqrt(l);
      back -> next = new i;
      back -> next -> prev = back;
      back = back -> next;
      back -> next = 0;
   
// заполнение и создание последующих
   while (back -> prev -> num - back -> prev -> wp != 0) {
    // заполнение
      back -> num = 1 / (back -> prev -> num - back -> prev -> wp);
      back -> wp = (int) back -> num;

    // проверка совпадения текущей дроби с top
      if (flag != 0 && (abs(back -> num - top -> next -> num) < 0.1)) {
        // удаление последнего узла и выход из цикла
        back = back -> prev;
        delete back -> next;
        back -> next = 0;
        break;
      }
      
    //создание следующего узла
      back -> next = new i;
      back -> next -> prev = back;
      back = back -> next;
      back -> next = 0;

      flag = 1;

      }

    //вывод разложения
      cout << l << " = ";
      cout << "[" << top -> wp << "; ";
      top = top -> next;
      if (top -> wp != 0){
        cout << "(" ;
        do {  
          cout << top -> wp;
          if (top -> next != 0) cout <<", ";
          top = top -> next; 
        } while (top);
        cout << ")]" << endl;
    } else cout << "(0)]" << endl; 
     
}



