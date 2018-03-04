#include "common.h"

#include "adc.h"
#include "serial.h"
#include "print.h"
#include "timer4.h"
#include "spi.h"
#include "nrf24.h"

///
/// \brief setUpClock sets clock to internal
/// HSI 16MHz clock
///

void setUpClock()
{
    CLK_DIVR = 0x00;  // disable presacler
    CLK_SWCR |= 0x02; // enable clock switching
    CLK_SWR =  0xE1;  // HSI as new clock
    while( ( CLK_SWCR & 0x01 ) != 0 );
}


// interrupt at every 2ms
volatile unsigned tim4Counter; //will become one after every 400ms
volatile bool flag50ms;

//volatile unsigned long millis;
void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    tim4Counter++;
//    millis++;

    // Set other timout things here
//    if (0 == (tim4Counter % 25))
//        flag50ms = 1;


    if(tim4Counter == 200 )
    {
        tim4Counter = 1;
        flag50ms = 1;
    }

    TIM4_SR = 0x00;
}

//unsigned long long micros()
//{
//    return (millis*1000 + (TIM4_CNTR + 1)*4 );
//}

//void delay( unsigned long inMs )
//{
//    unsigned long offset = millis + inMs;
//    while( offset >= millis );
//}

// MACROS
#define TRANSFER_SIZE 32
///////////////////////////////////////////////////////////////////////////////
uint8_t data[TRANSFER_SIZE] = "Hello !! How are you man?";

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
    initADC();

    // Configure pins
    PB_DDR = 0x20;
    PB_CR1 = 0x20;

//    // Timer related stuff
    setUpTimer4();

    initNrf();

    // keep default alignment, no scan node, no trigger


    printf("Welcome\n");

    enableInterrupts();
    while( 1 )
    {
//        delay(2500);
//        togglePC3();


//        // ADC low pass filter
////        count++;
//        temp32i = getADCValue(4);
//        adcValue = (adcValue*9 + (temp32i << 10) )/ 10;
////        printf("%d %d\n",(int32_t)(adcValue >> 10), temp32i);

        if( flag50ms )
        {
            nrfWrite(data, TRANSFER_SIZE);
            flag50ms = 0;
        }
    }
}

void ExtiPortCIRQHandler(void) __interrupt(5)
{
    // if PC4
    if ( 0 == (PC_IDR & 0x10)) // Active low
    {
        uint8_t status = nrfGetStatusRegister();
        if ( status & STATUS_TX_DS)
        {
            nrfSetRegister(REG_STATUS, STATUS_TX_DS);
            putchar('I');
            putchar('T');
        }
        else if ( status & STATUS_MAX_RT)
        {
            nrfSetRegister(REG_STATUS, STATUS_MAX_RT);
            nrfFlushTxFifo();
            putchar('I');
            putchar('R');
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
