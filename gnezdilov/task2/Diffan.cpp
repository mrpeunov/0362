
#include <stdio.h>
#include <stdlib.h>
int a, b, c, d,nod, k, q, r, x, y, x1, y1;
int gcd(int a1, int b1) {
    if (a1 >= b1) {
        q = a1 / b1;
        r = a1 % b1;
    }
    else
        if (a1 <= b1) {
            q = b1 / a1;
            r = b1 % a1;
        }
    if (r == 0) d = q;
    while (r != 0) {
        a1 = b;
        b1 = r;
        nod = r;
        r = a1 % b1;
    }
    return nod;
}
int main()
{
    int i, a0, b0;
    printf("Enter a, b, c separated by a space: ");
    scanf("%d%d%d", &a, &b, &c);
    a0 = a;
    b0 = b;
    d = gcd(a, b);
    if ((a % d == 0) && (b % d == 0) && (c % d == 0)) {
        a /= d;
        b /= d;
        c /= d;
        d = gcd(a, b);
        if (a > b) {
            for (i = 0; i < b; i++) {
                if ((c - a * i) % b == 0){
                    y1 = (c - a * i) / b;
                    x1 = i;
                }
            }
        }
        else if (b > a) {
                for (i = -1; i < a; i++) {
                    if ((d - b * i) % a == 0) {
                        x1 = (d - b * i) / a;
                        y1 = i;
                    }
                }
            }
        x1 *= c;
        y1 *= c;
        printf("x = %d + %dk\n",x1,b/d);
        printf("y = %d - %dk\n",y1,a/d);
        printf("Enter k: ");
        scanf("%d", &k);
        x = x1 + b * k / d;
        y = y1 - a * k / d;
        printf("x = %d\ny = %d", x, y);
    }
    return 0;
}


