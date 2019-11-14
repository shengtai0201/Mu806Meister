#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void display_int_lcd(unsigned char x, unsigned char y, const unsigned int num) {
    int length = floor(log10(abs(num))) + 1;
    char *str = malloc(length * sizeof (char));
    sprintf(str, "%d", num);

    display_string_lcd(x, y, str);
}
