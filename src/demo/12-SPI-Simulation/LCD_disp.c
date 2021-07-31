
#include "LCD_disp.h"

//画笔颜色以及背景色	   
uint16_t POINT_COLOR;
uint16_t BACK_COLOR;

//8*16 ASCII字库集点阵
const unsigned char ASCII_0816[95][16]={	  
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xCC,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
  {0x00,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x08,0x00,0x30,0x00,0x60,0x00,0x00,0x00},/*""",2*/
  {0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x03,0xFC,0x1E,0x20,0x02,0x20,0x00,0x00},/*"#",3*/
  {0x00,0x00,0x0E,0x18,0x11,0x04,0x3F,0xFF,0x10,0x84,0x0C,0x78,0x00,0x00,0x00,0x00},/*"$",4*/
  {0x0F,0x00,0x10,0x84,0x0F,0x38,0x00,0xC0,0x07,0x78,0x18,0x84,0x00,0x78,0x00,0x00},/*"%",5*/
  {0x00,0x78,0x0F,0x84,0x10,0xC4,0x11,0x24,0x0E,0x98,0x00,0xE4,0x00,0x84,0x00,0x08},/*"&",6*/
  {0x08,0x00,0x68,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xE0,0x18,0x18,0x20,0x04,0x40,0x02,0x00,0x00},/*"(",8*/
  {0x00,0x00,0x40,0x02,0x20,0x04,0x18,0x18,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*")",9*/
  {0x02,0x40,0x02,0x40,0x01,0x80,0x0F,0xF0,0x01,0x80,0x02,0x40,0x02,0x40,0x00,0x00},/*"*",10*/
  {0x00,0x80,0x00,0x80,0x00,0x80,0x0F,0xF8,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00},/*"+",11*/
  {0x00,0x01,0x00,0x0D,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*",",12*/
  {0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80},/*"-",13*/
  {0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*".",14*/
  {0x00,0x00,0x00,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x18,0x00,0x20,0x00},/*"/",15*/
  {0x00,0x00,0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"0",16*/
  {0x00,0x00,0x08,0x04,0x08,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"1",17*/
  {0x00,0x00,0x0E,0x0C,0x10,0x14,0x10,0x24,0x10,0x44,0x11,0x84,0x0E,0x0C,0x00,0x00},/*"2",18*/
  {0x00,0x00,0x0C,0x18,0x10,0x04,0x11,0x04,0x11,0x04,0x12,0x88,0x0C,0x70,0x00,0x00},/*"3",19*/
  {0x00,0x00,0x00,0xE0,0x03,0x20,0x04,0x24,0x08,0x24,0x1F,0xFC,0x00,0x24,0x00,0x00},/*"4",20*/
  {0x00,0x00,0x1F,0x98,0x10,0x84,0x11,0x04,0x11,0x04,0x10,0x88,0x10,0x70,0x00,0x00},/*"5",21*/
  {0x00,0x00,0x07,0xF0,0x08,0x88,0x11,0x04,0x11,0x04,0x18,0x88,0x00,0x70,0x00,0x00},/*"6",22*/
  {0x00,0x00,0x1C,0x00,0x10,0x00,0x10,0xFC,0x13,0x00,0x1C,0x00,0x10,0x00,0x00,0x00},/*"7",23*/
  {0x00,0x00,0x0E,0x38,0x11,0x44,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00},/*"8",24*/
  {0x00,0x00,0x07,0x00,0x08,0x8C,0x10,0x44,0x10,0x44,0x08,0x88,0x07,0xF0,0x00,0x00},/*"9",25*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x03,0x0C,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/
  {0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/
  {0x00,0x00,0x00,0x80,0x01,0x40,0x02,0x20,0x04,0x10,0x08,0x08,0x10,0x04,0x00,0x00},/*"<",28*/
  {0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x00,0x00},/*"=",29*/
  {0x00,0x00,0x10,0x04,0x08,0x08,0x04,0x10,0x02,0x20,0x01,0x40,0x00,0x80,0x00,0x00},/*">",30*/
  {0x00,0x00,0x0E,0x00,0x12,0x00,0x10,0x0C,0x10,0x6C,0x10,0x80,0x0F,0x00,0x00,0x00},/*"?",31*/
  {0x03,0xE0,0x0C,0x18,0x13,0xE4,0x14,0x24,0x17,0xC4,0x08,0x28,0x07,0xD0,0x00,0x00},/*"@",32*/
  {0x00,0x04,0x00,0x3C,0x03,0xC4,0x1C,0x40,0x07,0x40,0x00,0xE4,0x00,0x1C,0x00,0x04},/*"A",33*/
  {0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x11,0x04,0x0E,0x88,0x00,0x70,0x00,0x00},/*"B",34*/
  {0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x08,0x1C,0x10,0x00,0x00},/*"C",35*/
  {0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"D",36*/
  {0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x04,0x17,0xC4,0x10,0x04,0x08,0x18,0x00,0x00},/*"E",37*/
  {0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x17,0xC0,0x10,0x00,0x08,0x00,0x00,0x00},/*"F",38*/
  {0x03,0xE0,0x0C,0x18,0x10,0x04,0x10,0x04,0x10,0x44,0x1C,0x78,0x00,0x40,0x00,0x00},/*"G",39*/
  {0x10,0x04,0x1F,0xFC,0x10,0x84,0x00,0x80,0x00,0x80,0x10,0x84,0x1F,0xFC,0x10,0x04},/*"H",40*/
  {0x00,0x00,0x10,0x04,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x04,0x00,0x00,0x00,0x00},/*"I",41*/
  {0x00,0x03,0x00,0x01,0x10,0x01,0x10,0x01,0x1F,0xFE,0x10,0x00,0x10,0x00,0x00,0x00},/*"J",42*/
  {0x10,0x04,0x1F,0xFC,0x11,0x04,0x03,0x80,0x14,0x64,0x18,0x1C,0x10,0x04,0x00,0x00},/*"K",43*/
  {0x10,0x04,0x1F,0xFC,0x10,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x0C,0x00,0x00},/*"L",44*/
  {0x10,0x04,0x1F,0xFC,0x1F,0x00,0x00,0xFC,0x1F,0x00,0x1F,0xFC,0x10,0x04,0x00,0x00},/*"M",45*/
  {0x10,0x04,0x1F,0xFC,0x0C,0x04,0x03,0x00,0x00,0xE0,0x10,0x18,0x1F,0xFC,0x10,0x00},/*"N",46*/
  {0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00},/*"O",47*/
  {0x10,0x04,0x1F,0xFC,0x10,0x84,0x10,0x80,0x10,0x80,0x10,0x80,0x0F,0x00,0x00,0x00},/*"P",48*/
  {0x07,0xF0,0x08,0x18,0x10,0x24,0x10,0x24,0x10,0x1C,0x08,0x0A,0x07,0xF2,0x00,0x00},/*"Q",49*/
  {0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x11,0xC0,0x11,0x30,0x0E,0x0C,0x00,0x04},/*"R",50*/
  {0x00,0x00,0x0E,0x1C,0x11,0x04,0x10,0x84,0x10,0x84,0x10,0x44,0x1C,0x38,0x00,0x00},/*"S",51*/
  {0x18,0x00,0x10,0x00,0x10,0x04,0x1F,0xFC,0x10,0x04,0x10,0x00,0x18,0x00,0x00,0x00},/*"T",52*/
  {0x10,0x00,0x1F,0xF8,0x10,0x04,0x00,0x04,0x00,0x04,0x10,0x04,0x1F,0xF8,0x10,0x00},/*"U",53*/
  {0x10,0x00,0x1E,0x00,0x11,0xE0,0x00,0x1C,0x00,0x70,0x13,0x80,0x1C,0x00,0x10,0x00},/*"V",54*/
  {0x1F,0xC0,0x10,0x3C,0x00,0xE0,0x1F,0x00,0x00,0xE0,0x10,0x3C,0x1F,0xC0,0x00,0x00},/*"W",55*/
  {0x10,0x04,0x18,0x0C,0x16,0x34,0x01,0xC0,0x01,0xC0,0x16,0x34,0x18,0x0C,0x10,0x04},/*"X",56*/
  {0x10,0x00,0x1C,0x00,0x13,0x04,0x00,0xFC,0x13,0x04,0x1C,0x00,0x10,0x00,0x00,0x00},/*"Y",57*/
  {0x08,0x04,0x10,0x1C,0x10,0x64,0x10,0x84,0x13,0x04,0x1C,0x04,0x10,0x18,0x00,0x00},/*"Z",58*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x40,0x02,0x40,0x02,0x40,0x02,0x00,0x00},/*"[",59*/
  {0x00,0x00,0x30,0x00,0x0C,0x00,0x03,0x80,0x00,0x60,0x00,0x1C,0x00,0x03,0x00,0x00},/*"\",60*/
  {0x00,0x00,0x40,0x02,0x40,0x02,0x40,0x02,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"]",61*/
  {0x00,0x00,0x00,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00},/*"^",62*/
  {0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01},/*"_",63*/
  {0x00,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
  {0x00,0x00,0x00,0x98,0x01,0x24,0x01,0x44,0x01,0x44,0x01,0x44,0x00,0xFC,0x00,0x04},/*"a",65*/
  {0x10,0x00,0x1F,0xFC,0x00,0x88,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00},/*"b",66*/
  {0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x00},/*"c",67*/
  {0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x11,0x08,0x1F,0xFC,0x00,0x04},/*"d",68*/
  {0x00,0x00,0x00,0xF8,0x01,0x44,0x01,0x44,0x01,0x44,0x01,0x44,0x00,0xC8,0x00,0x00},/*"e",69*/
  {0x00,0x00,0x01,0x04,0x01,0x04,0x0F,0xFC,0x11,0x04,0x11,0x04,0x11,0x00,0x18,0x00},/*"f",70*/
  {0x00,0x00,0x00,0xD6,0x01,0x29,0x01,0x29,0x01,0x29,0x01,0xC9,0x01,0x06,0x00,0x00},/*"g",71*/
  {0x10,0x04,0x1F,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04},/*"h",72*/
  {0x00,0x00,0x01,0x04,0x19,0x04,0x19,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"i",73*/
  {0x00,0x00,0x00,0x03,0x00,0x01,0x01,0x01,0x19,0x01,0x19,0xFE,0x00,0x00,0x00,0x00},/*"j",74*/
  {0x10,0x04,0x1F,0xFC,0x00,0x24,0x00,0x40,0x01,0xB4,0x01,0x0C,0x01,0x04,0x00,0x00},/*"k",75*/
  {0x00,0x00,0x10,0x04,0x10,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,0x00,0x00},/*"l",76*/
  {0x01,0x04,0x01,0xFC,0x01,0x04,0x01,0x00,0x01,0xFC,0x01,0x04,0x01,0x00,0x00,0xFC},/*"m",77*/
  {0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x00,0x01,0x00,0x01,0x04,0x00,0xFC,0x00,0x04},/*"n",78*/
  {0x00,0x00,0x00,0xF8,0x01,0x04,0x01,0x04,0x01,0x04,0x01,0x04,0x00,0xF8,0x00,0x00},/*"o",79*/
  {0x01,0x01,0x01,0xFF,0x00,0x85,0x01,0x04,0x01,0x04,0x00,0x88,0x00,0x70,0x00,0x00},/*"p",80*/
  {0x00,0x00,0x00,0x70,0x00,0x88,0x01,0x04,0x01,0x04,0x01,0x05,0x01,0xFF,0x00,0x01},/*"q",81*/
  {0x01,0x04,0x01,0x04,0x01,0xFC,0x00,0x84,0x01,0x04,0x01,0x00,0x01,0x80,0x00,0x00},/*"r",82*/
  {0x00,0x00,0x00,0xCC,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x24,0x01,0x98,0x00,0x00},/*"s",83*/
  {0x00,0x00,0x01,0x00,0x01,0x00,0x07,0xF8,0x01,0x04,0x01,0x04,0x00,0x00,0x00,0x00},/*"t",84*/
  {0x01,0x00,0x01,0xF8,0x00,0x04,0x00,0x04,0x00,0x04,0x01,0x08,0x01,0xFC,0x00,0x04},/*"u",85*/
  {0x01,0x00,0x01,0x80,0x01,0x70,0x00,0x0C,0x00,0x10,0x01,0x60,0x01,0x80,0x01,0x00},/*"v",86*/
  {0x01,0xF0,0x01,0x0C,0x00,0x30,0x01,0xC0,0x00,0x30,0x01,0x0C,0x01,0xF0,0x01,0x00},/*"w",87*/
  {0x00,0x00,0x01,0x04,0x01,0x8C,0x00,0x74,0x01,0x70,0x01,0x8C,0x01,0x04,0x00,0x00},/*"x",88*/
  {0x01,0x01,0x01,0x81,0x01,0x71,0x00,0x0E,0x00,0x18,0x01,0x60,0x01,0x80,0x01,0x00},/*"y",89*/
  {0x00,0x00,0x01,0x84,0x01,0x0C,0x01,0x34,0x01,0x44,0x01,0x84,0x01,0x0C,0x00,0x00},/*"z",90*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x3E,0xFC,0x40,0x02,0x40,0x02},/*"{",91*/
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00},/*"|",92*/
  {0x00,0x00,0x40,0x02,0x40,0x02,0x3E,0xFC,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"}",93*/
  {0x00,0x00,0x60,0x00,0x80,0x00,0x80,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x20,0x00},/*"~",94*/
}; 

extern void SysCtlDelay(unsigned long ulCount);


/**
* @brief  初始化函数
* @param  无
* @retval 无
*/
void LCD_Init ( void )
{
  LMT028_Init ();	
}


/**
* @brief  LMT028初始化函数，如果用到lcd 要调用该函数
* @param  无
* @retval 无
*/
void LMT028_Init ( void )
{
  LMT028_GPIO_Config ();
  LMT028_FSMC_Config ();
  
  timer3_init();
  
  LMT028_Rst ();
  LMT028_REG_Config ();
  
  Set_Pen_Color(LCD_red);
  Set_Back_Color(LCD_black);
}


void LMT028_GPIO_Config ()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
  
  /* 配置控制线
  * PD14  :D0
  * PD15  :D1
  * PD0   :D2
  * PD1   :D3
  * PE7   :D4
  * PE8   :D5
  * PE9   :D6
  * PE10  :D7
  */
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD,&GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15 , GPIO_AF_FSMC);
  
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_Init(GPIOE,&GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  
  /* 配置控制线
  * PD4-FSMC_NOE   :LCD-RD
  * PD5-FSMC_NWE   :LCD-WR
  * PD7-FSMC_NE1   :LCD-CS
  * PD11-FSMC_A16  :LCD-DC
  */
  
  
  GPIO_InitStructure.GPIO_Pin=LCD_RD_Pin|LCD_WR_Pin|LCD_CS_Pin|LCD_DC_Pin;
  GPIO_Init(GPIOD,&GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource7 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource11 , GPIO_AF_FSMC);
  
  /* 配置LCD复位RST控制用脚 PC6*/     
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  GPIO_InitStructure.GPIO_Pin=LCD_RST_Pin;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  
  
  /* 配置LCD背光BK控制用脚 PC7*/  

  GPIO_PinAFConfig(GPIOC,LCD_BK_Pin,GPIO_AF_TIM3);

  GPIO_InitStructure.GPIO_Pin=LCD_BK_Pin;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  
  /* Connect TIM3 pins to PC7 */  
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);

}
  
  
  
void set_bk_value(uint16_t value)
{
  TIM_SetCompare2(TIM3,value);
}


/**
* @brief  LCD  FSMC 模式配置
* @param  无
* @retval 无
*/
void LMT028_FSMC_Config ( void )
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;  
  
  /* Enable FSMC clock */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); 
  
  
  readWriteTiming.FSMC_AddressSetupTime = 0x02;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 0x05;     // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
  
  
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;//  这里我们使用NE1 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;// 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM  
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;//存储器数据宽度为8bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;// 读写使用相同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;//读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming;//写时序
  
  
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置
  
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}


/**
* @brief  作为LCD的背光输出PWM.
* @param  None
* @retval None
*/
void timer3_init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  TIM_TimeBaseStructure.TIM_Period = 500;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock /2) / 100000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 249;//CCR2_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM3, ENABLE);
  
}


/**
* @brief  LMT028 软件复位
* @param  无
* @retval 无
*/
void LMT028_Rst ( void )
{			
  GPIO_ResetBits ( LCD_RST_GPIO, LCD_RST_Pin );	 
  
  Delay1ms(80);				   
  
  GPIO_SetBits ( LCD_RST_GPIO, LCD_RST_Pin );		 	 
  
  Delay1ms(80);		
}




/**
* @brief 设置坐标
* @param  X/Y:起始坐标 
* @retval 无
*/
void set_coordinate(uint16_t x,uint16_t y )
{
  uint8_t x_l,x_h,y_l,y_h;
  
  x_l=(x&0xff);
  x_h=((x>>8)&0xff);
  y_l=(y&0xff);
  y_h=((y>>8)&0xff);
  
  LMT028_Write_Cmd(0x2a); 
  LMT028_Write_Data(x_h);
  LMT028_Write_Data(x_l);
  
  LMT028_Write_Cmd(0x2b); 
  LMT028_Write_Data(y_h);
  LMT028_Write_Data(y_l); 
}

/**
  * @brief 设置窗体
  * @param  X/Y:起始坐标   width：区域宽度  height;区域高度  
  * @retval 无
  */

void set_windows(uint16_t X,uint16_t Y,uint16_t width,uint16_t height)
{
  uint8_t X_l,X_h,Y_l,Y_h;
  uint8_t width_l,width_h,height_l,height_h;
  
  X_l=(X&0xff);
  X_h=((X>>8)&0xff);
  Y_l=(Y&0xff);
  Y_h=((Y>>8)&0xff);
  
  width_l=((width+X)&0xff);
  width_h=(((width+X)>>8)&0xff);
  height_l=((height+Y)&0xff);
  height_h=(((height+Y)>>8)&0xff);
  
  // set column range as full screen
  LMT028_Write_Cmd(0x2a); 
  LMT028_Write_Data(X_h);
  LMT028_Write_Data(X_l); 
  LMT028_Write_Data(width_h);
  LMT028_Write_Data(width_l); 
  
  // set row range as full screen
  LMT028_Write_Cmd(0x2b); 
  LMT028_Write_Data(Y_h);
  LMT028_Write_Data(Y_l); 
  LMT028_Write_Data(height_h);
  LMT028_Write_Data(height_l);
}

/**
  * @brief 清除LMT028区域数据
  * @param  X/Y:起始坐标   width：区域宽度  height;区域高度 
  * @retval 无
  */
void clear_lcd_area(uint16_t X,uint16_t Y,uint16_t width,uint16_t height)
{
  uint32_t dp_y;
  uint32_t num;
  set_windows(X,Y,width,height);
  LMT028_Write_Cmd(0x2c);  
  num = width * height;
  for(dp_y = 0;dp_y < num;dp_y++){
    LMT028_Write_Data(0x00);
    LMT028_Write_Data(0x00);
  }
}
 
/**
 * @brief  初始化LMT028寄存器
 * @param  无
 * @retval 无
 */
 void LMT028_REG_Config ( void )
{
       // LMT028_Rst();
	LMT028_Write_Cmd ( 0x11  );
        Delay1ms  (150);
    
//--------------------------------ST7789S Frame rate setting----------------------------------//
	LMT028_Write_Cmd ( 0xB2  );
	LMT028_Write_Data ( 0x0C  );
	LMT028_Write_Data ( 0x0C  );
	LMT028_Write_Data ( 0x00 );
	LMT028_Write_Data ( 0x33 );
	LMT028_Write_Data ( 0x33 );
	LMT028_Write_Data ( 0xB7 );
	LMT028_Write_Data ( 0x35 );
        
////---------------------------------ST7789S Fmark setting--------------------------------------//
//        
//        LMT028_Write_Cmd ( 0xB3  );
//	LMT028_Write_Data ( 0x00  );
//	LMT028_Write_Data ( 0x0f  );
//	LMT028_Write_Data ( 0x0f );
//        
////        
//        SysCtlDelay(500); 
//        LMT028_Write_Cmd ( 0xC6  );
//	LMT028_Write_Data ( 0x1f);
//	
//---------------------------------ST7789S Power setting--------------------------------------//
        SysCtlDelay(500); 
	LMT028_Write_Cmd ( 0xBB);
	LMT028_Write_Data ( 0x28 );
        
        SysCtlDelay(500); 
 // mx,my,bgr,rev,ss,mh,mv,gs        
        LMT028_Write_Cmd ( 0xC0  );
	LMT028_Write_Data ( 0x2C );
        
        LMT028_Write_Cmd ( 0xC2  );
	LMT028_Write_Data ( 0x0f );
     
        SysCtlDelay(500); 
     //VRHS
        LMT028_Write_Cmd ( 0xC3  );
	LMT028_Write_Data ( 0x25);
      
        SysCtlDelay(500); 
    //VDV SET    
        LMT028_Write_Cmd ( 0xC4  );
	LMT028_Write_Data ( 0x20);
        
        SysCtlDelay(500); 
    // FRCTR2    
        LMT028_Write_Cmd ( 0xC6 );
	LMT028_Write_Data ( 0x0f);
        
        SysCtlDelay(500); 
        //regsel2 
	LMT028_Write_Cmd (0xCA);
	LMT028_Write_Data (0x0F );

        SysCtlDelay(500); 
	//regsel1
        LMT028_Write_Cmd ( 0xC8);
	LMT028_Write_Data ( 0x08 );
        
	SysCtlDelay(500); 
	// CABC
        LMT028_Write_Cmd ( 0x55);
	LMT028_Write_Data ( 0x90 );
        
        SysCtlDelay(500); 
	//PWCTRL1
        LMT028_Write_Cmd ( 0xd0);
	LMT028_Write_Data ( 0xa4 );
        LMT028_Write_Data ( 0xa1);
        
        SysCtlDelay(500); 
 //--------------------------------ST7789S gamma setting---------------------------------------//
        LMT028_Write_Cmd(0xe0);
	LMT028_Write_Data(0xd0);
	LMT028_Write_Data(0x03);
	LMT028_Write_Data(0x08);
	LMT028_Write_Data(0x0b);
	LMT028_Write_Data(0x0f);
	LMT028_Write_Data(0x2c);
	LMT028_Write_Data(0x41);
	LMT028_Write_Data(0x54);
	LMT028_Write_Data(0x4e);
	LMT028_Write_Data(0x07);
	LMT028_Write_Data(0x0e);
	LMT028_Write_Data(0x0c);
	LMT028_Write_Data(0x1e);
	LMT028_Write_Data(0x23); 
        
        SysCtlDelay(500); 
        LMT028_Write_Cmd(0xe1);
	LMT028_Write_Data(0xd0);
	LMT028_Write_Data(0x03);
	LMT028_Write_Data(0x09);
	LMT028_Write_Data(0x0b);
	LMT028_Write_Data(0x0d);
	LMT028_Write_Data(0x19);
	LMT028_Write_Data(0x3c);
	LMT028_Write_Data(0x54);
	LMT028_Write_Data(0x4f);
	LMT028_Write_Data(0x0e);
	LMT028_Write_Data(0x1d);
	LMT028_Write_Data(0x1c);
	LMT028_Write_Data(0x20);
	LMT028_Write_Data(0x22); 
        
        SysCtlDelay(500); 
        //65k色，16bit
        LMT028_Write_Cmd(0x3a);
        LMT028_Write_Data(0x55);
        
        SysCtlDelay(500); 
        //设置: MY=1, MX=1, MV=1(RowColEx), ML=0(normal), RGB=0(RGB)
        LMT028_Write_Cmd(0x36);
        //LMT028_Write_Data(0x60);  //信号线在右边  从左上到右下
        LMT028_Write_Data(0x60);
        
        SysCtlDelay(500); 
        //开启撕裂影响线
        LMT028_Write_Cmd(0x35);
        LMT028_Write_Data(0x00);
        
        SysCtlDelay(500); 
        
        //显示开
        LMT028_Write_Cmd(0x29);
        
        SysCtlDelay(500); 
        clear_lcd_area(0,0,320,240);      
}


/**
* @brief 设置填充lcd缓存模式  （以下缓存赋值以信号线为右边为标准）
* @param  show_type 赋值类型
* @retval 无
*/

void set_show_type(uint8_t show_type)
{
  switch(show_type)
  {
    //左上到右下
  case 1:
    {
      LMT028_Write_Cmd(0x36);
      LMT028_Write_Data(0x60);
      break;
    }
    
    //右上到左下
  case 2:
    {
      LMT028_Write_Cmd(0x36);
      LMT028_Write_Data(0x40);
      break;
    }
    
    //左下到右上
  case 3:
    {
      LMT028_Write_Cmd(0x36);
      LMT028_Write_Data(0x00);
      break;
    }
    
    //右下到左上
  case 4:
    {
      LMT028_Write_Cmd(0x36);
      LMT028_Write_Data(0x80);
      break;
    }
    
  }
}


/**
* @brief  Read the selected LCD register.
* @param  LCD_Reg: address of the selected register.
* @retval LCD register value
*/
uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
  uint16_t data;
  data = LCD->LCD_CMD; 
  return  data;
}



/**
* @brief  向LMT028写入命令
* @param  usData :要写入的命令（表寄存器地址）
* @retval 无
*/
void LMT028_Write_Cmd ( uint8_t usCmd )
{
  LCD->LCD_CMD=usCmd;	
}


/**
* @brief  向LMT028写入数据
* @param  usData :要写入数据（表寄存器地址）
* @retval 无
*/	
void LMT028_Write_Data ( uint8_t usData )
{
  LCD->LCD_DATA = usData;
}
/*!
* @brief	设置画笔颜色
* @param        Pen_Color 点的颜色
* @return	NONE
* @note	       NONE
*/
void Set_Pen_Color(uint16_t Pen_Color )
{
  POINT_COLOR=Pen_Color;
}

/*!
* @brief	设置背景颜色
* @param        Back_Color 颜色
* @return	NONE
* @note	       NONE
*/
void Set_Back_Color(uint16_t Pen_Color)
{
  BACK_COLOR=Pen_Color;
}

/*!
* @brief	画点
* @param 	x     坐标x
* @param 	y     坐标y
* @param        color 点的颜色
* @return	NONE
* @note	       NONE
*/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
  uint8_t color_h,color_l;
  
  color_h=(color>>8)&0xff;
  color_l=color&0xff;
  
  set_coordinate(x,y);//设置光标位置
  
  LMT028_Write_Cmd(0x2c); 
  LMT028_Write_Data(color_h);
  LMT028_Write_Data(color_l);
}

/*!
* @brief   画线
* @param   x1,y1:起点坐标
* @param   x2,y2:结束坐标 
* @param   color:颜色 
* @return	NONE	
*/	  
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{         
  u16 t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance; 
  int incx,incy,uRow,uCol; 
  delta_x=x2-x1; //计算坐标增量
  delta_y=y2-y1; 
  uRow=x1; 
  uCol=y1; 
  if(delta_x>0)
    incx=1; //设置单步方向
  else if(delta_x==0)
    incx=0;//垂直线
  else 
  {
    incx=-1;
    delta_x=-delta_x;
  } 
  if(delta_y>0)incy=1; 
  else if(delta_y==0)
    incy=0;//水平线 
  else
  {
    incy=-1;
    delta_y=-delta_y;
  } 
  if( delta_x>delta_y)
    distance=delta_x; //选取基本增量坐标轴
  else 
    distance=delta_y; 
  for(t=0;t<=distance+1;t++ )//画线输出
  {  
    LCD_DrawPoint(uRow,uCol,color);//画点
    xerr+=delta_x ; 
    yerr+=delta_y ; 
    if(xerr>distance) 
    { 
      xerr-=distance; 
      uRow+=incx; 
    } 
    if(yerr>distance) 
    { 
      yerr-=distance; 
      uCol+=incy; 
    } 
  }  
}


/*!
* @brief   显示字符串
* @param   x,y:起点坐标
* @param   width,height:区域大小 
* @param   *s:字符串起始地址
* @return	NONE	
*/
void LCD_ShowString(uint16_t x,uint16_t y, char *s)
{         
  char x0=x;
  while((*s<='~')&&(*s>=' '))//判断是不是非法字符
  {       
    if(x>=320)
    {
      x=x0;y+=16;
    }
    if(y>=240)
      break;//退出
    LCD_ShowChar(x,y,*s,16,0);
    x+=16/2;
    s++;
  }  
}

/*!
* @brief	在制定位置显示一个字符
* @param 	P 开始坐标以及宽度高度
* @param 	num:要显示的字符
* @param       size:字体大小  12/16/24
* @param       mode:叠加方式（1）  非叠加方式（0）
* @return	NONE	
*/
void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t num,uint16_t size,uint16_t mode)
{  							  
  uint16_t temp,t1,t;
  uint16_t y0=y;
  uint16_t csize=(size/8+((size%8)?1:0))*(size/2); //得到一个字符对应点阵集所占的字节数	
  num=num-' ';//得到偏移后的值
  for(t=0;t<csize;t++)
  {   
    temp=ASCII_0816[num][t];
    for(t1=0;t1<8;t1++)
    {			    
      if(temp&0x80)
        LCD_DrawPoint(x,y,POINT_COLOR);
      else if(mode==0)
        LCD_DrawPoint(x,y,BACK_COLOR);
      temp<<=1;  
      y++;
      if((y-y0)==size)
      {
        y=y0;
        x++;
      }
    }  	 
  }  	    	   	 	  
}

/**
* @brief  延时1us
* @param  usData :要写入的命令（表寄存器地址）
* @retval 无
*/

void  Delay_1us(uint16_t k){
  uint32_t i;
  for (i=0;i<1*k;i++){
    SysCtlDelay(120000000/3300000);  //1us
  }
}


/**
* @brief  延时1ms
* @param  usData :要写入的命令（表寄存器地址）
* @retval 无
*/

void  Delay1ms(uint16_t k)
{
  uint32_t i;
  for (i=0;i<k;i++){
    Delay_1us(1000);  //1us
  }
}

