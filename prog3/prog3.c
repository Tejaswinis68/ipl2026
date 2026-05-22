#include<stdio.h>

// Function to print bits of an integer
void printBits(int n)
{
    int i;

    for(i = 31; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);
    }

    printf("\n");
}

// Function to count number of 1 bits
int countOneBits(int n)
{
    int count = 0;

    while(n)
    {
        count += (n & 1);
        n = n >> 1;
    }

    return count;
}

// Function to check endian
void checkEndian()
{
    int n = 1;
    
    char *ptr = (char*)&n;

    if(*ptr == 1)
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
}

// Function to print bits of float
void printFloatBits(float f)
{
    int *ptr = (int*)&f;
    int i;

    for(i = 31; i >= 0; i--)
    {
        printf("%d", (*ptr >> i) & 1);
    }

    printf("\n");
}

int main()
{
    int num;
    float fnum;

    // Integer bits
    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("\nBits of integer %d:\n", num);
    printBits(num);

    // Count 1 bits
    printf("Number of 1 bits = %d\n",
           countOneBits(num));

    // Endian check
    printf("\nChecking Endian Format:\n");
    checkEndian();

    // Negative integer bits
    printf("\nBits of negative integer (%d):\n",
           -num);
    printBits(-num);

    // Float bits
    printf("\nEnter floating point number: ");
    scanf("%f", &fnum);

    printf("\nBits of float %.2f:\n",
           fnum);
    printFloatBits(fnum);

    // Negative float bits
    printf("\nBits of negative float %.2f:\n",
           -fnum);
    printFloatBits(-fnum);

    return 0;
}