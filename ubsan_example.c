#include <limits.h>
#include <stdio.h>

int main() {
    // Undefined Behavior 1: Signed integer overflow
    printf("--- Test 1: Signed Integer Overflow ---\n");
    int a = INT_MAX;
    int b = 1;
    int result = a + b;
    printf("INT_MAX + 1 = %d\n",
           result); // This line won't be reached if UBSan is enabled and set to abort

    // Undefined Behavior 2: Division by zero
    printf("\n--- Test 2: Division by Zero ---\n");
    int x = 10;
    int y = 0;
    int division = x / y;
    printf("10 / 0 = %d\n", division);

    // Undefined Behavior 3: Invalid left shift
    printf("\n--- Test 3: Invalid Left Shift ---\n");
    int z = 1;
    int shift_amount = 32; // Assuming a 32-bit integer
    int shifted = z << shift_amount;
    printf("1 << 32 = %d\n", shifted);

    // Undefined Behavior 4: Dereferencing a NULL pointer
    printf("\n--- Test 4: Dereferencing a NULL Pointer ---\n");
    int *ptr = NULL;
    // int val = *ptr; // This line is commented out to prevent a crash without UBSan
    // printf("Value: %d\n", val);

    return 0;
}
