#include "stm8l15x_spi.h"

#include "dev/spi.h"

#define SPI_INTERFACE                               SPI2
#define SPI_CLK                                     CLK_Peripheral_SPI2

#define SPI_PIN_SCK_PORT                            GPIOD
#define SPI_PIN_SCK                                 GPIO_Pin_6

#define SPI_PIN_MISO_PORT                           GPIOD
#define SPI_PIN_MISO                                GPIO_Pin_4

#define SPI_PIN_MOSI_PORT                           GPIOD
#define SPI_PIN_MOSI                                GPIO_Pin_5


void spi_init( void )
{
    /* Enable SPI clock */
    CLK_PeripheralClockConfig(SPI_CLK, ENABLE);

    /* Set the MOSI,MISO and SCK at high level */
    GPIO_ExternalPullUpConfig(SPI_PIN_SCK_PORT, SPI_PIN_SCK | SPI_PIN_MISO | \
                              SPI_PIN_MOSI, ENABLE);

    SPI_DeInit(SPI_INTERFACE);

    /* SPI_INTERFACE Config */
    SPI_Init(SPI_INTERFACE, SPI_FirstBit_MSB, SPI_BaudRatePrescaler_8, SPI_Mode_Master,
             SPI_CPOL_Low, SPI_CPHA_1Edge, SPI_Direction_2Lines_FullDuplex,
             SPI_NSS_Soft, (uint8_t)0x07);

    /* SPI_INTERFACE enable */
    SPI_Cmd(SPI_INTERFACE, ENABLE);   
}

uint8_t spi_in_out( uint8_t out_data )
{
    /* Send SPIy data */
    SPI_SendData( SPI_INTERFACE, out_data );
    while( SPI_GetFlagStatus( SPI_INTERFACE, SPI_FLAG_RXNE ) == RESET );
    return SPI_ReceiveData( SPI_INTERFACE );
}