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

uint32_t Touchpad_default_val;
void TIM_Config(void);
uint8_t Touchpad_Init(void);
uint8_t Touchpad_Scan(uint8_t mode);

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
  uint32_t t=0; 
  uint32_t time=0; 
  char LCD_string[200];
  
  
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
  
  if(Touchpad_Init()){
    LCD_ShowString(0,0,"Touchpad Init ERR");
  }else{
    sprintf(LCD_string,"Touchpad Init OK,tpad_default_val:%dus \r\n",Touchpad_default_val);
    LCD_ShowString(0,0,(char*)LCD_string);
  }
  
  while (1)
  {
    if(Touchpad_Scan(0))
    {
      time++;
      if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_4)){
        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
      }else{
        GPIO_SetBits(GPIOE,GPIO_Pin_4);
      }
      sprintf(LCD_string,"Touchpad press down,time is : %d \r\n",time);
      LCD_ShowString(0,16,(char*)LCD_string);
    }
    t++;
    if(t==10){
      t=0;
    }
    Delay(5);
  }
}
void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* TIM12 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  /* Connect TIM pins to AF9 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
  
  /* TIM12 channel 1 pin (PB14) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);



  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock/2) / 1000000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
 
}

void Touchpad_Reset()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_ResetBits(GPIOB,GPIO_Pin_14);
  
  SysCtlDelay(5*(SystemCoreClock/3000));
  
  TIM_ClearITPendingBit(TIM12, TIM_IT_Update|TIM_IT_CC1); 
  TIM_SetCounter(TIM12,0);
  
  
  /* Connect TIM pins to AF9 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM12);
  
  /* TIM12 channel 1 pin (PB14) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


uint16_t Touchpad_Get_Val()
{
  Touchpad_Reset();
  while(TIM_GetFlagStatus(TIM12, TIM_IT_CC1) == RESET)//�ȴ�����������
  {
    if(TIM_GetCounter(TIM12)>(0XFFFF-500))
      return TIM_GetCounter(TIM12);//��ʱ��,ֱ�ӷ���CNT��ֵ
  }
  return TIM_GetCapture1(TIM12);	 
}

uint8_t Touchpad_Init(void)
{
  uint16_t buf[10];
  uint16_t temp;
  uint8_t j,i;   
  
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  
  /* TIM12 Configuration */
  TIM_Config();

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_ICInit(TIM12, &TIM_ICInitStructure);
  
  /* Enable the CC1 Interrupt Request */
  TIM_ITConfig(TIM12, TIM_IT_CC1|TIM_IT_Update, ENABLE);
  
  /* TIM enable counter */
  TIM_Cmd(TIM12, ENABLE);
  
  for(i=0;i<10;i++)//������ȡ10��
  {				 
    buf[i]=Touchpad_Get_Val();
    SysCtlDelay(10*(SystemCoreClock/3000));    
  }
  
  for(i=0;i<9;i++)//����
  {
    for(j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])//��������
      {
	temp=buf[i];
	buf[i]=buf[j];
	buf[j]=temp;
      }
    }
  }
  
  temp=0;
  for(i=2;i<8;i++){
    temp+=buf[i];//ȡ�м��8�����ݽ���ƽ��
  }
  Touchpad_default_val=temp/6;	
  if(Touchpad_default_val>0XFFFF/2)
    return 1;//��ʼ����������Touchpad_ARR_MAX_VAL/2����ֵ,������!
  return 0;	
}

/**
  * @brief  ��ȡn��,ȡ���ֵ
  * @param  n��������ȡ�Ĵ���
  * @retval n�ζ������������������ֵ
  */
uint16_t Touchpad_Get_MaxVal(u8 n)
{
  uint16_t temp=0;
  uint16_t res=0; 
  while(n--)
  {
    temp=Touchpad_Get_Val();//�õ�һ��ֵ
    SysCtlDelay(5*(SystemCoreClock/3000));
    if(temp>res)res=temp;
  };
  return res;
}  

/**
  * @brief  ɨ�败������
  * @param  mode:0,��֧����������(����һ�α����ɿ����ܰ���һ��);1,֧����������(����һֱ����)
  * @retval 0,û�а���;1,�а���;
  */
#define Touchpad_GATE_VAL 	20	//����������ֵ,Ҳ���Ǳ������Touchpad_default_val+Touchpad_GATE_VAL,����Ϊ����Ч����.
uint8_t Touchpad_Scan(uint8_t mode)
{
  static uint8_t keyen=0;	//0,���Կ�ʼ���;>0,�����ܿ�ʼ���	 
  uint8_t res=0;
  uint8_t sample=3;		//Ĭ�ϲ�������Ϊ3��	 
  uint16_t rval;
  if(mode)
  {
    sample=6;	//֧��������ʱ�����ò�������Ϊ6��
    keyen=0;	//֧������	  
  }
  rval=Touchpad_Get_MaxVal(sample); 
  if(rval>(Touchpad_default_val+Touchpad_GATE_VAL)&&rval<(10*Touchpad_default_val))//����Touchpad_default_val+Touchpad_GATE_VAL,��С��10��Touchpad_default_val,����Ч
  {							 
    if((keyen==0)&&(rval>(Touchpad_default_val+Touchpad_GATE_VAL)))	//����Touchpad_default_val+Touchpad_GATE_VAL,��Ч
    {
      res=1;
    }
    keyen=3;				//����Ҫ�ٹ�3��֮����ܰ�����Ч   
  } 
  if(keyen)
    keyen--;		   							   		     	    					   
  return res;
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
