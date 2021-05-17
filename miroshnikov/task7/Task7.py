import heapq  # модуль для работы с мин. кучей
from collections import Counter  # словарь в котором для каждого объекта поддерживается счетчик
from collections import namedtuple


# класс для ветвей дерева - внутренних узлов; у них есть потомки:

class Node(namedtuple("Node", ["left", "right"])):
    def walk(self, code, acc):
        self.left.walk(code, acc + "0")
        self.right.walk(code, acc + "1")


# класс для листьев дерева, у него нет потомков, но есть значение символа

class Leaf(namedtuple("Leaf", ["char"])):
    def walk(self, code, acc):
        code[self.char] = acc or "0"


# функция кодирования строки в коды Хаффмана:

def huffman_encode(message):
    h = []
    for ch, freq in Counter(message).items():
        h.append((freq, len(h), Leaf(ch)))
    heapq.heapify(h)
    count = len(h)
    while len(h) > 1:
        freq1, _count1, left = heapq.heappop(h)
        freq2, _count2, right = heapq.heappop(h)
        heapq.heappush(h, (freq1 + freq2, count, Node(left, right)))
        count += 1
    code = {}
    if h:
        [(_freq, _count, root)] = h
        root.walk(code, "")
    return code


s = input('Введите сообщение: ')
code = huffman_encode(s)
encoded = "".join(code[ch] for ch in s)
print('Таблица символов: ')
for ch in sorted(code):
    print("{}: {}".format(ch, code[ch]))
print('Закодированное сообщение: ', encoded)
