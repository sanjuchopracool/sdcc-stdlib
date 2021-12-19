#include "common.h"

#include "adc.h"
#include "serial.h"
#include "print.h"
#include "timer4.h"
#include "spi.h"
#include "nrf24.h"
#include "pwm.h"
#include "led.h"
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
/********************************** DATA TRANSMIT INTERRUPT************************************************/
/**********************************************************************************************************/
volatile uint8_t packetSent = 0;
void ExtiPortCIRQHandler(void) __interrupt(3)
{
    // if PA1
    if ( 0 == (PA_IDR & 0x02)) // Active low
    {
        putchar('I');
        uint8_t status = nrfGetStatusRegister();
        if ( status & STATUS_TX_DS)
        {
            nrfSetRegister(REG_STATUS, STATUS_TX_DS);
            packetSent = 1;
            putchar('T');
        }
        else if ( status & STATUS_MAX_RT)
        {
            nrfSetRegister(REG_STATUS, STATUS_MAX_RT);
            nrfFlushTxFifo();
            putchar('R');
        }
        putchar('\n');
    }
}

/**********************************************************************************************************/
/********************************** TIMER 4 , CLOCK , LED BLINK********************************************/
/**********************************************************************************************************/

volatile uint8_t fired = 0;

//volatile unsigned long millis;
void Timer4UpdateIRQHandler(void) __interrupt(23)
{
    fired = 1;
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
/**********************************************************************************************************/

#define TRANSFER_SIZE 9
uint8_t data[TRANSFER_SIZE] = "Hello";

int main()
{
    uint8_t blinkLED = 1;
    uint8_t bindingAddress = 0xFF;
    uint8_t newBindingAddress = 0xFF;
    setUpClock();
    setUpSerial();
    initLED();
    // timer 4 provides 2 ms interrupt, no way to increase delay, with 16MHz
    setUpTimer4();
    initNrf();
    printf("TX ");
    if (!nrfIsConnected()) {
        printf("NOT ");
    }
    printf("CONNECTED\n");
    nrfFlushTxFifo();
    if (bindingAddress) {
        printf("SETTIING BIND ADDRESS %d\n", (int32_t)bindingAddress);
        nrfSetBindingAddress(bindingAddress);
        nrfSetFrequency(fhssFreq[0]);
        blinkLED = 0;
        onLED();
    }

    nrfSetTransmitMode();
    enableInterrupts();

    uint8_t firedCount = 0;
    uint8_t blinkCounter = 0;
    uint8_t fhssFreqSize = sizeof(fhssFreq);
    uint8_t currentFhssFreq = 0;
    printf("FHSS_FREQ_SIZE %d\n", (int32_t)fhssFreqSize);
    uint8_t fhssOn = 1;
    while( 1 )
    {
        // fired at every 2ms
        if (fired) {
            fired = 0;
            firedCount++;
//            blinkCounter++;
            if(firedCount == freqChangeSpeed)
            {
                if(bindingAddress && fhssOn) {
                    //printf("%d\n", (int32_t)currentFhssFreq);
    //                putchar('N');
    //                putchar('\n');
                    ++currentFhssFreq;
                    if (currentFhssFreq >= fhssFreqSize)
                        currentFhssFreq = 0;
                    nrfSetFrequency(fhssFreq[currentFhssFreq]);
                } // else {
    //                putchar('S');
    //                putchar('F');
    //                putchar('\n');
    //            }
            }
            else if (firedCount == fhssTransmitSpeed)
            {
                if (bindingAddress) {
                    // send normal data
                    putchar('T');
                    putchar('\n');
                    nrfWrite(data, TRANSFER_SIZE);
                } else {
                    if (packetSent) {
                        packetSent = 0;
                        bindingAddress = newBindingAddress;
                        printf("SETTIING BIND ADDRESS %d\n", (int32_t)bindingAddress);
                        nrfSetBindingAddress(bindingAddress);
                        // TODO save in eeprom
                        blinkLED = 0;
                        onLED();
                    } else {
                        // keep sending binding address
                        data_packet.switches = newBindingAddress;
                        printf("BINDING %d\n", (int32_t)newBindingAddress);
                        nrfWrite((uint8_t*)data_packet, sizeof(data_packet));
                    }
                }
                firedCount = 0;
            }
        }

//        if (blinkLED && (blinkCounter == 50))
//        {
//            toggleLED();
//            blinkCounter = 0;
//        }
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
