#include <stdio.h>
#define print printf

int main(void){
    int x = 10;
    int *p = &x;  // p stores the address of x
    print("Value of x: %d\n", x);  // Prints the value of x
    print("Address of x: %p\n", p);  // Prints the address of x
}