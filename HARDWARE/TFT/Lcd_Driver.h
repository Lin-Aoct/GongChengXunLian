#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H	 


#include "sys.h"

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   			//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111


#define LCD_SCL        	GPIO_Pin_10	//PB10--->>TFT --SCL/SCK
#define LCD_SDA        	GPIO_Pin_3	//PB12 MOSI--->>TFT --SDA/DIN
#define LCD_RST     		GPIO_Pin_10	//PB14--->>TFT --RST
#define LCD_RS         	GPIO_Pin_11	//PB13--->>TFT --RS/DC
#define LCD_CS        	GPIO_Pin_12  //MCU_PB11--->>TFT --CS/CE

#define LCD_LED        	GPIO_Pin_9  //MCU_PB9--->>TFT --BL

//液晶控制口置1操作语句宏定义
#define	LCD_SCL_SET  	GPIOB->BSRRL=LCD_SCL    
#define	LCD_SDA_SET  	GPIOC->BSRRL=LCD_SDA
#define	LCD_RST_SET  	GPIOE->BSRRL=LCD_RST
#define	LCD_RS_SET  	GPIOB->BSRRL=LCD_RS 
#define	LCD_CS_SET  	GPIOB->BSRRL=LCD_CS  
#define	LCD_LED_SET  	GPIOB->BSRRL=LCD_LED   

//液晶控制口置0操作语句宏定义
#define	LCD_SCL_CLR  	GPIOB->BSRRH=LCD_SCL  
#define	LCD_SDA_CLR  	GPIOC->BSRRH=LCD_SDA
#define	LCD_RST_CLR  	GPIOE->BSRRH=LCD_RST
#define	LCD_RS_CLR  	GPIOB->BSRRH=LCD_RS
#define	LCD_CS_CLR  	GPIOB->BSRRH=LCD_CS 
#define	LCD_LED_CLR  	GPIOB->BSRRH=LCD_LED 

//#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
//#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

//#define LCD_WR_DATA(data){\
//	LCD_RS_SET;\
//	LCD_CS_CLR;\
//	LCD_DATAOUT(data);\
//	LCD_WR_CLR;\
//	LCD_WR_SET;\
//	LCD_CS_SET;\
//} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

#endif
