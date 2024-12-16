#include <stdio.h>

typedef printf print;

int main(){
    int a,b,c,carpim;
    print("Lutfen sayilari giriniz: ");
    scanf("%d %d %d",&a,&b,&c);
    carpim = a*b*c;
    print("Sayilarin carpimi: %d",carpim);
    return 0;
}