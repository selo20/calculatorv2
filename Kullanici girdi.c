#include <stdio.h>

int main(){
    int a,b,c,carpim;
    printf("Lutfen sayilari giriniz: ");
    scanf("%d %d %d",&a,&b,&c);
    carpim = a*b*c;
    printf("Sayilarin carpimi: %d",carpim);
    return 0;
}