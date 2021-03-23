def Chineese_Theor(k, ost, mod):
    y = [0 for i in range(k)]     # массив слагаемых ответа
    c = 0
    mul = 1
    for i in range(k):            # считаем произведение модулей
        mul *= mod[i]
    for i in range(k):
        while c % (mul/mod[i]) != 0 or c % mod[i] != ost[i]:
            c += 1
        y[i] = c
        c = 0
    return sum(y)


k = int(input('Введите кол-во строк - '))
ost = [0 for i in range(k)]   # массив остатков
mod = [0 for i in range(k)]   # массив модулей
for i in range(k):
    ost[i], mod[i] = map(int, input('Введите через пробел пару: остаток и модуль - ').split())
print(Chineese_Theor(k, ost, mod))
