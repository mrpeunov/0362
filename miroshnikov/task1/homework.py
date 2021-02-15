k = int(input())
a = [i for i in range(1, k + 1)]
c = []
print(k)
for i in range(k):
    for j in range(k):
        if a[i] % a[j] == 0 and a[i] > a[j] and a[j] != 1 and a[i] not in c:
            c.append(a[i])

for i in range(len(c)):
    a.remove(c[i])

del a[0]

print(a)
