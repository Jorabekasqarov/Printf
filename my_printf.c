#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int my_printf(char* place_holder, ...);
int my_strlen(char* str);
char* my_itoa(int num);
int my_putstr(char* str);
int my_putchar(char c);
char* ptr_to_str(long addr);
char* hex_to_str(unsigned int num, char up_or_low);
char* dec_to_oct(int dec_num);

/*
int main() {
    int test = 12;
    char* string = NULL;
    printf ("string: %s\n", string);
    int total = my_printf("%%\ns: %s \nc: %c\nint: %d\np: %p\nx: %x\no: %o\n",
    string, 'z', 15435, &test, 0x7fa, 100);
    printf("total: %d\n", total);
    return total;
}
*/

int my_printf(char* format, ...) {
    va_list args;
    int length = my_strlen(format);
    int char_count = 0;
    va_start(args, format);
    for (int i = 0; i < length; i++) {
        if (format[i] == '%') {
            i++;
            switch(format[i]) {
                case 'c': {
                    char var = va_arg(args, int);
                    char_count += 1;
                    my_putchar(var);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    if (str == NULL) {
                        char_count += my_strlen("(null)");
                        my_putstr("(null)");
                    }
                    else {
                        char_count += my_strlen(str);
                        my_putstr(str); 
                    }
                
                    break;
                }
                case 'u':
                case 'd': {
                    int var = va_arg(args, int);
                    char* str = my_itoa(var);
                    char_count += my_strlen(str);
                    my_putstr(str);
                    free(str);
                    break;
                }
                case 'o': {
                    int var = va_arg(args, int);
                    char* str = dec_to_oct(var);
                    char_count += my_strlen(str);
                    my_putstr(str);
                    break;
                }
                case 'p': {
                    void* var = va_arg(args, void*);
                    char* str = ptr_to_str((long)var);
                    char_count += my_strlen(str);
                    my_putstr(str);  
                    free(str); 
                    break;                 
                }
                case 'x': {
                    unsigned int var = va_arg(args, unsigned int);
                    char* str = hex_to_str((long)var, 'A');
                    char_count += my_strlen(str);
                    my_putstr(str);
                    free(str);
                    break;
                }
                case '%': {
                    char percent = '%';
                    char_count += 1;
                    my_putchar(percent);
                    break;
                }
                default: {
                    // fill me in
                }
            }
        }
        else {
            my_putchar(format[i]);
            char_count += 1;
        }
   }
   va_end(args);
   return char_count;
}


int my_strlen(char* str) {
   int i = 0;
   while(str[i] != '\0') {
       ++i;
   }
   return i;
}

int my_putstr(char* str) {
    return write(1, str, my_strlen(str));
}

int my_putchar(char c) {
    return write(1, &c, sizeof(c));
}


char* my_itoa(int num) {
    int len = 1; //to make sure enough memory is allocated if num is one digit
    int temp = num;
    bool neg = false;
    if (temp < 0) {
        len++;
        neg = true;
    }
    while (temp /= 10) { //dividing by 10 to count num of digits to allocate mem
        len++;
    }
    char* str = (char*)malloc(sizeof(char) * len);
    str[len] = '\0';
    int element_0 = 0;
    if (neg) {
        num = -num; //converts negative number to positive
        str[0] = '-';
        element_0++;
    }
    for(int i = len - 1; i >= element_0; i--) {
        str[i] = num % 10 + '0';
        num /= 10;
        
    }
    return str;

}

char* ptr_to_str(long addr) {
    int base = 16;
    int digits = 0;
    long tmp = addr;
    while (tmp != 0) {
        digits++;
        tmp /= base;
    }
    char* str = (char*) malloc(digits + 3); // prefix "0x" + digits + null terminator
    str[0] = '0';
    str[1] = 'x';
    for (int i = digits - 1; i >= 0; i--) {
        int digit = (addr >> (i * 4)) & 0xf; // extract a nibble
        str[digits - i + 1] = "0123456789abcdef"[digit]; // convert nibble to a hex digit
    }
    str[digits + 2] = '\0'; // null terminator
    
    return str;
    
}

char* hex_to_str(unsigned int num, char up_or_low) {
    int base = 16;
    int digits = 1;
    unsigned int tmp = num;
    while (tmp != 0) {
        digits++;
        tmp /= base;
    }
    char* str = (char*) malloc(digits + 1); // Add +1 to include space for null terminator
    int index = digits - 1; // Index to track the current digit position
    while (num != 0) {
        int digit = num % base;
        if (digit < 10) {
            str[index - 1] = digit + '0';
        } else {
            str[index - 1] = digit - 10 + up_or_low;
        }
        num /= base;
        index--;
    }
    str[digits - 1] = '\0'; // Null terminator
    return str;
}

char* dec_to_oct(int dec_num) {
    int length = 0;
    int temp = dec_num;
    if (temp == 0) {
        length = 1; // Special case for dec_num = 0
    }
    while (temp != 0) {
        length++;
        temp /= 10;
    }
    char* str = (char*) malloc(length + 1);
    int index = length - 1;
    while (dec_num != 0) {
        str[index] = (dec_num % 8) + '0'; // Convert the remainder to character
        dec_num /= 8;
        index--;
    }
    str[length] = '\0';
    return str;
}