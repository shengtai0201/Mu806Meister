#include <p33EP256MU806.h>
#include "_COMMON_.h"
#include "_LED_.h"

void init_led() {
    TRISDbits.TRISD9 = 0;
    TRISDbits.TRISD8 = 0;

    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB6 = 0;
}

void led() {
    LATDbits.LATD9 = 1;
    LATDbits.LATD8 = 1;

    LATBbits.LATB13 = 1;
    LATBbits.LATB12 = 1;
    LATBbits.LATB11 = 1;
    LATBbits.LATB10 = 1;
    LATBbits.LATB9 = 1;
    LATBbits.LATB8 = 1;
    LATBbits.LATB7 = 1;
    LATBbits.LATB6 = 1;
}

void bright(unsigned short number) {
    switch (number) {
        case 0:
            LATDbits.LATD9 = 0;
            break;
        case 1:
            LATBbits.LATB6 = 0;
            break;
        case 2:
            LATBbits.LATB7 = 0;
            break;
        case 3:
            LATBbits.LATB8 = 0;
            break;
        case 4:
            LATBbits.LATB9 = 0;
            break;
        case 5:
            LATBbits.LATB10 = 0;
            break;
        case 6:
            LATBbits.LATB11 = 0;
            break;
        case 7:
            LATBbits.LATB12 = 0;
            break;
        case 8:
            LATBbits.LATB13 = 0;
            break;
        case 9:
            LATDbits.LATD8 = 0;
            break;
    }
}

void dark(unsigned short number) {
    switch (number) {
        case 0:
            LATDbits.LATD9 = 1;
            break;
        case 1:
            LATBbits.LATB6 = 1;
            break;
        case 2:
            LATBbits.LATB7 = 1;
            break;
        case 3:
            LATBbits.LATB8 = 1;
            break;
        case 4:
            LATBbits.LATB9 = 1;
            break;
        case 5:
            LATBbits.LATB10 = 1;
            break;
        case 6:
            LATBbits.LATB11 = 1;
            break;
        case 7:
            LATBbits.LATB12 = 1;
            break;
        case 8:
            LATBbits.LATB13 = 1;
            break;
        case 9:
            LATDbits.LATD8 = 1;
            break;
    }
}

void display_led(unsigned int number) {
    int one = number % 10;
    int two = (number - one) % 100 / 10;
    int three = (number - two * 10 - one) % 1000 / 100;

    bright(three);
    Delay(200);
    dark(three);
    Delay(200);

    bright(two);
    Delay(200);
    dark(two);
    Delay(200);

    bright(one);
    Delay(200);
    dark(one);
    Delay(200);
}