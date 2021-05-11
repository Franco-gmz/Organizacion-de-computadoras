#include<stdio.h>


unsigned char proximo(unsigned char*,unsigned int,unsigned int,unsigned char,unsigned int);

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

    unsigned char indice = (left<<2)|(center<<1)|right; // 0 0 0 0 0 L C R
    
    return (regla>>indice)&1;   //regla[indice]

}

int main(){

    unsigned char input[5][5] = {

        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}

    };

    unsigned char expected_output[5][5] = {

        {0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 1, 0}

    };

    int errors = 0;
    unsigned int n = 5;
    unsigned char rule = 30;
    unsigned char* ptr = &input[0][0];


    printf("\n\n");
    for(unsigned int i=0;i<4;i++){
        for(unsigned int j=0;j<5;j++){
            
            input[i+1][j] = proximo(ptr,i,j,rule,n);
            if(input[i+1][j] == expected_output[i+1][j]){
                printf("(%d,%d) EXITO\n",i,j);
            }
            else{
                printf("(%d,%d) FALLO\n",i,j);
                errors+=1;
            }
            printf("\tEstado esperado: %d\n",expected_output[i+1][j]);
            printf("\tEstado calculado: %d\n\n",input[i+1][j]);
        }
    }
    printf("Errores totales:%d\n\n",errors);
    return 0;

}

/*

int main(){

    unsigned char input[5][5] = {
        
        {'0','0','0','0','0'},
        {'1','1','1','1','1'},
        {'1','1','1','0','0'},
        {'0','1','0','1','1'},
        {'0','0','1','0','0'}
    };

    unsigned char states[5][5] = {
        
        {'0','0','0','0','0'},
        {'0','0','0','0','0'},
        {'1','0','0','1','1'},
        {'0','1','0','1','0'},
        {'0','1','1','1','0'}
    };

    int errors = 0;
    unsigned int n = 5;
    unsigned char rule = 30;
    char* ptr = &input[0][0];
    
    printf("\n\n");
    for(unsigned int i=0;i<5;i++){
        for(unsigned int j=0;j<5;j++){
            char state = proximo(ptr,i+1,j+1,rule,n);
            if(state == states[i][j]){
                printf("(%d,%d) EXITO\n",i+1,j+1);
            }
            else{
                printf("(%d,%d) FALLO\n",i+1,j+1);
                errors+=1;
            }
            printf("\tEstado esperado: %c\n",states[i][j]);
            printf("\tEstado calculado: %c\n\n",state);
        }
    }
    printf("Errores totales:%d\n\n",errors);
    return 0;
} */