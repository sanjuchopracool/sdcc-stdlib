#include "nrf24.h"
#include "common.h"
#include "spi.h"

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
#define REG_RX_PW_P0              0x11
#define REG_SETUP_AW              0x03
#define REG_RF_CH                 0x05
#define REG_RF_SETUP              0x06
#define REG_FIFO_STATUS           0x17

#define RF_250KBPS                  (1<<5)
#define RF_MAX_POWER                (3<<1)

#define TX_FIFO_SIZE   32
#define RX_FIFO_SIZE   32

// EN_AA register:
#define EN_AA_NONE            0

// SETUP_RETR register:
#define SETUP_RETR_NONE       0


#define CS_LOW()     PA_ODR &= (~(0x08))
#define CS_HIGH()    PA_ODR |= 0x08;

#define CE_LOW()     PA_ODR &= (~(0x04))
#define CE_HIGH()    PA_ODR |= 0x04;

// raise CE to enable the RF transmission PA2
#define NRF24L01P_RaiseCE() PA_ODR |= 0x04
// drop CE to disable RF Transmission
#define NRF24L01P_DropCE()  PA_ODR &= 0xFB

#define REG_RX_ADDR_P0      0x0A
#define REG_TX_ADDR         0x10
uint8_t DEFAULT_ADDRESS[5] =  {0xA8, 0xD7, 0xF9, 0xEF, 0x00};
///////////////////////////////////////////////////////////////////////////////
///         TODO:
///         Add CE Code
///         INTERRUPT CODE
///////////////////////////////////////////////////////////////////////////////

void initNrf()
{
    initSPI();

    // PA1(interrupt),PA2(CE),PA3(CSN)
    PA_DDR |= 0x08;
    PA_CR1 |= 0x08;
    PA_CR2 |= 0x08;

    //PA2
    // CE
    PA_DDR |= 0x04; // Direction
    PA_CR1 |= 0x04; // Push pull (Required)
    PA_CR2 |= 0x04; // Fast (10MHz)

    // INTERRUPT
    //PA1
//        PA_DDR &= (uint8_t)(~(0x02)); //Already reset
//        PA_CR1 &= (uint8_t)(~(0x02)); //Already reset
    PA_CR2 |= 0x02;
    EXTI_CR1 |= 0x02;
    EXTI_CR2 = 0x00;

    // Set settings
    // clear all pending interrupts
    nrfSetRegister(REG_STATUS,
                STATUS_MAX_RT|
                STATUS_TX_DS|
                STATUS_RX_DR);   // Clear any pending interrupts

    // set 250KBPS DATA RATE
    // MAX POWER
    nrfSetRegister(REG_RF_SETUP,
                   RF_250KBPS|RF_MAX_POWER);

    // BOTH REQUIRED FOR AUTO ACKNOWLEDGEMENT
    nrfSetRxAddress(0);
#ifdef RECEIVER
    nrfSetRegister(REG_CONFIG,
                CONFIG_EN_CRC |
                CONFIG_MASK_TX_DS | CONFIG_MASK_MAX_RT |
                CONFIG_PWR_UP);
#else
    nrfSetRegister(REG_CONFIG,
                CONFIG_EN_CRC |
                CONFIG_MASK_RX_DR |
                CONFIG_PWR_UP);
    nrfSetTxAddress(0);
#endif



    // set transfer size
    // of 32 bytes, it can be between 1-32
    // it is not required at TX Side
    // It is only required at RX Side
    //nrfSetRegister(REG_RX_PW_P0, 32);


    // enable transmission
    NRF24L01P_RaiseCE();
}

uint8_t nrfGetRegister(uint8_t inReg)
{
    uint8_t data = 0;
    CS_LOW();
    spiWriteRead(inReg);
    data = spiWriteRead(0xFF);
    CS_HIGH();
    return data;
}

uint8_t nrfGetStatusRegister()
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

void nrfFlushTxFifo()
{
    CS_LOW();
    spiWriteRead(SPI_CMD_FLUSH_TX);
    spiWriteRead(SPI_CMD_NOP);
    CS_HIGH();
}

// Make sure count is less than or equal to 32
uint8_t nrfWrite(uint8_t *data, uint8_t count)
{
    uint8_t i;

    CS_LOW();
    spiWriteRead(SPI_CMD_WR_TX_PAYLOAD);
    for (i = 0; i < count; ++i )
        spiWriteRead(*data++);
    CS_HIGH();

    CE_HIGH();
    while (!(nrfGetStatusRegister() | (STATUS_TX_DS | STATUS_MAX_RT)));
    CE_LOW();
    return count;
}

uint8_t nrfIsConnected()
{
      uint8_t setup = nrfGetRegister(REG_SETUP_AW);
      return (setup >= 1 && setup <= 3);
}

void nrfSetPALevel(NRF_POWER_LEVEL level)
{
    uint8_t setup = nrfGetRegister(REG_RF_SETUP) & 0xF8;
    if(level > 3){  						// If invalid level, go to max PA
        level = (RF24_PA_MAX << 1) + 1;		// +1 to support the SI24R1 chip extra bit
    }else{
        level = (level << 1) + 1;	 		// Else set level as requested
    }
    nrfSetRegister(REG_RF_SETUP, setup |= level);	// Write it to the chip
}

void nrfSetReceiveMode()
{
    uint8_t theConfig = nrfGetRegister(REG_CONFIG);
    theConfig |= CONFIG_PRIM_RX;
    nrfSetRegister(REG_CONFIG, theConfig);
    // Enable AutoAcknowledgement for pipe 0
    nrfSetRegister(REG_EN_AA, 0x01);
    // enable only first rx pipe
    // we want only one to one communication
    nrfSetRegister( REG_EN_RXADDR, 0x01 );
}

void nrfSetTransmitMode()
{
    uint8_t theConfig = nrfGetRegister(REG_CONFIG);
    theConfig &= ~CONFIG_PRIM_RX;
    nrfSetRegister(REG_CONFIG, theConfig);
    // Enable AutoAcknowledgement for pipe 0
    nrfSetRegister( REG_EN_RXADDR, 0x01 );
    nrfSetRegister(REG_SETUP_RETR, 0xFF);
}

void nrfSetFixedDataSize(uint8_t dataSize)
{
    if (dataSize > 32) dataSize = 32;
    nrfSetRegister(REG_RX_PW_P0, dataSize);
}

int8_t nrfReadData( uint8_t *data, uint8_t count)
{
    CS_LOW();
    spiWriteRead(SPI_CMD_R_RX_PL_WID);
    uint8_t rxPayloadWidth = spiWriteRead(SPI_CMD_NOP);
    CS_HIGH();

    if ( rxPayloadWidth > RX_FIFO_SIZE )
    {
        nrfFlushRxFifo();
    }
    else
    {
        if ( rxPayloadWidth < count ) count = rxPayloadWidth;
        CS_LOW();
        spiWriteRead(SPI_CMD_RD_RX_PAYLOAD);
        for ( int i = 0; i < count; ++i )
        {
            *data++ = spiWriteRead(SPI_CMD_NOP);
        }
        CS_HIGH();
        return count;
    }
    return -1;
}

void nrfFlushRxFifo()
{
    CS_LOW();
    spiWriteRead(SPI_CMD_FLUSH_RX);
    spiWriteRead(SPI_CMD_NOP);
    CS_HIGH();
}

void nrfSetRxAddress(uint8_t address)
{
    DEFAULT_ADDRESS[4] = address;
    CS_LOW();
    spiWriteRead(SPI_CMD_WR_REG | REG_RX_ADDR_P0);
    for (uint8_t i = 0; i < 5; ++i )
        spiWriteRead(DEFAULT_ADDRESS[i]);
    CS_HIGH();
}

void nrfSetTxAddress(uint8_t address)
{
    DEFAULT_ADDRESS[4] = address;
    CS_LOW();
    spiWriteRead(SPI_CMD_WR_REG | REG_TX_ADDR);
    for (uint8_t i = 0; i < 5; ++i )
        spiWriteRead(DEFAULT_ADDRESS[i]);
    CS_HIGH();
}


void nrfSetBindingAddress(uint8_t address)
{
    nrfSetTxAddress(address);
    nrfSetRxAddress(address);
    // disable acknowledgement
//    nrfSetRegister(REG_EN_AA, 0x00);
    // retry only 1 time
    nrfSetRegister(REG_SETUP_RETR, 0x00);
//    // mask all interrupts
//    nrfSetRegister(REG_CONFIG,
//                CONFIG_EN_CRC |
//                CONFIG_MASK_TX_DS | CONFIG_MASK_MAX_RT | CONFIG_MASK_RX_DR |
//                CONFIG_PWR_UP);
//    nrfSetRegister(REG_STATUS,
//                STATUS_MAX_RT|
//                STATUS_TX_DS|
//                STATUS_RX_DR);   // Clear any pending interrupts
}

void nrfSetFrequency(int8_t freq)
{
    nrfSetRegister(REG_RF_CH, freq);
}

uint8_t nrfIsDataReady()
{
    return !(nrfGetRegister(REG_FIFO_STATUS) & 0x01);
}
