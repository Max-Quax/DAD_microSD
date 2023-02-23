/*
 * DAD_microSD.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Max
 */

#ifndef HAL_DAD_MICROSD_H_
#define HAL_DAD_MICROSD_H_

#include <HAL/DAD_UART.h>
#include <string.h>

#define MICRO_SD_BAUD_RATE 9600
#define MICRO_SD_MODULE_INSTANCE EUSCI_A2_BASE  // Module instance - module A0 for debug

// Configures and Initializes UART
    // Parameter - structure for using the UART HAL
void DAD_microSD_InitUART(DAD_UART_Struct* uartStruct);

// Opens file
    // Step into cmd mode, append to file
    // If filename does not exist, file is created
    // Parameter - array of chars for file name. 8.3 format
    // Parameter - structure for using the UART HAL
bool DAD_microSD_openFile(char* fileName, DAD_UART_Struct* uartStruct);

// Write to file
    // TODO write
    // Parameter - array of chars for file name. 8.3 format
    // Parameter - array of strs for message. writes as CSV
    // Parameter - structure for using the UART HALs
bool DAD_microSD_Write_CSV(char* fileName, char** message, uint16_t messageLen, DAD_UART_Struct* uartStruct);

#endif /* HAL_DAD_MICROSD_H_ */
