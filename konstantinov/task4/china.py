from functools import reduce
from operator import mul    

def kitay(n, a):
    s = 0
    prod = reduce(mul, n)
    for n_i, a_i in zip(n, a):
        p = prod // n_i
        s += a_i * inverse(p, n_i) * p
    return s % prod    

def inverse(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1:
        return 1
    while a > 1:
        q = a // b
        a, b = b, a % b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += b0
    return x1    

a=[]
print('Введите кол-во чисел')
a1=int(input())
print("Введите  числа")
for i in range(a1):
    a.append(int(input()))

n=[]
print('Введите кол-во чисел')
n1=int(input())
print("Введите  числа")
for i in range(n1):
    n.append(int(input()))

print(kitay(n, a)) 