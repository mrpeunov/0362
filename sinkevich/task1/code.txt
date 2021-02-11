#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int main()
{
int k,n;
float p;
size_t i;
setlocale(LC_ALL, "RUS");
printf("Поиск всех простых чисел в промежутке от 1 до n\n");
printf("Введите n:");
scanf("%d", &n);
int *mass;
mass=(int*)malloc(n*sizeof(int));
for (i=2; i<=n; i++){
    mass[i]=i;
}
p=sqrt(n);
k=2;
int r=1;
while (r==1) {
r=0;
for (i=2; i<=n; i++){
    if ((mass[i]%k==0) && (mass[i]!=k)) {mass[i]=0;}
}

for (i=2; i<=n; i++){
    if ((mass[i]>k) && (mass[i]<p)) {k=mass[i]; r=1; break;}
}
}
printf("Список всех простых чисел на промежутке от 1 до %d: \n", n);
for (i=2; i<=n; i++) {
    if (mass[i]!=0) {printf("%d ", mass[i]);}
}
printf("\n");
free(mass);
 return 0;
}

