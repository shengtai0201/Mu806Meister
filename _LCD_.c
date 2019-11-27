#include <stdio.h>
#include <stdlib.h>
#include <p33EP256MU806.h>
#include "_TLCD_.h"
#include "_LCD_.h"

void init_lcd() {
    OpenLCD();
}

void display_string_lcd(unsigned char x, unsigned char y, const char *str) {
    setcurLCD(0, y);
    putrsLCD("        ");

    setcurLCD(x, y);
    putrsLCD(str);
}

unsigned int pow(unsigned int value, unsigned int n) {
    unsigned int i, result = value;
    for (i = 1; i < n; i++) {
        result *= value;
    }

    return result;
}

void display_int_lcd(unsigned char x, unsigned char y, unsigned int value, unsigned int numberOfDigits) {
    setcurLCD(0, y);
    putrsLCD("        ");

    setcurLCD(x, y);
    int i;
    for (i = 0; i < numberOfDigits; i++) {
        unsigned int number = value / pow(10, (numberOfDigits - 1 - i)) % 10;
        putcLCD('0' + number);
    }
}