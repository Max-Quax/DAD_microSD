/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// HAL includes
#include <HAL/DAD_microSD.h>
#include <HAL/DAD_UART.h>

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // Init microSD communication
    DAD_UART_Struct microSD_UART;
    DAD_microSD_InitUART(&microSD_UART);

    // Open file, write test message
    char fileName[] = "test.csv";
    char *message[] = {"one", "two", "three", "four"};
    DAD_microSD_write(fileName, message, 4, &microSD_UART);


    while(1); // Trap CPU
}
