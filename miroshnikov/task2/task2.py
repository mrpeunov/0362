def nod(num1, num2):
    num1 = abs(num1)
    num2 = abs(num2)
    while num1 != 0 and num2 != 0:
        if num1 >= num2:
            num1 %= num2
        else:
            num2 %= num1
    return num1 or num2

def Diofant(a, b, c, d):
    x, y = 0, 0
    if abs(c) % d != 0:
        print('Нет решений')
    else:
        a /= d
        b /= d
        c /= d
    if abs(a) >= abs(b):
        while (c - a * x) % b != 0:
            x += 1
        y = int((c - a * x) / b)
    elif abs(b) > abs(a):
        y += 1
        while (c - b * y) % a != 0:
            y += 1
        x = int((c - b * y) / a)
    print('Частное решение: X -', x, ', Y -', y)

    a = int(a)
    b = int(b)

    if b >= 0:
        print('X = ', x, '+', abs(b), 'S')
    else:
        print('X = ', x, '-', abs(b), 'S')
    if a >= 0:
        print('Y = ', y, '+', abs(a), 'S')
    else:
        print('Y = ', y, '-', abs(a), 'S')

    s = int(input('Введите параметр S: '))
    x = x + b * s
    y = y + a * s

    print('Решение: X -', x, ', Y -', y)

a = int(input('Введите a: '))
b = int(input('Введите b: '))
c = int(input('Введите c: '))
d = nod(a, b)
Diofant(a, b, c, d)