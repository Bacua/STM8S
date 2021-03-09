/**
  ******************************************************************************
  * @file    EXTI_InterruptPriority\main.c
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   This file contains the main function for the EXTI Interrupt Priority example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
#include "stm8s.h"
//#include "main.h"

/**
  * @addtogroup EXTI_InterruptPriority
  * @{
  */
#define LED7_PORT_L  (GPIOC)
#define LED7A (GPIO_PIN_4)
#define LED7B (GPIO_PIN_5)
#define LED7C (GPIO_PIN_6)
#define LED7D (GPIO_PIN_7)

#define LED7_PORT_H  (GPIOD)
#define LED7E (GPIO_PIN_2)
#define LED7F (GPIO_PIN_3)
#define LED7G (GPIO_PIN_5)
#define LED7H (GPIO_PIN_6)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);
void Sang_led (uint8_t so);
void dorongxung_1(uint16_t dorongxung);
static void TIM2_Config(void);


volatile uint8_t dem = 0;

const uint8_t ma_led7[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};
                          //0    1     2    3    4   5    6    7    8    9     tat
const GPIO_Pin_TypeDef led7_pin[8]={LED7A,LED7B,LED7C,LED7D,LED7E,LED7F,LED7G,LED7H};



/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

  /* GPIO Configuration  -----------------------------------------*/
  GPIO_DeInit(GPIOA);
  GPIO_Init(GPIOA,GPIO_PIN_3,GPIO_MODE_IN_PU_IT);
  
  GPIO_Init(LED7_PORT_L, (GPIO_Pin_TypeDef)(LED7A|LED7B|LED7C|LED7D), GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(LED7_PORT_H, (GPIO_Pin_TypeDef)(LED7E|LED7F|LED7G|LED7H), GPIO_MODE_OUT_PP_HIGH_SLOW);

  /* TIM2 configuration -----------------------------------------*/
  TIM2_Config();  

  /* Initialize the Interrupt sensitivity */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);
  
  enableInterrupts();

  while (1)
  {
    /* The LED toggles in the interrupt routines */
  }

}

static void TIM2_Config(void)
{
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 999);

  /* PWM1 Mode configuration: Channel1 */ 
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

void dorongxung_1(uint16_t dorongxung){
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,dorongxung, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);
}

void Sang_led (uint8_t so){
  if(so>9){
    so=9;
  }
  uint8_t madk=ma_led7[so];
  uint8_t i,dk;
  for(i =0;i<8;i++){
    //dich=1<<i;
    dk=(madk>>i)&1;
    if(dk==1){
      if(i<4){
        GPIO_WriteHigh(LED7_PORT_L,led7_pin[i]);
      }
      else {
        GPIO_WriteHigh(LED7_PORT_H,led7_pin[i]);
      }
    }
    else {
      if(i<4){
        GPIO_WriteLow(LED7_PORT_L,led7_pin[i]);
      }
      else {
        GPIO_WriteLow(LED7_PORT_H,led7_pin[i]);
      }
    }
  }
}

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
