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
#define PA_ODR *(__IO uint8_t*)0x5000
#define PA_IDR *(__IO uint8_t*)0x5001
#define PA_DDR *(__IO uint8_t*)0x5002
#define PA_CR1 *(__IO uint8_t*)0x5003
#define PA_CR2 *(__IO uint8_t*)0x5004

#define PB_ODR *(__IO uint8_t*)0x5005
#define PB_IDR *(__IO uint8_t*)0x5006
#define PB_DDR *(__IO uint8_t*)0x5007
#define PB_CR1 *(__IO uint8_t*)0x5008
#define PB_CR2 *(__IO uint8_t*)0x5009

#define PC_ODR *(__IO uint8_t*)0x500A
#define PC_IDR *(__IO uint8_t*)0x500B
#define PC_DDR *(__IO uint8_t*)0x500C
#define PC_CR1 *(__IO uint8_t*)0x500D
#define PC_CR2 *(__IO uint8_t*)0x500E

#define PD_ODR *(__IO uint8_t*)0x500F
#define PD_IDR *(__IO uint8_t*)0x5010
#define PD_DDR *(__IO uint8_t*)0x5011
#define PD_CR1 *(__IO uint8_t*)0x5012
#define PD_CR2 *(__IO uint8_t*)0x5013

#define PE_ODR *(__IO uint8_t*)0x5014
#define PE_IDR *(__IO uint8_t*)0x5015
#define PE_DDR *(__IO uint8_t*)0x5016
#define PE_CR1 *(__IO uint8_t*)0x5017
#define PE_CR2 *(__IO uint8_t*)0x5018

#define PF_ODR *(__IO uint8_t*)0x5019
#define PF_IDR *(__IO uint8_t*)0x501A
#define PF_DDR *(__IO uint8_t*)0x501B
#define PF_CR1 *(__IO uint8_t*)0x501C
#define PF_CR2 *(__IO uint8_t*)0x501D

///////////////////////////////////////////////////////////////////////////////
////////////////////// CLOCK set AT 16MHz HSI /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* CLOCK */
#define CLK_SWR 	*(__IO uint8_t*)0x50C4
#define CLK_SWCR	*(__IO uint8_t*)0x50C5
#define CLK_DIVR	*(__IO uint8_t*)0x50C6

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

#define TIM4_CR1 	*(__IO uint8_t*)0x5340
#define TIM4_IER 	*(__IO uint8_t*)0x5343
#define TIM4_SR 	*(__IO uint8_t*)0x5344
#define TIM4_EGR 	*(__IO uint8_t*)0x5345
#define TIM4_CNTR 	*(__IO uint8_t*)0x5346
#define TIM4_PSCR 	*(__IO uint8_t*)0x5347
#define TIM4_ARR 	*(__IO uint8_t*)0x5348

void setUpTimer4()
{
    // main clock 16 MHZ
    // prescaler 128
    // timer clock 125KHz
    // Counter 250
    // interrupt at every 2ms

    TIM4_PSCR = 0x07;
    TIM4_ARR = 249;
    TIM4_IER = 0x01;
    TIM4_CR1 = 0x01;
}

unsigned tim4Counter; //will become one after every 400ms
bool flag50ms;

void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    tim4Counter++;

    // Set other timout things here
    if (0 == (tim4Counter % 25))
        flag50ms = 1;


    if(tim4Counter == 200 )
    {
        tim4Counter = 1;
    }

    TIM4_SR = 0x00;
}

//unsigned long long micros()
//{
//    return (millis*1000 + (TIM4_CNTR + 1)*4 );
//}

//void delay( unsigned long inMs )
//{
//    unsigned long long offset = millis + inMs;
//    while( offset >= millis );
//}

///////////////////////////////////////////////////////////////////////////////
////////////////////// UART1 //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define UART1_SR	*(__IO uint8_t*)0x5230
#define UART1_DR	*(__IO uint8_t*)0x5231
#define UART1_BRR1	*(__IO uint8_t*)0x5232
#define UART1_BRR2	*(__IO uint8_t*)0x5233
#define UART1_CR2	*(__IO uint8_t*)0x5235
#define UART1_CR3	*(__IO uint8_t*)0x5236

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

void printInt(int32_t n, unsigned char base)
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
    int32_t ival;

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
            ival = va_arg(ap,int32_t);
            printInt(ival, 10);
            break;
        case 'X':
        case 'x':
            ival = va_arg(ap,int32_t);
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

#define ADC1_CSR    *(__IO uint8_t*)0x5400
#define ADC1_CR1    *(__IO uint8_t*)0x5401
#define ADC1_CR2    *(__IO uint8_t*)0x5402
#define ADC1_CR3    *(__IO uint8_t*)0x5403
#define ADC1_DRH    *(__IO uint8_t*)0x5404
#define ADC1_DRL    *(__IO uint8_t*)0x5405
#define ADC1_TDRH    *(__IO uint8_t*)0x5406
#define ADC1_TDRL   *(__IO uint8_t*)0x5407
#define ADC1_HTRH   *(__IO uint8_t*)0x5408
#define ADC1_HTRL    *(__IO uint8_t*)0x5409
#define ADC1_LTRH   *(__IO uint8_t*)0x540A
#define ADC1_LTRL   *(__IO uint8_t*)0x540B
#define ADC1_AWSRH   *(__IO uint8_t*)0x540C
#define ADC1_AWSRL  *(__IO uint8_t*)0x540D
#define ADC1_AWCRH  *(__IO uint8_t*)0x540E
#define ADC1_AWCRL  *(__IO uint8_t*)0x540F


#define ADC1_CR1_ADON    ((uint8_t)0x01) /*!< A/D Converter on/off mask */
#define ADC1_FLAG_EOC    (uint8_t)0x80  /**< EOC falg */

///////////////////////////////////////////////////////////////////////////////

uint16_t getADCValue(uint8_t channel)
{
    uint16_t value;
    // i ma using reset value for adc1
    // so i can directly set channel value to CST
    ADC1_CSR = channel;        // set channel
    ADC1_CR1 |= ADC1_CR1_ADON; // start conversion

    while(! (ADC1_CSR & ADC1_FLAG_EOC) );
    //    // MSB at High and LSB at LOW
    value = (uint16_t)(ADC1_DRL | (uint16_t)ADC1_DRH << 2);
    ADC1_CSR &= (~ADC1_FLAG_EOC);
    return value;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// SPI ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define SPI_CR1         *(__IO uint8_t*)0x5200
#define SPI_CR2         *(__IO uint8_t*)0x5201
#define SPI_ICR         *(__IO uint8_t*)0x5202
#define SPI_SR         *(__IO uint8_t*)0x5203
#define SPI_DR         *(__IO uint8_t*)0x5204

#define SD_SPI_SCK_PIN                   GPIO_PIN_5                  /* PC.05 */
#define SD_SPI_SCK_GPIO_PORT             GPIOC                       /* GPIOC */
#define SD_SPI_MISO_PIN                  GPIO_PIN_7                  /* PC.05 */
#define SD_SPI_MISO_GPIO_PORT            GPIOC                       /* GPIOC */
#define SD_SPI_MOSI_PIN                  GPIO_PIN_6                  /* PC.06 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOC                       /* GPIOC */
#define SD_CS_PIN                        GPIO_PIN_3                  /* PE.03 */
#define SD_CS_GPIO_PORT                  GPIOA                       /* GPIOA */

#define CS_LOW()     PA_ODR &= (~(0x08))
#define CS_HIGH()    PA_ODR |= 0x08;
///////////////////////////////////////////////////////////////////////////////
void initSPI()
{
    // By default the clock is enabled
    // No change required for mosi, miso, sck

    SPI_CR1 = 0x44;

    // Set CS pin in Output push-pull high level.
    PA_DDR |= 0x08;
    PA_CR1 |= 0x08;
    PA_CR2 |= 0x08;
}

uint8_t spiWriteRead(uint8_t inData)
{
    SPI_DR = inData;
    while(!(SPI_SR & 0x01 ));
    return (SPI_DR);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// NRF24L01P ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define SPI_CMD_RD_REG            0x00
#define SPI_CMD_WR_REG            0x20
#define SPI_CMD_RD_RX_PAYLOAD     0x61
#define SPI_CMD_WR_TX_PAYLOAD     0xa0
#define SPI_CMD_R_RX_PL_WID       0x60
#define SPI_CMD_FLUSH_TX          0xe1
#define SPI_CMD_FLUSH_RX          0xe2

#define SPI_CMD_NOP               0xff
#define TIMING_Tpece2csn_us       4
#define TIMING_Thce_us              10   //  10uS
#define TIMING_Tpd2stby_us        4500   // 4.5mS worst case

// CONFIG register:
#define REG_CONFIG                0x00

#define CONFIG_PRIM_RX        (1<<0)
#define CONFIG_PWR_UP         (1<<1)
#define CONFIG_CRC0           (1<<2)
#define CONFIG_EN_CRC         (1<<3)
#define CONFIG_MASK_MAX_RT    (1<<4)
#define CONFIG_MASK_TX_DS     (1<<5)
#define CONFIG_MASK_RX_DR     (1<<6)

#define REG_EN_AA                 0x01

#define REG_EN_RXADDR             0x02
#define REG_SETUP_RETR            0x04
#define REG_STATUS                0x07
#define REG_RX_PW_P0              0x11

// STATUS register:
#define STATUS_TX_FULL        (1<<0)
#define STATUS_RX_P_NO        (0x7<<1)
#define STATUS_MAX_RT         (1<<4)
#define STATUS_TX_DS          (1<<5)
#define STATUS_RX_DR          (1<<6)

#define TX_FIFO_SIZE   32
#define RX_FIFO_SIZE   32

// EN_AA register:
#define EN_AA_NONE            0

// SETUP_RETR register:
#define SETUP_RETR_NONE       0

///////////////////////////////////////////////////////////////////////////////
///         TODO:
///         Add CE Code
///         INTERRUPT CODE
///////////////////////////////////////////////////////////////////////////////

uint8_t nrfGetRegister(uint8_t inReg)
{
    uint8_t data = 0;
    CS_LOW();
    spiWriteRead(inReg);
    data = spiWriteRead(0xFF);
    CS_HIGH();
    return data;
}

uint8_t mrfGetStatusRegister()
{
    uint8_t status = 0;
    CS_LOW();
    status  = spiWriteRead( SPI_CMD_NOP );
    CS_HIGH();
    return status;
}

void nrfSetRegister( uint8_t inReg, uint8_t inRegData ) {
    CS_LOW();
    spiWriteRead(SPI_CMD_WR_REG | inReg);
    spiWriteRead(inRegData);
    CS_HIGH();
}

// Make sure count is less than or equal to 32
uint8_t nrfWrite(uint8_t *data, uint8_t count)
{
    uint8_t i;

    CS_LOW();
    spiWriteRead(SPI_CMD_WR_TX_PAYLOAD);
    for (i = 0; i < count; i++ )
        spiWriteRead(*data++);
    CS_HIGH();
    return count;
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
    uint8_t value = 0;
    uint8_t index = 0;
    uint32_t adcValue = 0;
    uint32_t temp32i = 0;
//    int32_t count = 0;

    setUpClock();
    setUpSerial();
    // Configure pins
    PB_DDR = 0x20;
    PB_CR1 = 0x20;

    // Timer related stuff
    setUpTimer4();
    enableInterrupts();

    // ADC related stuff
    // Default value is fine input pins
    // Fmster/4, single conversion mode, enable ADC
    ADC1_CR1 = 0x21;

    initSPI();

    printf("Size %d\n", (int32_t)(sizeof(adcValue)));
    // keep default alignment, no scan node, no trigger

    while( 1 )
    {
//        printf("Working?\n");
//        for( index = 0; index < 8; ++index)
//        {
//            nrfSetRegister(index, index);
//            value = nrfGetRegister(index);
//            printf("%d %d\n",index, value);
//        }
//        delay( 1000 );

        // ADC low pass filter
//        count++;
        temp32i = getADCValue(4);
        adcValue = (adcValue*9 + (temp32i << 10) )/ 10;
//        printf("%d %d\n",(int32_t)(adcValue >> 10), temp32i);

        if( flag50ms )
        {
            printf("%d %d\n",(int32_t)(adcValue >> 10), (int32_t)getADCValue(4));
//            count = 0;
            flag50ms = 0;
        }
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
