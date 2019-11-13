//***************************************************//
//函式庫宣告設定
//***************************************************//
#include    <p33EP256MU806.h>   //晶片選擇含入
#define     FCY     60000000
#include    "_TLCD_.h"

_FOSCSEL(FNOSC_PRIPLL); //震盪器設定主振盪器（XT，HS和EC）W / PLL
_FOSC(FCKSM_CSECME & OSCIOFNC_OFF & POSCMD_XT);
//時鐘切換和時鐘監視器(只有時鐘切換致能)
//設定OSC2 時脈輸出
//主振盪器選擇：中速模式（XT)範圍3~10M Hz
_FWDT(FWDTEN_OFF); //監視計數器又稱為看門狗(計數監視器關閉)
//***************************************************//
//副程式宣告設定
//***************************************************//
void Init_Crystal(void); // 石英震盪器副程式
void Init_IO(void); // IO副程式
void Delay(unsigned int delay_count); // Delay副程式
void LCD_Mode(int LCD_mode); // LCD副程式
//***************************************************//
//主程式
//***************************************************//
int number = 54;
int index = 0;

int main(void) {
    Init_Crystal(); // 石英震盪器初使化設定
    Init_IO(); // IO初使化設定
    OpenLCD(); // 開啟LCD
    LATDbits.LATD8 = 1; // RD8的LED滅(左)
    LATDbits.LATD9 = 1; // RD9的LED滅(右)

    LATBbits.LATB6 = 1; // RB6的LED滅
    LATBbits.LATB7 = 1; // RB7的LED滅
    LATBbits.LATB8 = 1; // RB8的LED滅
    LATBbits.LATB9 = 1; // RB9的LED滅
    LATBbits.LATB10 = 1; // RB10的LED滅
    LATBbits.LATB11 = 1; // RB11的LED滅
    LATBbits.LATB12 = 1; // RB12的LED滅
    LATBbits.LATB13 = 1; // RB13的LED滅  
    while (1) // 迴圈
    {
        if (PORTGbits.RG9 == 0) // 當上方按鈕按下
        {
            if (number < 99)
                number++;
            Delay(100); // 延遲500ms
            while (PORTGbits.RG9 == 0); //等到上方按鈕被按下
        }
        if (PORTGbits.RG6 == 0) // 當下方按鈕按下
        {
            if (number > 0)
                number--;
            Delay(100); // 延遲500ms
            while (PORTGbits.RG6 == 0); //等到下方按鈕被按下
        }

        if (PORTGbits.RG8 == 0) {
            if (index > 0)
                index--;

            Delay(100);
            while (PORTGbits.RG8 == 0);
        }

        if (PORTGbits.RG7 == 0) {
            if (index < 6)
                index++;

            Delay(100);
            while (PORTGbits.RG7 == 0);
        }

        LCD_Mode(2);
        LCD_Mode(1); // LCD模式選擇
    }
}
//***************************************************//
//石英震盪器副程式
//***************************************************//

void Init_Crystal(void) {
    PLLFBD = 58; // M=PLLFBD+2
    CLKDIVbits.PLLPOST = 0; // N2=2
    CLKDIVbits.PLLPRE = 0; // N1=2
    // Fcy=0.5*((Fin*M)/(N1*N2))//約60MIPS
}
//***************************************************//
//IO副程式
//***************************************************//

void Init_IO(void) {
    ANSELGbits.ANSG9 = 0; // 類比腳轉數位腳
    ANSELGbits.ANSG8 = 0; // 類比腳轉數位腳
    ANSELGbits.ANSG7 = 0; // 類比腳轉數位腳
    ANSELGbits.ANSG6 = 0; // 類比腳轉數位腳

    //Button    		
    TRISDbits.TRISD10 = 1; //RD10設定為輸入模式，按鍵(右)
    TRISGbits.TRISG9 = 1; // RG9設定為輸入模式，按鍵(上)	
    TRISGbits.TRISG6 = 1; // RG6設定為輸入模式，按鍵(下)    
    TRISGbits.TRISG8 = 1; // RG8設定為輸入模式，按鍵(左)	   
    TRISGbits.TRISG7 = 1; // RG7設定為輸入模式，按鍵(右)
    //Led
    TRISDbits.TRISD8 = 0; // RD8設定為輸出模式，LED(左)
    TRISDbits.TRISD9 = 0; // RD9設定為輸出模式，LED(右)

    //Led
    TRISBbits.TRISB6 = 0; // RB6設定為輸出模式，LED1
    TRISBbits.TRISB7 = 0; // RB7設定為輸出模式，LED2    
    TRISBbits.TRISB8 = 0; // RB8設定為輸出模式，LED3
    TRISBbits.TRISB9 = 0; // RB9設定為輸出模式，LED4
    TRISBbits.TRISB10 = 0; // RB10設定為輸出模式，LED5
    TRISBbits.TRISB11 = 0; // RB11設定為輸出模式，LED6
    TRISBbits.TRISB12 = 0; // RB12設定為輸出模式，LED7
    TRISBbits.TRISB13 = 0; // RB13設定為輸出模式，LED8

}
//***************************************************//
//Delay副程式
//***************************************************//

void Delay(unsigned int delay_count) {
    unsigned int delay_a, delay_b;

    for (delay_a = 0; delay_a <= delay_count; delay_a++) {
        for (delay_b = 0; delay_b <= 5000; delay_b++);
    }
}
//***************************************************//
//LCD副程式
//***************************************************//

void LCD_Mode(int LCD_mode) {
    switch (LCD_mode) {
        case 1:
            setcurLCD(0, 0);
            putrsLCD("Shengtai");
            //setcurLCD(0, 1);
            setcurLCD(index, 1);
            //put_3Num(number);
            putrsLCD("18");
            break;
        case 2:
            setcurLCD(0, 0);
            putrsLCD("        ");
            setcurLCD(0, 1);
            putrsLCD("        ");
            break;
        default:
            setcurLCD(0, 0);
            putrsLCD("ERROR   ");
            setcurLCD(0, 1);
            putrsLCD("        ");
            break;
    }
}