#include "common.h"

#include "adc.h"
#include "serial.h"
#include "print.h"
#include "timer4.h"
#include "spi.h"
#include "nrf24.h"
#include "pwm.h"
#include "led.h"
#include "utility.h"
#include "fhss.h"

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

/**********************************************************************************************************/
/********************************** DATA RECEIVED INTERRUPT************************************************/
/**********************************************************************************************************/
volatile uint8_t dataReceived;
/**********************************************************************************************************/
/********************************** TIMER 4 , CLOCK , LED BLINK********************************************/
/**********************************************************************************************************/

volatile uint8_t ledToggleFlag;
volatile uint8_t  tim4Counter;
volatile uint8_t ledBlinkSpeed = 250;
/**********************************************************************************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/

int main()
{
    uint8_t blinkLED = 1;
    uint8_t bindingAddress = 0;
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
    nrfSetFixedDataSize(sizeof(data_packet));
    nrfFlushRxFifo();

    bindingAddress = readEEPROMAddress();
    printf("EEPROM ADDRESS %d\n", (int32_t)bindingAddress);
    if (bindingAddress) {
        nrfSetBindingAddress(bindingAddress);
    } else {
        // Blink faster for binding
        ledBlinkSpeed = 50;
    }

    nrfSetReceiveMode();
    while( 1 )
    {
        if (dataReceived) {
            dataReceived = 0;
            nrfReadData((uint8_t*)data_packet, sizeof(data_packet));
            if (bindingAddress) {
                // CONSUME DATA
                printf("%s\n", (const char*)data_packet);
            } else {
                bindingAddress = data_packet.switches;
                printf("WRITE BIND ADDRESS %d\n", (int32_t)bindingAddress);
                nrfSetBindingAddress(bindingAddress);
                writeEEPROMAddress(bindingAddress);
                ledBlinkSpeed = 250;
            }

        }
        if( blinkLED && ledToggleFlag )
        {
            ledToggleFlag = 0;
            toggleLED();
        }
    }
}


/**********************************************************************************************************/
/********************************** DATA RECEIVED INTERRUPT************************************************/
/**********************************************************************************************************/
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
/**********************************************************************************************************/
/********************************** TIMER 4 , CLOCK , LED BLINK********************************************/
/**********************************************************************************************************/

//volatile unsigned long millis;
void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    tim4Counter++;
    //    millis++;

    // Set other timout things here
    //    if (0 == (tim4Counter % 25))
    //        flag50ms = 1;


    if(tim4Counter == ledBlinkSpeed )
    {
        tim4Counter = 0;
        ledToggleFlag = 1;
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
/**********************************************************************************************************/
/**********************************************************************************************************/

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
