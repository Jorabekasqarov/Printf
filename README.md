# Printf
Custom Printf Function in C

# Description

This C program implements a custom my_printf function, inspired by the standard printf function, 
which allows formatting and printing of strings along with various data types. 
The function supports format specifiers for characters, strings, integers, pointers, hexadecimal, and octal numbers.

# Implementation

The my_printf function takes a format string and a variable number of arguments using the stdarg.h library. 
It iterates through the format string, searching for the '%' character to identify format specifiers. 
When a format specifier is found, the function extracts the corresponding argument from the variable argument list and processes it accordingly.

Supported Format Specifiers

%c: Prints a single character.
%s: Prints a null-terminated string.
%d or %u: Prints signed or unsigned decimal numbers, respectively.
%o: Prints numbers in octal format.
%p: Prints pointer addresses in hexadecimal format.
%x: Prints numbers in lowercase hexadecimal format.
%%: Prints a literal '%' character.

# Usage

To use the my_printf function, include the my_printf 
function declaration and the required libraries in your C program. 
The function behaves similarly to the standard printf function, 
allowing you to format and print data with the supported format specifiers.

Example Usage
c
Copy code
#include <stdio.h>

// Custom printf function declaration
int my_printf(char* place_holder, ...);

int main() {
    int test = 12;
    char* string = NULL;
    printf("string: %s\n", string); // Output: "string: (null)"
    int total = my_printf("%%\ns: %s \nc: %c\nint: %d\np: %p\nx: %x\no: %o\n",
    string, 'z', 15435, &test, 0x7fa, 100);

    printf("Total characters printed: %d\n", total); // Output: "Total characters printed: 49"
    return 0;
}

# Conclusion

The custom my_printf function provides a simple and flexible way to format and print various data types in C. 
By supporting commonly used format specifiers, this function enables C programmers to customize their output, 
making it a valuable addition to any C project. However, it's essential to ensure the correct usage of format 
specifiers to avoid potential issues like buffer overflows or incorrect output. Happy coding!
