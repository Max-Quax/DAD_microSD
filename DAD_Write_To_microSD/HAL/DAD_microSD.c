/*
 * DAD_microSD.c
 *
 *  Created on: Feb 19, 2023
 *      Author: Max
 */

#include <HAL/DAD_microSD.h>

void DAD_microSD_InitUART(DAD_UART_Struct* uartStruct){
    DAD_UART_Set_Config(MICRO_SD_BAUD_RATE, MICRO_SD_MODULE_INSTANCE, uartStruct);  // Config UART
    DAD_UART_Init(uartStruct, 512); // Init UART with 512-byte buffer
}

bool DAD_microSD_openFile(char* fileName, DAD_UART_Struct* uartStruct){
    MAP_UART_disableInterrupt(uartStruct->moduleInst, EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Check name size
    if(strlen(fileName) > 12)
        return false;

    // Open openLog microSD controller in cmd mode
    char cmdMode[4] = "&&&";
    DAD_UART_Write_Str(uartStruct, cmdMode);
    DAD_UART_Write_Char(uartStruct, 13);        // Carriage return


    // TODO check that cmd mode was entered

    // Append to file
    char command[20] = "append ";
    strcat(command, fileName);                  // concat fileName into command
    DAD_UART_Write_Str(uartStruct, command);    // Call command to begin writing to fileName
    DAD_UART_Write_Char(uartStruct, 13);        // Carriage return

    //MAP_UART_enableInterrupt(uartStruct->moduleInst, EUSCI_A_UART_RECEIVE_INTERRUPT);

    return true;
}

bool DAD_microSD_Write_CSV(char* fileName, char** message, uint16_t messageLen, DAD_UART_Struct* uartStruct){
    // Check that file was opened
    if(DAD_microSD_openFile(fileName, uartStruct)){
        // Write message
        uint16_t i;
        for(i = 0; i < messageLen; i++){
            DAD_UART_Write_Str(uartStruct, message[i]);
            DAD_UART_Write_Char(uartStruct, ',');           // Separate with commas
        }
        DAD_UART_Write_Char(uartStruct, 13);                // Carriage return
        return true;
    }

    return false;
}

