#include<stdio.h>
#include"../lib/state.h"

int main(){

    char a[10] = {0,1,1,0,0,0,1,1,1,0};
    unsigned int n = 10;
    unsigned char rule = 30;
    unsigned int row = 1;
    unsigned int col = 9;
    char prox = proximo(a,row,col,rule,n);
    print("\n\nEstado esperado:0 ---- Proximo estado:%c\n\n",prox);
    return 0;
}