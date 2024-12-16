#include <stdio.h>

struct Address {
    char street[100];
    char city[50];
    int zip;
};

struct Student {
    char name[50];
    int age;
    struct Address address;  // Nested structure
};

int main() {
    struct Student student1 = {"Alice", 20, {"123 Main St", "Wonderland", 12345}};

    printf("Name: %s\n", student1.name);
    printf("City: %s\n", student1.address.city);  // Access nested structure
    return 0;
}
