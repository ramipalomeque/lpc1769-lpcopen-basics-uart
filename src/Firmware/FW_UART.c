/*
 * 		  File: /Ejercitacion_UART/src/Firmware/FW_UART.c
 *  Created on: 13 may. 2026
 *      Author: Ramiro
 */

/* ============================================================================
 * PUBLIC HEADER INCLUDES
 * ============================================================================
 */
#include "board.h"
#include "Primitives/PR_UART.h"
 

/* ============================================================================
 * PRIVATE HEADER INCLUDES
 * ============================================================================
 */
#include "Firmware/FW_UART.h"


/* ============================================================================
 * LOCAL DEFINES
 * ============================================================================
 */



/* ============================================================================
 * LOCAL MACROS
 * ============================================================================
 */



/* ============================================================================
 * GLOBAL VARIABLES
 * ============================================================================
 */



/* ============================================================================
 * STATIC VARIABLES (FILE-SCOPE)
 * ============================================================================
 */



/* ============================================================================
 * FUNCTION DEFINITIONS
 * ============================================================================
 */
void FW_InitUART0( void )
{
	Chip_IOCON_PinMux(LPC_IOCON, UART0_TX, IOCON_MODE_INACT, IOCON_FUNC1);
	Chip_IOCON_PinMux(LPC_IOCON, UART0_RX, IOCON_MODE_INACT, IOCON_FUNC1);


	Chip_UART_Init(LPC_UART0);
	Chip_UART_SetBaud(LPC_UART0, UART_BAUDRATE);
	Chip_UART_ConfigData(LPC_UART0, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS));


	Chip_UART_TXEnable(LPC_UART0);

    Chip_UART_IntEnable(LPC_UART0, (UART_IER_RBRINT |  UART_IER_THREINT));
    NVIC_EnableIRQ(UART0_IRQn);

	return;
}

void UART0_IRQHandler(void)
{
    uint32_t iir;
    uint8_t IntPendiente,IntEnCurso;
    uint8_t dato;

    do
    {
        iir = Chip_UART_ReadIntIDReg(LPC_UART0);

		IntPendiente = iir & 0x01;
		IntEnCurso = ( iir >> 1 ) & 0x07;

        switch (IntEnCurso)
        {
            case UART_RX_IRQ:

                dato = Chip_UART_ReadByte(LPC_UART0);
                PushRx(dato);
                break;

            case UART_TX_IRQ:

            	dato = PopTx();
                if (dato != UART_NO_DATA)
                	Chip_UART_SendByte(LPC_UART0, (uint8_t)dato);
                else
                	StartUART0_TX = 0;

                break;
         }
    } while(! ( IntPendiente & 0x01 ) );
}
