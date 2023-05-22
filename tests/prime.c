#include <stdio.h>


static int num = 127;

int main() {
    for(int i=0; i*i <= num; i++) {
        if (num % i == 0) {
            printf("%d is not a prime", num);
            return 0;
        } 
    }
    printf("%d is a prime", num);
    return 0;
}