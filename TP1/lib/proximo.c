#include<stdio.h>

unsigned char proximo(unsigned char* a,unsigned int i,unsigned int j,unsigned char regla,unsigned int N) {

    unsigned char center = *(a + N*i + j); //input[i][j]

    unsigned char left;
    if(j == 0)
        left = *(a + N*i + N-1);    //input[i][N-1]
    else 
        left = *(a + N*i + j-1);   //input[i][j-1]

    unsigned char right;
    if(j == N-1)
        right = *(a + N*i + 0);     //input[i][0]
    else 
        right = *(a + N*i + j+1);  //input[i][j+1]

    unsigned char indice = (unsigned char)((left<<2)|(center<<1)|right); // 0 0 0 0 0 L C R
    
    return (regla>>indice)&1;   //regla[indice]

}
