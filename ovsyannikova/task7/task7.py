# Реализация считывания исходных данных
#  return
# message - сообщение, которое необходимо закодировать
# remaining_values - отсортированный список частот
# symbols_frequency - словарь символов с частотами


def enter():
    message = str(input("Enter the message, separating the letters with spaces: ")).split(' ')
    num = int(input("Enter number of symbols: "))
    symbols_frequency = {}
    for i in range(num):
        symbols_frequency[input("Enter symbol: ")] = int(input("Enter symbol's frequency: "))
    remaining_values = sorted(symbols_frequency.values(), reverse=True)
    return message, remaining_values, symbols_frequency


# Реализация алгоритма соединения символов и их частот
# symbols_frequency - словарь символов с частотами
# remaining_values - отсортированный список частот
#  return
# symbols_frequency - пополненный словарь символов с частотами


def connect(symbols_frequency, remaining_values):
    while len(remaining_values) > 2:
        last = rem_val[len(rem_val) - 1]
        seclast = rem_val[len(rem_val) - 2]
        symbols_frequency[get_key(symbols_frequency, seclast) + get_key(symbols_frequency, last)] = seclast + last
        remaining_values.append(seclast + last)
        remaining_values.remove(last)
        remaining_values.remove(seclast)
        remaining_values.sort(reverse=True)
    return symbols_frequency


# Реализация алгоритма присвоения символам уникального кода
# symbols_frequency - словарь символов с частотами
#  return
# symbols_code - словарь символов и их уникальных кодов


def disconnect(symbols_frequency):
    symbols_code = symbols_frequency.copy()
    symbols = sorted(symbols_frequency.values(), reverse=True)
    for i in range(0, len(symbols)):
        symbols[i] = get_key(symbols_frequency, symbols[i])
    symbols_code[symbols[0]] = '1'
    symbols_code[symbols[1]] = '0'
    for i in range(0, len(symbols)):
        count = 2
        for j in range(i + 1, len(symbols)):
            if symbols[j] in symbols[i]:
                count -= 1
                if -1 < count < 2 and i != j:
                    symbols_code[symbols[j]] = str(symbols_code[symbols[i]]) + str(count)
    return symbols_code


# Реализация алгоритма кодирования введенного сообщения
# message - сообщение, которое необходимо закодировать
# symbols_code - словарь символов и их уникальных кодов
#  return
# result - результат кодирования


def decrypt(message, symbols_code):
    for i in range(0, len(message)):
        message[i] = symbols_code[message[i]]
    result = ''.join(message)
    return result


# Реализация алгоритма получения ключа в словаре по его значению
# d - словарь
# value - значение
#  return
# k - ключ в словаре d по значению value


def get_key(d, value):
    for k, v in d.items():
        if v == value:
            return k


if __name__ == '__main__':
    msg, rem_val, symbf = enter()
    symbf = connect(symbf, rem_val)
    symbc = disconnect(symbf)
    res = decrypt(msg, symbc)
    print("\nResult: " + res)
