#include <stdio.h>

void main(){
    unsigned char r=0,g=0,b=0;
    while (1){    
        if(r == 255){
            g++;
        }
        if (g==255)
        {
            b++;
        }
        printf("%c %c %c",r,g,b);
        r++;
    }    
}