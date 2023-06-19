#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    int x;
    if(n == 1) return 1;
    else{
        if(n == 2) return 1;
        else return fibonacci(n-1) + fibonacci(n-2);
    }
    return 0;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <n>\n", argv[0]);
        return 0;
    }
    
    int resp = 0;

    resp = fibonacci(atoi(argv[1]));
    printf("%d\n", resp);
    return 0;
}