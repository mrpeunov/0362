package com.company;
import java.util.ArrayList;
import java.util.Scanner;




public class Main {

 // Функция printArray выводит все подмножества заданного множества. N-мощность множества
    public static void printArray(int N) {
        Scanner con = new Scanner(System.in);
        ArrayList<String> arraylist = new ArrayList<>();   //Список элементов множества
        System.out.println("Введите элементы множества: ");
        for (int i = 0; i < N; i++) {
            arraylist.add(con.nextLine());
        }
        System.out.println("Все подмножества: ");
        System.out.print("NULL");
        int subSize = (int)Math.pow(2,N);        //Вычисление кол-ва подмножеств subSize = 2^n
        for (int i = 0; i < subSize; i++) {      //Цикл, работающий с каждым подмножеством
                for (int j = 0; j<N;j++){        //Цикл, работающий с каждым элементом пожмножества
                    if ((i & (1<<j))>0){         //(1<<j)=2^j. Проверка: если побитовое произведение операндов > 0,то
                        System.out.print(arraylist.get(j)+" "); //Переменная является элементом текущего подмножества
                    }
                }
            System.out.println();
        }
    }

    // Функция printK выводит все подмножества длины K заданного множества. N - мощность алфавита
    public static void printK(int N) {
        Scanner scanner = new Scanner(System.in);
        int count,res;  //count - счетчик единиц; res - число, равное шагу итерации;
        ArrayList<String> list = new ArrayList<>(); //список элементов множества
        System.out.println("Введите элементы множества: ");
        for (int i = 0; i < N; i++) {
            list.add(scanner.nextLine());
        }
        System.out.println("Введите значение длины подмножества: ");
        int k = scanner.nextInt();
        while (k <= 0 || k > N) {
            System.out.println("Ошибка ввода!");
            System.out.println("Введите значение длины подмножества: ");
            k = scanner.nextInt();
        }
        int size = (int)Math.pow(2,N);
        for (int i = 1; i<size;i++){  //Подсчет кол-ва единиц в двоичной записи числа числа, равному номеру шага итерации
            res = i;
            count=0;
            while (res  >0){
                if (res%2>0) count++;
                res /=2;
            }
            if (count==k){             // Если кол-во единиц номера шага итерации равен значению длины подмножества,
                for (int j=0; j<N;j++){    //Число равное шагу итерации является элементом подмножества заданной длины
                    if ((i & (1<<j))>0){
                        System.out.print(list.get(j)+" ");
                    }
                }
                System.out.println();
            }
        }
    }

    // Функция printSearch выводит все подмножества, содержащие заданный элемент. N-мощность множества
    public static void printSearch(int N){
        Scanner scan = new Scanner(System.in);
        ArrayList<String> data = new ArrayList<>(); //Список элементов множества
        ArrayList<String> ddata = new ArrayList<>(); //Список элементов без элемента, по которому осуществляется поиск
        System.out.println("Введите элементы множества: ");
        for (int i = 0; i < N; i++) {
            data.add(scan.nextLine());
        }
        System.out.println("Введите элемент, по которому нужно искать подмножества: ");
        int index = data.indexOf(scan.nextLine()); // извлечение индекса искомого элемента.
        if (index == -1) {     //Функция IndexOf возвращает -1, если элемент в списке не найден.
            System.out.println("Элемент не найден");
            return;
        }
        for (int i = 0; i<index;i++) ddata.add(data.get(i));  //Заполнение доп. списка значениями списка data без
        for (int i =index+1;i<N;i++) ddata.add(data.get(i));  //искомого элемента
        int size = (int) Math.pow(2,N-1);
        for (int i=0;i<size;i++){
            System.out.print(data.get(index)+" ");
            for (int j = 0; j<N-1;j++){          //то же самое, что и в функции printArray, только без искомого
                if ((i&(1<<j))>0) System.out.print(ddata.get(j)+" "); //элемента
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice = 1;
        System.out.print("Введите кол-во элементов множества: ");
        int N = scanner.nextInt();
         while (choice !=0){
             System.out.println("1. Вывод всех подмножеств");
             System.out.println("2. Вывод подмножеств длины k");
             System.out.println("3. Вывод подножеств с определенным элементом");
             System.out.println("0. Завершить операцию");
             System.out.println("Введите номер операции: ");
             choice = scanner.nextInt();
             switch (choice){
                 case 0:
                     scanner.close();
                     break;
                 case 1:
                     printArray(N);
                     break;
                 case 2:
                     printK(N);
                     break;
                 case 3:
                     printSearch(N);
                     break;
             }
         }
    }
}

