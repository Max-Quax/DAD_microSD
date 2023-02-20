/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// HAL includes
#include <HAL/DAD_microSD.h>
#include <HAL/DAD_UART.h>
#include <HAL/DAD_Timer.h>

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

    //
    //Timed Test
    //
    // Timer setup
    double timeElapsed;
    Timer_A_UpModeConfig timerCfg;
    DAD_Timer_Initialize_ms(60000, TIMER_A1_BASE, &timerCfg);

    // Generate test string
    int i;
    char msg[2049] = "t";
    for(i = 0; i < 2048; i++)
    strcat(msg, "t");

    // Send test string over UART
    DAD_Timer_Start(TIMER_A1_BASE);                         // Begin test timer
    DAD_UART_Write_Str(&microSD_UART, msg);
    timeElapsed = DAD_Timer_Stop(TIMER_A1_BASE, &timerCfg); // End test timer

    while(1); // Trap CPU
}
