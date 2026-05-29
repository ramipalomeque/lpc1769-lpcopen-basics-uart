/*
 * 		  File: /Ejercitacion_UART/inc/Primitives/PR_UART.h
 *  Created on: 13 may. 2026
 *      Author: Ramiro
 */

#ifndef PRIMITIVES_PR_UART_H_
#define PRIMITIVES_PR_UART_H_

/* ============================================================================
 * INCLUDES
 * ============================================================================
 */
#include "board.h"


/* ============================================================================
 * DEFINES
 * ============================================================================
 */
#define 	TXBUFFER_SIZE	128
#define 	RXBUFFER_SIZE	128

#define		UART_NO_DATA	0xff


/* ============================================================================
 * MACROS
 * ============================================================================
*/



/* ============================================================================
 * TYPE DEFINITIONS
 * ============================================================================
 */



/* ============================================================================
 * EXTERN VARIABLES
 * ============================================================================
 */
extern volatile uint8_t BufferUART0_TX[TXBUFFER_SIZE];
extern volatile uint8_t BufferUART0_RX[RXBUFFER_SIZE];
extern volatile uint8_t IndiceTxIn,IndiceTxOut;
extern volatile uint8_t IndiceRxIn,IndiceRxOut;
extern volatile uint8_t StartUART0_TX;



/* ============================================================================
 * FUNCTION PROTOTYPES
 * ============================================================================
*/
void PushTx( uint8_t dato);
uint8_t PopTx( void );

void PushRx( uint8_t dato);
uint8_t PopRx( void );

int8_t EnviarString (const char *str,uint32_t len);
int8_t RecibirString(char *buffer, uint32_t len);


/* ============================================================================
 * INLINE FUNCTIONS
 * ============================================================================
*/


#endif /* PRIMITIVES_PR_UART_H_ */
