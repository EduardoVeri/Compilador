/* Um programa para calcular o mdc
    segundo o algoritmo de euclides. */

#include <stdio.h>
#include <stdlib.h>

int gcd (int u, int v)
{ 	
	if (v == 0) {return u;}
	else return gcd(v,u-u/v*v);
}

void main(int argc, char *argv[])
{	int x; int y;

    if(argc != 3) {
        printf("Uso: %s <int> <int>\n", argv[0]);
        exit(1);
    } 

	x = atoi(argv[1]); y = atoi(argv[2]);
    printf("gcd(%d,%d) = %d\n", x, y, gcd(x,y));

}