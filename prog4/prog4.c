#include <stdio.h>

// Structure with bitfields
struct Bitfield
{
    unsigned int firstbit : 1;   // 1-bit field
    unsigned int secondbit : 2;  // 2-bit field
    unsigned int thirdbit : 3;   // 3-bit field
};

int main()
{
    struct Bitfield a; // Declare structure variable

    // Assign values
    a.firstbit = 1;
    a.secondbit = 2;
    a.thirdbit = 5;

    // Display values
    printf("First bit = %u\n", a.firstbit);
    printf("Second bit = %u\n", a.secondbit);
    printf("Third bit = %u\n", a.thirdbit);

    return 0;
}