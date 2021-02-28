#include <stdio.h>
#include <stddef.h>

int dioph(int *a, int *b, int *c);

int main(){
    int a, b, c;
    printf("Enter a, b, c: \n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    dioph(&a, &b, &c);
return 0;
}

int dioph(int *a, int *b, int *c) {
    size_t i, j;
    int arr[4][3]={{0, 0, 1}, {0}, {1, 0, 1}, {0, 1, 0}};
    int k, x1, y1, nx, ny, nod;
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
        if ((*c)%nod!=0) {
                printf ("No solution \n");
                return 0; }
        x1=arr[2][0]*(*c)/nod;
        y1=arr[3][0]*(*c)/nod;
        nx=(*b)/nod;
        ny=-(*a)/nod;

        printf("\nGeneral solution: \n");
        printf("x=%d%+dk \n", x1, nx);
        printf("y=%d%+dk \n\n", y1, ny);

        printf("Enter k: \n");
        scanf("%d", &k);

        printf("\nPartial solution for k=%d: \n", k);
        printf("x=%d \n", x1+nx*k);
        printf("y=%d \n", y1+ny*k);

    return 0;
    }


