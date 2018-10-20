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


#define TX_FIFO_SIZE   32
#define RX_FIFO_SIZE   32

// EN_AA register:
#define EN_AA_NONE            0

// SETUP_RETR register:
#define SETUP_RETR_NONE       0


#define CS_LOW()     PA_ODR &= (~(0x08))
#define CS_HIGH()    PA_ODR |= 0x08;

// raise CE to enable the RF transmission PA2
#define NRF24L01P_RaiseCE() PA_ODR |= 0x04
// drop CE to disable RF Transmission
#define NRF24L01P_DropCE()  PA_ODR &= 0xFB

///////////////////////////////////////////////////////////////////////////////
///         TODO:
///         Add CE Code
///         INTERRUPT CODE
///////////////////////////////////////////////////////////////////////////////

void initNrf()
{
    initSPI();

    // Set CS pin in Output push-pull high level.
    // PA3
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


    nrfSetRegister(REG_CONFIG,
                CONFIG_EN_CRC |
                CONFIG_MASK_RX_DR |
                CONFIG_PWR_UP);

    // Enable AutoAcknowledgement for pipe 0
    nrfSetRegister(REG_EN_AA, 0x01);

    // enable only first rx pipe
    // we want only one to one communication
    nrfSetRegister( REG_EN_RXADDR, 0x01 );

    // set transfer size
    // of 32 bytes, it can be between 1-32
    // it is not required at TX Side
    // It is only required at RX Side
    //        setRegister(REG_RX_PW_P0, TRANSFER_SIZE );

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
    for (i = 0; i < count; i++ )
        spiWriteRead(*data++);
    CS_HIGH();
    return count;
}
