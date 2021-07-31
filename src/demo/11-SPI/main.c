/**
  ******************************************************************************
  * @file    Project/STM32F2xx_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "LCD_disp.h"
#include "Ex_Flash.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

void FLASH_GPIO_Init(void);
void FLASH_SPIInit(void);

extern EX_Flash_struct  EX_Flash;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  GPIO_InitTypeDef  GPIO_Init_s;
  uint8_t  uid[8];
  uint32_t RDID_data;
  uint32_t i;

  uint8_t buf[200];
  char str[200];
  
  /* ����SysTickΪ1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  /* ʹ��GPIOE�˿�ʱ�� */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  
  /* ����LED�ܽ� */
  GPIO_Init_s.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init_s.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Init_s.GPIO_OType = GPIO_OType_PP;
  GPIO_Init_s.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init_s.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_Init_s);
  
  LCD_Init();
  FLASH_SPIInit();
  EX_FLASH_init();//�����ȵ���1�Σ���ȡFlash����Ϣ
  
  Ex_FLASH_ReadUID(uid);  
  sprintf(str,"UID  of NOR Flash : %x%x%x%x%x%x%x%x\r\n",uid[0],uid[1],uid[2],uid[3],uid[4],uid[5],uid[6],uid[7]);
  LCD_ShowString(0,16*0,(char*)str);
  
  RDID_data = Ex_FLASH_ReadID();
  sprintf(str,"RDID of NOR Flash : %x",RDID_data);
  LCD_ShowString(0,16*1,(char*)str);
  
  switch(EX_Flash.Flash_stype){
  case Winbond_Flash:
    sprintf(str,"Manufactor of NOR Flash is Winbond_Flash");
    break;
  case GD_Flash:
    sprintf(str,"Manufactor of NOR Flash is Winbond_Flash");
    break;
  default:
    sprintf(str,"Manufactor of NOR Flash is not know");
    break;
  }
  
  LCD_ShowString(0,16*3,(char*)str);
  
  switch(EX_Flash.Flash_Memory){
  case Flash_2M:
    sprintf(str,"Capacity of NOR Flash is 2M");
    break;
  case Flash_4M:
    sprintf(str,"Capacity of NOR Flash is 4M");
    break;
  default:
    sprintf(str,"Capacity of NOR Flash is not know");
    break;
  }
  LCD_ShowString(0,16*4,(char*)str);
  
  
  for(i=0;i<50;i++){
    buf[i]='A';
  }
  
  ExFlash_Erase_Sec(0);
  LCD_ShowString(0,16*6,"Erase sector 0");
  
  ExFlash_WR_NByte(0,buf, 50);
  LCD_ShowString(0,16*7,"Write 50 A to sector 0");
  
  for(i=0;i<60;i++){
    buf[i]=0x00;
  }
  
  ExFlash_RD(0,buf,50);
  sprintf(str,"%s",buf);
  LCD_ShowString(0,16*8,"The data read by sector 0 is ");
  LCD_ShowString(0,16*9,(char*)str);
  
  while (1)
  { 
    GPIO_SetBits(GPIOE,GPIO_Pin_4);  //Ϩ��LED��
    Delay(500);                      //��ʱ500ms
    GPIO_ResetBits(GPIOE,GPIO_Pin_4);//����LED��
    Delay(500);                      //��ʱ500ms
  }
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t SPI_ReadWriteByte(uint8_t data)
{
  while(!(SPI1->SR & SPI_I2S_FLAG_TXE));
  SPI1->DR = data;
  while(!(SPI1->SR & SPI_I2S_FLAG_RXNE));
  return SPI1->DR;                                               
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void FLASH_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*!< Enable the SPI clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
  /*!< Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
  /*!< SPI pins configuration *************************************************/
  
  /*!< Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(GPIOA, 5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, 6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOB, 5, GPIO_AF_SPI1);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//GPIO_PuPd_DOWN;
  
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /*!< Configure sFLASH Card CS pin in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void  FLASH_SPIInit(void)
{  
  
  SPI_InitTypeDef  SPI_InitStructure;
  
  FLASH_GPIO_Init();
  
  /*!< Deselect the FLASH: Chip Select high */
  GPIO_SetBits(GPIOE,GPIO_Pin_12);
  
  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//�� SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;// SPI ���ͽ��� 8 λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//�ڶ������������ݱ�����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS �ź����������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//Ԥ��Ƶ 16
  
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ���� MSB λ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7;//CRC ֵ����Ķ���ʽ
  SPI_Init(SPI1, &SPI_InitStructure);
  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(SPI1, ENABLE);
}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


/*120Mhzʱ��ʱ����ulCountΪ1ʱ��������ʱ3��ʱ�ӣ���ʱ=3*1/120us=1/40us*/
/*
SystemCoreClock=120000000

us����ʱ,��ʱn΢��
SysCtlDelay(n*(SystemCoreClock/3000000));

ms����ʱ,��ʱn����
SysCtlDelay(n*(SystemCoreClock/3000));

m����ʱ,��ʱn��
SysCtlDelay(n*(SystemCoreClock/3));
*/

#if defined   (__CC_ARM) /*!< ARM Compiler */
__asm void
SysCtlDelay(unsigned long ulCount)
{
    subs    r0, #1;
    bne     SysCtlDelay;
    bx      lr;
}
#elif defined ( __ICCARM__ ) /*!< IAR Compiler */
void
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
       "    bne.n   SysCtlDelay\n"
       "    bx      lr");
}

#elif defined (__GNUC__) /*!< GNU Compiler */
void __attribute__((naked))
SysCtlDelay(unsigned long ulCount)
{
    __asm("    subs    r0, #1\n"
       "    bne     SysCtlDelay\n"
       "    bx      lr");
}

#elif defined  (__TASKING__) /*!< TASKING Compiler */                           
/*��*/
#endif /* __CC_ARM */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
