#include <stdio.h>
#include <stddef.h>
#include <locale.h>

int diophforchtheor(int *a, int *b);
int chtheor(int cmx[4][100], int *n);

int main(){
    setlocale (LC_ALL, "Rus");
    int n, res;
    size_t i, j;
    int cmx[4][100];
    for (i=0; i<4; i++){
        for (j=0; j<n; j++) {
            cmx[i][j]=1; }}
    printf("Введите количество уравнений: ");
    scanf ("%d", &n);
    printf("\n");
    printf("x === c mod m\n\n");
    for (i=0; i<n; i++){
        printf("Введите с: ");
        scanf("%d", &cmx[0][i]);
        printf("Введите m: ");
        scanf("%d", &cmx[1][i]);
        printf("\n"); }
    res=chtheor(cmx, &n);
    if (res==000) {
        return 1; }
    else {printf("Ответ: x=%d\n", res);}
return 0;
}

int chtheor(int cmx[4][100], int *n){
    size_t i, j;
    int a, b;
    int k, x=0;
    k=*n;
    for (i=0; i<4; i++) {
        cmx[3][k]*=cmx[1][i];
        for (j=0; j<k; j++) {
            if (i!=j) {
                cmx[3][i]*=cmx[1][j]; }}}
    for (i=0; i<k; i++) {
        a=cmx[3][i];
        b=cmx[1][i];
        cmx[2][i]=diophforchtheor(&a, &b);
        if (cmx[2][i]==00000) {
            printf("Нет решений\n");
            return 000;}
        x=x+cmx[0][i]*cmx[2][i]*cmx[3][i]; }
    x=x%(cmx[3][k]);
    if (x<0) {
        x=cmx[3][k]+x; }
return x;
}

int diophforchtheor(int *a, int *b) {
    size_t i, j;
    int arr[4][3]={{0, 0, 1}, {0, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    int x1, nod;
    if (a>b) {
    arr[0][0]=*a;
    arr[0][1]=*b;}
    else {
    arr[0][0]=*b;
    arr[0][1]=*a;}
    while (arr[0][2]!=0) {
        for (i=0; i<4; i++){
            arr[i][2]=0; }
        arr[0][2]=arr[0][0]%arr[0][1];
        arr[1][1]=arr[0][0]/arr[0][1];
        arr[2][2]=arr[2][0]-arr[2][1]*arr[1][1];
        arr[3][2]=arr[3][0]-arr[3][1]*arr[1][1];
        for (i=0; i<4; i++){
                arr[i][0]=0;}
        for (i=0; i<4; i++){
              for (j=0; j<2; j++){
                    arr[i][j]=arr[i][j+1]; }} }
    nod=arr[0][0];
    if (nod!=1) {
        return 000000; }
    x1=arr[2][0];
    return x1;
}

