
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;

public class HuffmanCode {

    class Node implements Comparable<Node>{ //класс, работающий с узлами дерева символов
        int sum;
        String code;

        void buildCode(String code){
            this.code = code;
        }

        @Override
        public int compareTo(Node o) {
            return Integer.compare(sum, o.sum);
        }
    }

    class InternalNode extends Node{  //класс, кодирующий символы
        Node left;
        Node right;

        @Override
        void buildCode(String code){ //функция, кодирующий символ
            super.buildCode(code);
            left.buildCode(code + "0");
            right.buildCode(code + "1");
        }
        public InternalNode(Node left, Node right) {
            this.left = left;
            this.right = right;



            sum = left.sum + right.sum;
        }
    }

    class LeastNode extends Node{ //класс, который вывод таблицу символов
        char symbol;

        @Override
        void buildCode(String code){
            super.buildCode(code);
            System.out.println(symbol + ":" + code);
        }

        public LeastNode(char symbol, int count) {
            this.symbol = symbol;
            sum = count;
        }
    }
    private void run (){ //основная функция ввода/вывода и исполнения алгоритма
        Scanner input = new Scanner(System.in);
        System.out.println("Введите сообщение: ");
        String s = input.next();
        Map<Character,Integer> count = new HashMap<>();
        for(int i = 0; i<s.length();i++){ //подсчет частоты символов в строке
            char c = s.charAt(i);
            if (count.containsKey(c)){
                count.put(c, count.get(c)+1);
            } else {
                count.put(c,1);
            }
        }
        Map<Character, Node>charNodes = new HashMap<>(); //Хэш-таблица для кодирования сообщения
        PriorityQueue<Node> priorityQueue = new PriorityQueue<>(); //Ставит приоритет присоединения символов, на
        for(Map.Entry<Character, Integer> entry : count.entrySet()){ //основе частоты: чем меньше частота, тем выше
            LeastNode node = new LeastNode(entry.getKey(), entry.getValue()); //приоритет
            charNodes.put(entry.getKey(),node);
            priorityQueue.add(node);
        }
        while (priorityQueue.size() > 1){
            Node first = priorityQueue.poll();
            Node second = priorityQueue.poll();
            priorityQueue.add(new InternalNode(first,second));
        }

        Node root = priorityQueue.poll();
        if (count.size()==1){
            root.code = "0";
        } else {
            root.buildCode("");
        }
        String result = "";
        for(int i = 0; i<s.length();i++) {
            char c = s.charAt(i);
            result +=charNodes.get(c).code;
        }
        System.out.println("Закодированная строка: "+result);

    }


    public static void main(String[] args){
        new HuffmanCode().run();
    }
}
