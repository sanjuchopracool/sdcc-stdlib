#include "spi.h"
#include "common.h"

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
