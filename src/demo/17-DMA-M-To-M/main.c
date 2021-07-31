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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

const uint32_t SRC_Const_Buffer[32]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
uint32_t DST_Buffer[32];

void DMA_Config(void);

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
  uint8_t num;
  
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
  
  /* Configure and enable the DMA Stream for Memory to Memory transfer */
  DMA_Config();
  
  /* Wait the end of transmission (the DMA Stream is disabled by Hardware at the 
     end of the transfer) .
     There is also another way to check on end of transfer by monitoring the 
     number of remaining data to be transferred. */
  /* while (DMA_GetCurrentMemoryTarget(DMA_STREAM) != 0) */  /* First method */
  while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)            /* Second method */
  {
    /*
       Since this code present a simple example of how to use DMA, it is just
       waiting on the end of transfer.
       But, while DMA Stream is transferring data, the CPU is free to perform 
       other tasks in parallel to the DMA transfer.
    */
  }
  for(num = 0;num<32;num++)
  {
    if(SRC_Const_Buffer[num] != DST_Buffer[num])
      break;
  }
  if(num == 32)
  {
    Set_Pen_Color(LCD_grenn);
    LCD_ShowString(0,0,"Memory to memory test is ok");
  }
  else
  {
    Set_Pen_Color(LCD_red);
    LCD_ShowString(0,0,"Memory to memory test is wrong");
  }
  

  while (1)
  {
    GPIO_SetBits(GPIOE,GPIO_Pin_4);  //Ϩ��LED��
    Delay(500);                      //��ʱ500ms
    GPIO_ResetBits(GPIOE,GPIO_Pin_4);//����LED��
    Delay(500);                      //��ʱ500ms
  }
}
/**
  * @brief  Configure the DMA controller according to the Stream parameters
  *         defined in main.h file 
  * @param  None
  * @retval None
  */
void DMA_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
  __IO uint32_t    Timeout = 10000;
    
  /* Enable DMA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* Reset DMA Stream registers (for debug purpose) */
  DMA_DeInit(DMA2_Stream0);

  /* Check if the DMA Stream is disabled before enabling it.
     Note that this step is useful when the same Stream is used multiple times:
     enabled, then disabled then re-enabled... In this case, the DMA Stream disable
     will be effective only at the end of the ongoing data transfer and it will 
     not be possible to re-configure it before making sure that the Enable bit 
     has been cleared by hardware. If the Stream is used only once, this step might 
     be bypassed. */
  while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)
  {
  }
  
  /* Configure DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //DMA���󷢳�ͨ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Const_Buffer;//���������ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DST_Buffer;//���ô洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;//���䷽������
  DMA_InitStructure.DMA_BufferSize = (uint32_t)32;//�����С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//ReceiveBuff��ַ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//SENDBUFF_SIZE��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//ReceiveBuff���ݵ�λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;//SENDBUFF_SIZE���ݵ�λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMAģʽ������ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//���ȼ�����
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;//FIFO ģʽ��ʹ��.          
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;// FIFO ��ֵѡ��
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ��ģʽѡ�񣬿�ѡ����ģʽ�� 4 ���ĵ�����ͻ��ģʽ�� 8 ���ĵ�����ͻ��ģʽ�� 16 ���ĵ�����ͻ��ģʽ�� 
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ��ģʽѡ�񣬿�ѡ����ģʽ�� 4 ���ĵ�����ͻ��ģʽ�� 8 ���ĵ�����ͻ��ģʽ�� 16 ���ĵ�����ͻ��ģʽ��
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    
  /* Enable DMA Stream Transfer Complete interrupt */
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

  /* DMA Stream enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* Check if the DMA Stream has been effectively enabled.
     The DMA Stream Enable bit is cleared immediately by hardware if there is an 
     error in the configuration parameters and the transfer is no started (ie. when
     wrong FIFO threshold is configured ...) */
  Timeout = 10000;
  while ((DMA_GetCmdStatus(DMA2_Stream0) != ENABLE) && (Timeout-- > 0))
  {
  }
   
  /* Check if a timeout condition occurred */
  if (Timeout == 0)
  {
    /* Manage the error: to simplify the code enter an infinite loop */
    while (1)
    {
    }
  }

  /* Enable the DMA Stream IRQ Channel */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);     
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
