/**
  ******************************************************************************
  * @file    GPIO_Toggle\main.c
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief   This file contains the main function for GPIO Toggle example.
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

#include <stm8s.h>
#include <stdlib.h>
#include <stdarg.h>

/* GPIO */
#define PA_ODR *(unsigned char*)0x5000
#define PA_IDR *(unsigned char*)0x5001
#define PA_DDR *(unsigned char*)0x5002
#define PA_CR1 *(unsigned char*)0x5003
#define PA_CR2 *(unsigned char*)0x5004

#define PB_ODR *(unsigned char*)0x5005
#define PB_IDR *(unsigned char*)0x5006
#define PB_DDR *(unsigned char*)0x5007
#define PB_CR1 *(unsigned char*)0x5008
#define PB_CR2 *(unsigned char*)0x5009

#define PC_ODR *(unsigned char*)0x500A
#define PC_IDR *(unsigned char*)0x500B
#define PC_DDR *(unsigned char*)0x500C
#define PC_CR1 *(unsigned char*)0x500D
#define PC_CR2 *(unsigned char*)0x500E

#define PD_ODR *(unsigned char*)0x500F
#define PD_IDR *(unsigned char*)0x5010
#define PD_DDR *(unsigned char*)0x5011
#define PD_CR1 *(unsigned char*)0x5012
#define PD_CR2 *(unsigned char*)0x5013

#define PE_ODR *(unsigned char*)0x5014
#define PE_IDR *(unsigned char*)0x5015
#define PE_DDR *(unsigned char*)0x5016
#define PE_CR1 *(unsigned char*)0x5017
#define PE_CR2 *(unsigned char*)0x5018

#define PF_ODR *(unsigned char*)0x5019
#define PF_IDR *(unsigned char*)0x501A
#define PF_DDR *(unsigned char*)0x501B
#define PF_CR1 *(unsigned char*)0x501C
#define PF_CR2 *(unsigned char*)0x501D

///////////////////////////////////////////////////////////////////////////////
////////////////////// CLOCK set AT 16MHz HSI /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* CLOCK */
#define CLK_SWR 	*(unsigned char*)0x50C4
#define CLK_SWCR	*(unsigned char*)0x50C5
#define CLK_DIVR	*(unsigned char*)0x50C6

void setUpClock()
{
    CLK_DIVR = 0x00;  // disable presacler
    CLK_SWCR |= 0x02; // enable clock switching
    CLK_SWR =  0xE1;  // HSI as new clock
    while( ( CLK_SWCR & 0x01 ) != 0 );
}


///////////////////////////////////////////////////////////////////////////////
////////////////////// TIMER 4 ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define TIM4_CR1 	*(unsigned char*)0x5340
#define TIM4_IER 	*(unsigned char*)0x5343
#define TIM4_SR 	*(unsigned char*)0x5344
#define TIM4_EGR 	*(unsigned char*)0x5345
#define TIM4_CNTR 	*(unsigned char*)0x5346
#define TIM4_PSCR 	*(unsigned char*)0x5347
#define TIM4_ARR 	*(unsigned char*)0x5348

void setUpTimer4()
{
    // main clock 16 MHZ
    // prescaler 64
    // timer clock 250KHz
    // Counter 250
    // interrupt at every 1ms

    TIM4_PSCR = 0x06;
    TIM4_ARR = 249;
    TIM4_IER = 0x01;
    TIM4_CR1 = 0x01;
}

unsigned long long millis = 0;
void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    millis++;
    TIM4_SR = 0x00;
}

unsigned long long micros()
{
    return (millis*1000 + (TIM4_CNTR + 1)*4 );
}

void delay( unsigned long inMs )
{
    unsigned long long offset = millis + inMs;
    while( offset >= millis );
}

///////////////////////////////////////////////////////////////////////////////
////////////////////// UART1 //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define UART1_SR	*(unsigned char*)0x5230
#define UART1_DR	*(unsigned char*)0x5231
#define UART1_BRR1	*(unsigned char*)0x5232
#define UART1_BRR2	*(unsigned char*)0x5233
#define UART1_CR2	*(unsigned char*)0x5235
#define UART1_CR3	*(unsigned char*)0x5236

#define UART_CR2_TEN (1 << 3)
#define UART_SR_TXE (1 << 7)

void putchar(char c)
{
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void setUpSerial()
{
    UART1_CR2 = UART_CR2_TEN; //enable tx

    // 9600 baud
    UART1_BRR2 = 0x03;
    UART1_BRR1 = 0x68;
}

char charFromHex(unsigned char num)
{
    char ch = '0';
    if(num < 10)
        return ch + num ;
    switch(num)
    {
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    default:
        return 0;
    }
}

void sendString(const char *msg)
{
    while(*msg!='\0')
    {
        putchar(*msg);
        msg++;
    }
}

void sendBuffer(const char *msg,uint16_t num)
{
    int i = 0;
    while(i < num)
        putchar(msg[i++]);

}

void printInt(int n, unsigned char base)
{
    char buffer[11] = {0};
    char i = 9;

    if( n < 0)
    {
        putchar('-');
        n = -n;
    }

    switch(base)
    {
    case 16:
        sendString("0x");
        break;
    default:
        break;
    }

    if(n == 0)
        putchar('0');

    while(n)
    {
        buffer[i--] = charFromHex(n % base);
        n /= base;
    }
    sendString(&buffer[i + 1]);
}

void printf(char* format,...)
{
    va_list ap;	/* points to each unnamed arg in turn */
    char *p,*sval;
    int ival;

    va_start(ap,format);	/* make ap point to 1st unnamed arg */

    for(p=format;*p;p++)
    {
        if(*p != '%')
        {
            putchar(*p);
            continue;
        }

        switch(*++p)
        {
        case 'd':
            ival = va_arg(ap,int);
            printInt(ival, 10);
            break;
        case 'X':
        case 'x':
            ival = va_arg(ap,int);
            printInt(ival, 16);
            break;
        case 's':
            for(sval = va_arg(ap,char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            putchar(ival);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);	/* clean up when done */
}

///////////////////////////////////////////////////////////////////////////////
////////////////////// ADC //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

int main()
{
    uint16_t adcValue = 0;
    setUpClock();
    setUpSerial();
    // Configure pins
    PB_DDR = 0x20;
    PB_CR1 = 0x20;

    // Timer related stuff
    setUpTimer4();
    enableInterrupts();

    // ADC related stuff
    // Default value is fine input

    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
              ADC1_CHANNEL_2,
              ADC1_PRESSEL_FCPU_D4,
              ADC1_EXTTRIG_GPIO,
              DISABLE,
              ADC1_ALIGN_RIGHT,
              ADC1_SCHMITTTRIG_CHANNEL2,
              DISABLE);

    ADC1_Cmd(ENABLE);
    while( 1 )
    {
        ADC1_StartConversion();
        while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == FALSE);
        adcValue = ADC1_GetConversionValue();
        ADC1_ClearFlag(ADC1_FLAG_EOC);
        PB_ODR ^= 0x20;
        printf("%d\n", adcValue);
        delay( 100 );
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
