#include<iostream>

using namespace::std;
struct Node
{
	int Data;
	
	Node* Next;
	Node* Prev;
};
struct Node2
{
	
	int Data;
	Node2* Next;
	Node2* Prev;
};
int factorial(Node* p, int z)
{
	if (z != 0)
	{
		p->Data = p->Data * z;
		z--;
		factorial(p, z);
	}
	return p->Data;
}
void factorial_to_CC()
{
	int x;
	Node* Head, * Tail, * p;
	Head = Tail = new Node;
	Head->Prev = Tail->Next = 0;
	cin >> x;
	Head->Data = x;

	p = Head;

	while (1)
	{
		cin >> x;
		if (x == -1)
			break;
		Tail->Next = new Node;
		Tail = Tail->Next;
		Tail->Data = x;
		Tail->Prev = p;
		p = Tail;
	}
	Tail->Next = 0;
	p = Tail->Prev;
	int z = 2;
	int sum = Tail->Data;
	while (p)
	{
		p->Data = factorial(p, z);
		sum = sum + p->Data;
		p = p->Prev;
		z++;
	}
	cout << sum;
}
void CC_to_fatorial(int x,Node*&Head,Node*&Tail)
{
	int i = 2;
	Node * p;
	Head->Prev = Tail->Next = 0;
	Head->Data = x % i;
	x = x / i;
	p = Head;
	i++;
	while (x != 0)
	{
		Tail->Next = new Node;
		Tail = Tail->Next;
		Tail->Data = x % i;
		Tail->Prev = p;
		p = Tail;
		x = x / i;
		i++;
	}
	Tail->Next = 0;
}
void Node2_fill(int y,Node2*& Head2, Node2*& Tail2)
{
	Node2* p;
	Head2->Data = 1;
	p = Head2;
	for(int i=2;i<=y;i++)
	{
		Tail2->Next = new Node2;
		Tail2 = Tail2->Next;
		Tail2->Data = i;
		Tail2-> Prev = p;
		p = Tail2;
	}
	Tail2->Next = 0;
}
void punkt_5(Node* Head, Node* Tail, Node2* Head2, Node2* Tail2)
{
	Node* p;
	Node2* p2, * middle, * n, * b, * a;
	p = Tail;
	while (p)
	{
		p2 = Head2;
		if (p->Data == 0)
		{
			cout << p2->Data << " ";
			p2 = p2->Next;
			p2->Prev = 0;
			delete Head2;
			Head2 = p2;
		}
		else
		{
			for (int i = 0; i < p->Data - 1; i++)
			{
				p2 = p2->Next;
			}
			if (p2->Next != 0)
			{
				cout << p2->Next->Data << " ";
				
					middle = p2->Next;
					b = p2;
					if (middle->Next != 0)
					{
						n = middle->Next;
						b->Next = n;
						n->Prev = b;
						delete middle;
					}
					else
						b->Next = 0;
				
			}
		}
		p = p->Prev;
	}
	if (Head2 != 0)
		cout << Head2->Data;
}

int main()
{
	Node* Head, * Tail, * p;
	Node2* Head2, * Tail2, * p2;
	Head = Tail = new Node;
	Head2 = Tail2 = new Node2;
	setlocale(LC_ALL, "Russian");
	int x;
	cout << "1.Перевод числа из десятичной СС в факториальную\n";
	cout << "2.Из факториальной в десятичную СС.\n";
	cout << "3.Получение перестановки по номеру и алфавиту\n";
	cout << "Введите цифру:";
	cin >> x;
	switch (x)
	{
	case 1:
	{
		int  y;
		cout << "\nВведите десятичное число:";
		cin >> y;
		CC_to_fatorial(y, Head, Tail);
		p = Tail;
		while (p)
		{
			cout << p->Data << " ";
			p = p->Prev;
		}
		break;
	}
	case 2:
	{
		cout << "Вводите числа через пробел(чтобы разделить  единичные числа от десятков\n";
		cout << "при конце ввода напишите -1 \n";
		factorial_to_CC();
		break;
	}
	case 3:
	{
		int y;
		cout << "Введите номер перестановки и длину цифр(1 максимальную цифру):";
		cin >> x >> y;
		x--;
		Node2_fill(y, Head2, Tail2);
		CC_to_fatorial(x, Head, Tail);
		punkt_5(Head, Tail, Head2, Tail2);
	}
	}
	return 0;
}