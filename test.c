//***************************************************//
//函式庫宣告設定
//***************************************************//
#include    <p33EP256MU806.h>   // 晶片選擇含入
#define     FCY     60000000

_FOSCSEL(FNOSC_PRIPLL); // 震盪器設定主振盪器（XT，HS和EC）W / PLL
_FOSC(FCKSM_CSECME & OSCIOFNC_OFF & POSCMD_XT);
// 時鐘切換和時鐘監視器(只有時鐘切換致能)
// 設定OSC2 時脈輸出
// 主振盪器選擇：中速模式（XT)範圍3~10M Hz
_FWDT(FWDTEN_OFF); // 監視計數器又稱為看門狗(計數監視器關閉)
//***************************************************//
//副程式宣告設定
//***************************************************//
void Init_Crystal(void); // 石英震盪器副程式
void Init_IO(void); // IO副程式
void Delay(unsigned int delay_count); // Delay副程式
//***************************************************//
//主程式
//***************************************************//

void led_display(int);
void led_light(int);
void led_delight(int);

void test1(void){
        Delay(200);
        LATBbits.LATB6 = 0;
        Delay(200);
        LATBbits.LATB6 = 1;
        Delay(200);
        LATBbits.LATB13 = 0;
        Delay(200);
        LATBbits.LATB13 = 1;
        Delay(200);

        LATDbits.LATD9 = 0;
        LATDbits.LATD8 = 0;
        Delay(200);
        LATBbits.LATB6 = 0;
        LATBbits.LATB13 = 0;
        Delay(200);
        LATBbits.LATB7 = 0;
        LATBbits.LATB12 = 0;
        Delay(200);
        LATBbits.LATB8 = 0;
        LATBbits.LATB11 = 0;
        Delay(200);
        LATBbits.LATB9 = 0;
        LATBbits.LATB10 = 0;
        Delay(200);

        LATBbits.LATB9 = 1;
        LATBbits.LATB10 = 1;
        Delay(200);
        LATBbits.LATB8 = 1;
        LATBbits.LATB11 = 1;
        Delay(200);
        LATBbits.LATB7 = 1;
        LATBbits.LATB12 = 1;
        Delay(200);
        LATBbits.LATB6 = 1;
        LATBbits.LATB13 = 1;
        Delay(200);
        LATDbits.LATD9 = 1;
        LATDbits.LATD8 = 1;
        Delay(200);
}

void test2(void){
        int number = 18;
    while (1) // 迴圈
    {
        if(PORTGbits.RG9 == 0){
            number += 1;
            led_display(number);
        }
        
        if(PORTGbits.RG6 == 0){
            number -= 1;
            led_display(number);
        }
        
        if(PORTGbits.RG8 == 0){
            number += 10;
            led_display(number);
        }
        
        if(PORTGbits.RG7 == 0){
            number -= 10;
            led_display(number);
        }
    }
}

//int main(void)
//{
//    Init_Crystal(); // 石英震盪器初使化設定
//    Init_IO(); // IO初使化設定

//    while (1) // 迴圈
//    {
        //  英文名字
        
        
//    }
//}
//***************************************************//
//石英震盪器副程式
//***************************************************//

void led_light(int number){
    switch (number){
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

void led_delight(int number){
    switch (number){
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

void led_display(int number){
    int one = number % 10;
    int two = (number - one) % 100 / 10;
    int three =  (number - two * 10 - one) % 1000 / 100;
    
    led_light(three);
    Delay(200);
    led_delight(three);
    Delay(200);
    
    led_light(two);
    Delay(200);
    led_delight(two);
    Delay(200);
    
    led_light(one);
    Delay(200);
    led_delight(one);
    Delay(200);
}

void Init_Crystal(void)
{
    PLLFBD = 58; // M=PLLFBD+2
    CLKDIVbits.PLLPOST = 0; // N2=2
    CLKDIVbits.PLLPRE = 0; // N1=2
    // Fcy=0.5*((Fin*M)/(N1*N2))//約60MIPS
}
//***************************************************//
//IO副程式
//***************************************************//

void Init_test1(void){
    TRISDbits.TRISD9 = 0;
    LATDbits.LATD9 = 1;
    TRISDbits.TRISD8 = 0;
    LATDbits.LATD8 = 1;
    
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 1;
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    TRISBbits.TRISB11 = 0;
    LATBbits.LATB11 = 1;
    TRISBbits.TRISB10 = 0;
    LATBbits.LATB10 = 1;
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 1;
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 1;
    TRISBbits.TRISB7 = 0;
    LATBbits.LATB7 = 1;
    TRISBbits.TRISB6 = 0;
    LATBbits.LATB6 = 1;
    
    
}

void Init_IO(void)
{
    Init_test1();
    
    TRISGbits.TRISG9 = 1;
    ANSELGbits.ANSG9 = 0; 
    
    TRISGbits.TRISG6 = 1;
    ANSELGbits.ANSG6 = 0; 
    
    TRISGbits.TRISG8 = 1;
    ANSELGbits.ANSG8 = 0; 
    
    TRISGbits.TRISG7 = 1;
    ANSELGbits.ANSG7 = 0;
}
//***************************************************//
//Delay副程式
//***************************************************//

void Delay(unsigned int delay_count)
{
    unsigned int delay_a, delay_b;

    for (delay_a = 0; delay_a <= delay_count; delay_a++)
    {
        for (delay_b = 0; delay_b <= 5000; delay_b++);
    }
}
