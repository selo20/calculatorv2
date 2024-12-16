#include <stdio.h>

void main(){
    char infoLog[512];
    int size = sizeof(infoLog);

    infoLog[0] = 'a';
    infoLog[1] = 'b';
    
    for(int i=0; i<2;i++){
        printf("%c",infoLog[i]);
    }
    printf("%d",size);
}