//***************************************************//
//函式庫宣告設定
//***************************************************//
#include 	"_TLCD_.h"
#include 	<p33EP256MU806.h>	
//***************************************************//
//LCD腳位 
//***************************************************//
#define LCD_RS			LATDbits.LATD1		//定義RG2為輸出控制腳位
#define LCD_RW			LATDbits.LATD2		//定義RG3為輸出控制腳位
#define LCD_E			LATDbits.LATD3		//定義RF6為輸出控制腳位


#define	DIR_LCD_RS		TRISDbits.TRISD1	//定義RG2為輸入或輸出的控制腳位
#define	DIR_LCD_RW		TRISDbits.TRISD2	//定義RG3為輸入或輸出的控制腳位
#define	DIR_LCD_E		TRISDbits.TRISD3	//定義RF6為輸入或輸出的控制腳位

union sample {
    unsigned int data;

    struct {
        unsigned DB0 : 1;
        unsigned DB1 : 1;
        unsigned DB2 : 1;
        unsigned DB3 : 1;
        unsigned unused : 12;
    };

} LCD_bus;

#define DB0 LCD_bus.DB0
#define DB1 LCD_bus.DB1
#define DB2 LCD_bus.DB2
#define DB3 LCD_bus.DB3
#define LCD_DATA		LCD_bus.data			
#define LCD_DATA_4		LATDbits.LATD4			//定義RD8為輸出腳位
#define LCD_DATA_5		LATDbits.LATD5			//定義RD9為輸出腳位
#define LCD_DATA_6		LATDbits.LATD6			//定義RD10為輸出腳位
#define LCD_DATA_7		LATDbits.LATD7			//定義RD11為輸出腳位
#define	DIR_LCD_DATA_4		TRISDbits.TRISD4	//定義RD8為輸入或輸出的控制腳位
#define	DIR_LCD_DATA_5		TRISDbits.TRISD5	//定義RD9為輸入或輸出的控制腳位
#define	DIR_LCD_DATA_6		TRISDbits.TRISD6	//定義RD10為輸入或輸出的控制腳位
#define	DIR_LCD_DATA_7		TRISDbits.TRISD7	//定義RD11為輸入或輸出的控制腳位
//******************************************************************//
//由LCD Module 的資料定義撰寫
//******************************************************************//
#define DISP_2Line_8Bit		0x0038
#define DISP_2Line_4Bit		0x0028
#define DISP_ON				0x00C		
#define DISP_ON_C			0x00E		
#define DISP_ON_B			0x00F		
#define DISP_OFF			0x008	
#define CLR_DISP			0x001	
#define ENTRY_INC			0x006
#define ENTRY_INC_S			0x007
#define ENTRY_DEC			0x004
#define ENTRY_DEC_S			0x005	
#define DD_RAM_ADDR			0x080	
#define DD_RAM_UL			0x080	

unsigned char Temp_CMD;
unsigned char Str_Temp;
unsigned char Out_Mask;
int Temp_LCD_DATA;
//******************************************************************//
//由LCD Module的資料裡面的初始流程圖撰寫
//******************************************************************//

void OpenLCD(void) {
    Temp_LCD_DATA = LCD_DATA;

    LCD_E = 0;
    LCD_DATA &= 0xfff0;
    DIR_LCD_DATA_4 = 0;
    DIR_LCD_DATA_5 = 0;
    DIR_LCD_DATA_6 = 0;
    DIR_LCD_DATA_7 = 0;
    DIR_LCD_E = 0;
    DIR_LCD_RS = 0;
    DIR_LCD_RW = 0;

    LCD_DATA &= 0xfff0;
    LCD_DATA |= 0x0003;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();
    LCD_L_Delay();

    LCD_DATA &= 0xfff0;
    LCD_DATA |= 0x0003;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();
    LCD_L_Delay();

    LCD_DATA &= 0xfff0;
    LCD_DATA |= 0x0003;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();
    LCD_L_Delay();

    LCD_DATA &= 0xfff0;
    LCD_DATA |= 0x0002;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();
    LCD_L_Delay();

    WriteCmdLCD(DISP_2Line_4Bit);
    LCD_S_Delay();

    WriteCmdLCD(DISP_ON);
    LCD_S_Delay();

    WriteCmdLCD(ENTRY_INC);
    LCD_S_Delay();

    WriteCmdLCD(CLR_DISP);
    LCD_L_Delay();

    LCD_DATA = Temp_LCD_DATA;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
}
//******************************************************************//
//由LCD Module的資料裡面的時序圖撰寫
//******************************************************************//

void WriteCmdLCD(unsigned char LCD_CMD) {
    Temp_LCD_DATA = LCD_DATA;

    Temp_CMD = (LCD_CMD & 0xF0) >> 4;
    LCD_DATA = (LCD_DATA & 0xfff0) | Temp_CMD;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();

    Temp_CMD = LCD_CMD & 0x0F;
    LCD_DATA = (LCD_DATA & 0xfff0) | Temp_CMD;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_CMD_W_Timing();
    LCD_DATA = Temp_LCD_DATA;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_S_Delay();
}
//******************************************************************//
//由LCD Module的資料裡面的時序圖撰寫
//******************************************************************//

void WriteDataLCD(unsigned char LCD_CMD) {
    Temp_LCD_DATA = LCD_DATA;

    Temp_CMD = (LCD_CMD & 0xF0) >> 4;
    LCD_DATA = (LCD_DATA & 0xfff0) | Temp_CMD;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_DAT_W_Timing();

    Temp_CMD = LCD_CMD & 0x0F;
    LCD_DATA = (LCD_DATA & 0xfff0) | Temp_CMD;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_DAT_W_Timing();
    LCD_DATA = Temp_LCD_DATA;
    LCD_DATA_4 = DB0;
    LCD_DATA_5 = DB1;
    LCD_DATA_6 = DB2;
    LCD_DATA_7 = DB3;
    LCD_S_Delay();
}
//******************************************************************//
//由LCD Module的資料裡面的時序圖撰寫
//******************************************************************//

void putcLCD(unsigned char LCD_Char) {
    WriteDataLCD(LCD_Char);
}
//******************************************************************//
//由LCD Module的資料裡面的時序圖撰寫
//******************************************************************//

void LCD_CMD_W_Timing(void) {
    LCD_RS = 0;
    Nop();
    LCD_RW = 0;
    Nop();
    LCD_E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    LCD_E = 0;
}
//******************************************************************//
//由LCD Module的資料裡面的時序圖撰寫
//******************************************************************//

void LCD_DAT_W_Timing(void) {
    LCD_RS = 1;
    Nop();
    LCD_RW = 0;
    Nop();
    LCD_E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    LCD_E = 0;
}
//******************************************************************//
//  設定LCD所顯示的座標值
//  CurY = Line (0 or 1)
//  CurX = Position ( 0 to 15)
//******************************************************************//

void setcurLCD(unsigned char CurX, unsigned char CurY) {
    WriteCmdLCD(0x80 + CurY * 0x40 + CurX);
    LCD_S_Delay();
}
//******************************************************************//
//將字串儲存在ROM
//******************************************************************//

void putrsLCD(const char *Str) {
    while (1) {
        Str_Temp = *Str;
        if (Str_Temp != 0x00) {
            WriteDataLCD(Str_Temp);
            Str++;
        } else
            return;
    }
}
//******************************************************************//
//將字串儲存在RAM
//******************************************************************//

void putsLCD(char *Str) {
    while (1) {
        Str_Temp = *Str;
        if (Str_Temp != 0x00) {
            WriteDataLCD(Str_Temp);
            Str++;
        } else
            return;
    }
}
//******************************************************************//
//將字串以16進制顯示
//******************************************************************//

void puthexLCD(unsigned char HEX_Val) {
    unsigned char Temp_HEX;

    Temp_HEX = (HEX_Val >> 4) & 0x0f;
    if (Temp_HEX > 9)Temp_HEX += 0x37;
    else Temp_HEX += 0x30;
    WriteDataLCD(Temp_HEX);
    Temp_HEX = HEX_Val & 0x0f;
    if (Temp_HEX > 9)Temp_HEX += 0x37;
    else Temp_HEX += 0x30;
    WriteDataLCD(Temp_HEX);
}

//******************************************************************//
//Delay約10ms
//******************************************************************//

void LCD_L_Delay(void) {
    int L_Loop;
    for (L_Loop = 0; L_Loop < 100; L_Loop++)
        LCD_S_Delay();
}
//******************************************************************//
//Delay約100us
//******************************************************************//

void LCD_S_Delay(void) {
    int S_Loop, Null_Var;
    for (S_Loop = 0; S_Loop < 200; S_Loop++)
        Null_Var += 1;
}

void put_2Num(unsigned int The_Number) {
    unsigned int n0, n1;
    n0 = (The_Number / 10) % 10; //十位數
    n1 = (The_Number % 100) % 10; //各位數
    putcLCD('0' + n0); //轉換為ASCII編碼
    putcLCD('0' + n1); //轉換為ASCII編碼				
}

void put_3Num(unsigned int The_Number) {
    unsigned int n0, n1, n2;
    n0 = The_Number / 100; //百位數
    n1 = (The_Number / 10) % 10; //十位數
    n2 = (The_Number % 100) % 10; //各位數
    putcLCD('0' + n0); //轉換為ASCII編碼
    putcLCD('0' + n1); //轉換為ASCII編碼
    putcLCD('0' + n2); //轉換為ASCII編碼				
}

void put_4Num(unsigned long The_Number) {
    unsigned char n0, n1, n2, n3;
    n0 = The_Number / 1000; //仟位數	
    n1 = (The_Number / 100) % 10; //百位數
    n2 = (The_Number / 10) % 10; //十位數
    n3 = (The_Number % 100) % 10; //個位數
    putcLCD('0' + n0);
    putcLCD('0' + n1);
    putcLCD('0' + n2);
    putcLCD('0' + n3); //轉換為ASCII編碼	
}

void put_5Num(unsigned long n) {
    unsigned long n1, n2, n3, n4, n0;
    n0 = (n / 10000); //萬位數 
    n1 = (n / 1000) % 10; //千位數  
    n2 = (n / 100) % 10; //百位數  
    n3 = (n / 10) % 10; //十位數  	
    n4 = (n % 100) % 10; //個位數  	
    putcLCD(48 + n0);
    putcLCD(48 + n1);
    putcLCD(48 + n2);
    putcLCD(48 + n3);
    putcLCD(48 + n4);
}