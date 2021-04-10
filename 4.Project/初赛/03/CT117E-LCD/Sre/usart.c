#include "usart.h"

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void USART_RCC_Configuration(void)
{   
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable USART2 Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void USART_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Configure USART2 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void USART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void usart_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	/* System Clocks Configuration */
  USART_RCC_Configuration();
       
  /* NVIC configuration */
  USART_NVIC_Configuration();

  /* Configure the GPIO ports */
  USART_GPIO_Configuration();

/* USART2 onfiguration ------------------------------------------------------*/
  /* USART2 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx;

  /* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);
  
  /* Enable USART2 Receive interrupts */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  /* Enable the USART2 */
  USART_Cmd(USART2, ENABLE);
}
