n = int(input("Введите n: "))
a = []

for i in range(2, n + 1):
   for j in range(i + i, n + 1, i):
   if (j not in a): a.append(j)
for i in range(1, n + 1):
   if (i not in a): print(i)