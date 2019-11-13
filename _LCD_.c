#include <stdio.h>
#include <p33EP256MU806.h>
#include "_TLCD_.h"
#include "_LCD_.h"

void init_lcd(){
    OpenLCD();
}

void display_string_lcd(unsigned char x, unsigned char y, const char *str){
    setcurLCD(0, y);
    putrsLCD("        ");
    
    setcurLCD(x, y);
    putrsLCD(str);
}

void display_int_lcd(unsigned char x, unsigned char y, const unsigned int num){
    char *str = "";
    sprintf(str, "%d", num);
    
    display_string_lcd(x, y, str);
}
