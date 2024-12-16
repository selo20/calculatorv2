#define TRUE 1
#define FALSE 0
#include <stdio.h>

int main() {
    int x = 10;
    int *ptr = &x;

    printf("Value of x: %d\n", x);      // Prints the value of x
    printf("Address of x: %p\n", &x);   // Prints the address of x
    printf("Value of x (using pointer): %d\n", *ptr);  // Dereferences the pointer to get the value of x

    return 0;
}
