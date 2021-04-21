
# Функция нахождения всех подмножеств
# Принимает на вход массив значений(множество)
# Возвращает массив всех подмножеств(включая несобственные)


def all_subsets(set_1):
    subs = [[]]
    for i in set_1:
        for j in range(len(subs)):
            tmp_list = subs[j].copy()
            tmp_list.append(i)
            subs.append(tmp_list)
    return subs


# Функция нахождения всех подмножеств длины k
# Принимает на вход массив значений(множество)
# Возвращает массив всех подмножеств длины k(включая несобственные)


def k_subs(k, set_2):
    if k > len(set_2):
        return "No subsets of such length"
    subs = all_subsets(set_2)
    k_s = []
    for i in subs:
        if len(i) == k:
            k_s.append(i)
    return k_s


# Функция нахождения всех подмножеств, содержащих n
# Принимает на вход массив значений(множество)
# Возвращает массив всех подмножеств, содержащих n(включая несобственные)


def choose(n, set_3):
    if n not in set_3:
        return "No subsets containing this number"
    subs = all_subsets(set_3)
    c_s = []
    for i in subs:
        if n in i:
            c_s.append(i)
    return c_s


print("1 - find all subsets, 2 - find all k-length subsets, 3 - find all subsets containing n")
ch = int(input("Please, choose which function you'd like to test: "))
if ch == 1:
    user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
    print(all_subsets(user_set))
elif ch == 2:
    user_k = int(input('Please type in the length of the subset: '))
    user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
    print(k_subs(user_k, user_set))
elif ch == 3:
    user_n = int(input('Please type in the number which should be contained by subsets: '))
    user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
    print(k_subs(user_n, user_set))
else:
    while ch > 3 or ch < 1:
        ch = int(input("Incorrect input. Please, choose which function you'd like to test: "))
        if ch == 1:
            user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
            print(all_subsets(user_set))
        elif ch == 2:
            user_k = int(input('Please type in the length of the subset: '))
            user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
            print(k_subs(user_k, user_set))
        elif ch == 3:
            user_n = int(input('Please type in the number which should be contained by subsets: '))
            user_set = list(map(int, input("Please type in the set separating numbers with whitespace: ").split()))
            print(k_subs(user_n, user_set))
