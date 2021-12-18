#include "common.h"

#include "adc.h"
#include "serial.h"
#include "print.h"
#include "timer4.h"
#include "spi.h"
#include "nrf24.h"
#include "pwm.h"
#include "led.h"

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


volatile uint8_t tim4Counter;
volatile uint8_t flagHalfSecond;
volatile uint8_t dataReceived;

//volatile unsigned long millis;
void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    tim4Counter++;
    //    millis++;

    // Set other timout things here
    //    if (0 == (tim4Counter % 25))
    //        flag50ms = 1;


    if(tim4Counter == 250 )
    {
        tim4Counter = 0;
        flagHalfSecond = 1;
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
uint8_t data[TRANSFER_SIZE] = "";

///////////////////////////////////////////////////////////////////////////////
int main()
{
    setUpClock();
    setUpSerial();
    initLED();
    // timer 4 provides 2 ms interrupt, no way to increase delay, with 16MHz
    setUpTimer4();
    initNrf();
    printf("RX ");
    if (!nrfIsConnected()) {
        printf("NOT ");
    }
    printf("CONNECTED\n");
    enableInterrupts();
    nrfSetFixedDataSize(TRANSFER_SIZE);
    nrfFlushRxFifo();
    nrfSetReceiveMode();
    while( 1 )
    {
        if (dataReceived) {
            dataReceived = 0;
            nrfReadData(data, TRANSFER_SIZE);
            printf("%s\n", data);

        }
        if( flagHalfSecond )
        {
            flagHalfSecond = 0;
            toggleLED();
        }
    }
}

void ExtiPortCIRQHandler(void) __interrupt(3)
{
    // if PA1
    if ( 0 == (PA_IDR & 0x02)) // Active low
    {
        uint8_t status = nrfGetStatusRegister();
        if ( status & STATUS_RX_DR)
        {
            nrfSetRegister(REG_STATUS, STATUS_RX_DR);
            dataReceived = 1;
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
