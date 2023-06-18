#include <stdio.h>

int main(void)
{
    int fat; int n;
    n = 5;
    fat = 1;
    while(n > 1){
        fat = fat*n;
        n = n - 1;
    }

    printf("%d\n", fat);
    return 0;
}