
def factorial(dec):        #Функия нахождения факториала, принимает на вход десятичное число
    fact = 1
    for i in range(1, dec + 1):
        fact *= i
    return fact

def dectofact(dec):             #функция перевода из десятичной в факториальную
    i = 2
    rems = []
    factn = ''
    while dec // i != 0:
        rems.append(str(dec % i))
        dec = dec // i
        i += 1
    rems.append(str(dec % i))
    i = 0
    for i in reversed(rems):
        factn += i
    factn = int(factn)
    return factn


def facttodec(fact):                #функция перевода из факториальной в десятичную
    dec = 0
    for i in range(1, len(str(fact)) + 1):
        dec += (fact % 10) * factorial(i)
        fact = fact // 10
    return dec


def ind(perm, alph):               #Функция нахождения номера заданного слова по алфавиту
    base = len(alph)
    perm = list(reversed(perm))
    indperm = 0
    for i in range(len(perm)):
        indperm += perm[i] * (base ** i)
    indperm += 1
    return indperm

def permstr(ind, alph):                #Функция нахождения перестановки по номеру и алфавиту
    i = 0
    j = 0
    permut = []
    ind = str(dectofact(ind - 1))
    factind = []
    for i in range(len(ind)):
        factind.append(int(ind[i]))
    for j in range(len(ind)):
        permut.append(alph[factind[j]])
        del alph[factind[j]]
    permut.append(alph[0])
    return permut





