def fnod(p, r):
    return p if r == 0 
    else fnod(r, m % r)

print("Введите коэфиценты вашего уравнения ниже: ")

a = int(input("a = "))
b = int(input("b = "))
c = int(input("c = "))
 
assert c != 0
 
fnod2 = fnod(abs(a), abs(b))
if c % fnod2:
    print("Критическая ошибка! Перезапустите программу!")
else:
    a //= fnod2
    b //= fnod2
    c //= fnod2
 
    for m in range(abs(a)):
        if ( c - b * m ) % a == 0:
            y = m
            x = ( c - b * y ) // a
            if x < 0:
                x += b
                y -= a
            print("Уравнение решено!")
            print("X =", x, "Y =", y)
            break
    else:
        print("Критическая ошибка! Перезапустите программу!")