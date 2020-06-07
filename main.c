#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define SLAVE_ADDRESS 0x3C

void I2C0_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE,GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3);
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(),false);
}

void I2C0_Send(uint16_t lcd_addr, uint8_t lcd_data)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, lcd_addr, false);
    I2CMasterDataPut(I2C0_BASE, lcd_data);
    I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_SEND);
   // while(!I2CMasterBusy());
}

int main()
{
    uint32_t ui32DataTx;
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    I2C0_Init();
   // IntMasterEnable();

    while(1)
    {
        ui32DataTx = 250499;
        I2C0_Send(SLAVE_ADDRESS,ui32DataTx);
    }
}
