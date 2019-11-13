#include <p33EP256MU806.h>
#include "_COMMON_.h"
#include "_LED_.h"
#include "_BUTTON_.h"
#include "_LCD_.h"

#define FCY 60000000

_FOSCSEL(FNOSC_PRIPLL); // 震盪器設定主振盪器（XT，HS和EC）W / PLL
_FOSC(FCKSM_CSECME & OSCIOFNC_OFF & POSCMD_XT);
// 時鐘切換和時鐘監視器(只有時鐘切換致能)
// 設定OSC2 時脈輸出
// 主振盪器選擇：中速模式（XT)範圍3~10M Hz
_FWDT(FWDTEN_OFF); // 監視計數器又稱為看門狗(計數監視器關閉)

void Init_Crystal(); // 石英震盪器副程式

void test1() {
    Delay(200);
    bright(1);
    Delay(200);
    dark(1);
    Delay(200);
    bright(8);
    Delay(200);
    dark(8);
    Delay(200);

    bright(0);
    bright(9);
    Delay(200);
    bright(1);
    bright(8);
    Delay(200);
    bright(2);
    bright(7);
    Delay(200);
    bright(3);
    bright(6);
    Delay(200);
    bright(4);
    bright(5);
    Delay(200);

    dark(4);
    dark(5);
    Delay(200);
    dark(3);
    dark(6);
    Delay(200);
    dark(2);
    dark(7);
    Delay(200);
    dark(1);
    dark(8);
    Delay(200);
    dark(0);
    dark(9);
    Delay(200);
}

unsigned int seat_number = 18;

void test2() {
    if (PORTGbits.RG9 == 0) {
        seat_number += 1;
        display_led(seat_number);

        Delay(100);
        while (PORTGbits.RG9 == 0);
    }

    if (PORTGbits.RG6 == 0) {
        seat_number -= 1;
        display_led(seat_number);

        Delay(100);
        while (PORTGbits.RG6 == 0);
    }

    if (PORTGbits.RG8 == 0) {
        seat_number += 10;
        display_led(seat_number);

        Delay(100);
        while (PORTGbits.RG8 == 0);
    }

    if (PORTGbits.RG7 == 0) {
        seat_number -= 10;
        display_led(seat_number);

        Delay(100);
        while (PORTGbits.RG7 == 0);
    }
}

unsigned short lcd_index = 0;

void test3() {
    if (PORTGbits.RG8 == 0) {
        if (lcd_index > 0)
            lcd_index--;

        Delay(100);
        while (PORTGbits.RG8 == 0);
    }

    if (PORTGbits.RG7 == 0) {
        if (lcd_index < 6)
            lcd_index++;

        Delay(100);
        while (PORTGbits.RG7 == 0);
    }

    display_string_lcd(0, 0, "Shengtai");
    display_string_lcd(lcd_index, 1, "18");
}

unsigned int student_id = 02;

void test4_1() {
    int i;
    for (i = 0; i < 10; i++) {
        Delay(200);
        bright(i);
    }

    display_int_lcd(3, 1, student_id);
}

void test4_2() {
    if (PORTGbits.RG8 == 0) {
        int i;
        for (i = 0; i < 10; i++) {
            Delay(200);
            dark(i);
        }

        Delay(100);
        while (PORTGbits.RG8 == 0);
    }
}

void test4_3() {
    if (PORTGbits.RG7 == 0) {
        unsigned int tmp = student_id;
        if ((tmp += 3) < 100)
            student_id = tmp;

        if (lcd_index < 6)
            lcd_index++;

        display_int_lcd(lcd_index, 1, student_id);

        Delay(100);
        while (PORTGbits.RG7 == 0);
    }
}

void test4_4() {
    if (PORTGbits.RG6 == 0) {
        unsigned int tmp = student_id;
        if ((tmp -= 4) > 0)
            student_id = tmp;

        if (lcd_index > 0)
            lcd_index--;

        display_int_lcd(lcd_index, 1, student_id);

        Delay(100);
        while (PORTGbits.RG6 == 0);
    }
}

void test4_5() {
    if (PORTGbits.RG9 == 0 && PORTDbits.RD10 == 0) {
        student_id = 3;

        display_int_lcd(lcd_index, 1, student_id);

        Delay(100);
        while (PORTGbits.RG9 == 0 && PORTDbits.RD10 == 0);
    }
}

int main() {
    Init_Crystal();

    // Init_IO
    init_led();
    init_button();
    init_lcd();

    led();
    test4_1();

    while (1) {
        //test1();
        //test2();
        //test3();

        test4_2();
        test4_3();
        test4_4();
        test4_5();
    }

    return 0;
}

void Init_Crystal() {
    PLLFBD = 58; // M=PLLFBD+2
    CLKDIVbits.PLLPOST = 0; // N2=2
    CLKDIVbits.PLLPRE = 0; // N1=2
    // Fcy=0.5*((Fin*M)/(N1*N2))//約60MIPS
}