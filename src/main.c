/*
===============================================================================
 Name        : Ejercitacion_UART.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "string.h"
#include "Firmware/FW_UART.h"

#include "Primitives/PR_UART.h"
// TODO: insert other definitions and declarations here
#define UART_SELECTION LPC_UART0
#define UART_BAUDRATE 9600

int main(void)
{
    char msg2 [100];
    char buffer[RXBUFFER_SIZE];

    SystemCoreClockUpdate();
    Board_Init();
    FW_InitUART0();

    Board_LED_Set(0,true);

    sprintf(msg2,"Hola UART\n");
    EnviarString(msg2, strlen(msg2));
    sprintf(msg2,"Opciones:\n\t-Apagar\n\t-Encender\n\t-Toggle\n");
    EnviarString(msg2, strlen(msg2));


    while (1)
    {

    	if(RecibirString(buffer,RXBUFFER_SIZE)==0)
    	{
    		sprintf(msg2,"Recibi; %s\n",buffer);
    		//printf("%s\n",msg2);
    		EnviarString(msg2, strlen(msg2));

    		if(buffer[0]=='T' || buffer[0]=='t')
    			Board_LED_Toggle(0);
    		if(buffer[0]=='A' || buffer[0]=='a')
    		    Board_LED_Set(0,true);
    		if(buffer[0]=='E' || buffer[0]=='e')
    			Board_LED_Set(0,false);
    	}
	}

}
