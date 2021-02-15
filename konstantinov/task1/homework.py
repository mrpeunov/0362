def naturalchisla():

    x = int(input())

    if x>=2: 
    
        spisok = []

        for i in range(x + 1):
    
            spisok.append(i)

        spisok[1] = 0

        i = 2

        while i <= x:
   
            if spisok[i] != 0:
        
                j = i + i
                while j <= x:
            
                    spisok[j] = 0
           
                    j = j + i
   
            i += 1

        spisok = set(spisok)

        spisok.remove(0)
    
        print('Вот список простых чисел ')
    
        print(spisok)

        print('Введите любое число:')

        naturalchisla()

    else:
    
        print('Не существует простых чисел, которые меньше вашего. Введите другое число!')
        
        naturalchisla()

if __name__ == '__main__':
    naturalchisla()
