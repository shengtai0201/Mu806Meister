#include <p33EP256MU806.h>
#include "_BUTTON_.h"

void init_button() {
    // 上
    TRISGbits.TRISG9 = 1;
    ANSELGbits.ANSG9 = 0;

    // 下
    TRISGbits.TRISG6 = 1;
    ANSELGbits.ANSG6 = 0;

    // 左
    TRISGbits.TRISG8 = 1;
    ANSELGbits.ANSG8 = 0;

    // 右
    TRISGbits.TRISG7 = 1;
    ANSELGbits.ANSG7 = 0;
    
    // 最下方，左
    TRISEbits.TRISE4 = 1;
    ANSELEbits.ANSE4 = 0;
    
    // 最下方，右
    TRISDbits.TRISD10 = 1;
}
