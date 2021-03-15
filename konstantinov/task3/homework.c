#include <stdio.h>
 
int main() {
    int m, n;
    
    scanf("%d %d", &m, &n);
    
    int k = m * n;
    
    if ( k < 0 ) {
        k *= -1;
    }
    
    for ( int i = 2; i < k; i++ ) {
        if ( m % i == 0 && n % i == 0 ) {
            m /= i;
            n /= i;
        }
    }
    
    printf("%d %d\n", m, n);
    
    return 0;
}