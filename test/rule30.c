#include<stdio.h>
#include"../lib/state.h"

int main(){

    unsigned char input[5][5] = {
        
        {0,0,0,0,0},
	{1,1,1,1,1},
        {1,1,1,0,0},
        {0,1,0,1,1},
        {0,0,1,0,0}
    };

    unsigned char states[5][5] = {
        
        {0,0,0,0,0},
        {0,0,0,0,0},
        {1,0,0,1,1},
        {0,1,0,1,0},
        {0,1,1,1,0}
    };

    int errors = 0;
    unsigned int n = 5;
    unsigned char rule = 30;
    unsigned char* ptr = &input[0][0];
    
    printf("\n\n");
    for(unsigned int i=0;i<5;i++){
        for(unsigned int j=0;j<5;j++){
            unsigned char state = proximo(ptr,i+1,j+1,rule,n);
            if(state == states[i][j]){
                printf("(%d,%d) EXITO\n",i+1,j+1);
            }
            else{
                printf("(%d,%d) FALLO\n",i+1,j+1);
                errors+=1;
            }
            printf("\tEstado esperado: %d\n",states[i][j]);
            printf("\tEstado calculado: %d\n\n",state);
        }
    }
    printf("Errores totales:%d\n\n",errors);
    return 0;
}
