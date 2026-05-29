/*
 * 		  File: /Ejercitacion_UART/src/Primitives/PR_UART.c
 *  Created on: 13 may. 2026
 *      Author: Ramiro
 */

/* ============================================================================
 * PUBLIC HEADER INCLUDES
 * ============================================================================
 */

 

/* ============================================================================
 * PRIVATE HEADER INCLUDES
 * ============================================================================
 */
#include "Primitives/PR_UART.h"


/* ============================================================================
 * LOCAL DEFINES
 * ============================================================================
 */
#define 	START_UART0_TX  Chip_UART_SendByte(LPC_UART0, (uint8_t)PopTx())

/* ============================================================================
 * LOCAL MACROS
 * ============================================================================
 */



/* ============================================================================
 * GLOBAL VARIABLES
 * ============================================================================
 */

volatile uint8_t BufferUART0_TX[TXBUFFER_SIZE];
volatile uint8_t BufferUART0_RX[RXBUFFER_SIZE];
volatile uint8_t IndiceTxIn,IndiceTxOut;
volatile uint8_t IndiceRxIn,IndiceRxOut;
volatile uint8_t StartUART0_TX;


/* ============================================================================
 * STATIC VARIABLES (FILE-SCOPE)
 * ============================================================================
 */



/* ============================================================================
 * FUNCTION DEFINITIONS
 * ============================================================================
 */

/**
 * |@fn void PushTx(uint8_t)
 * @brief
 *
 * @param dato
 */
void PushTx( uint8_t dato)
{
	BufferUART0_TX[IndiceTxIn] = dato;

	IndiceTxIn ++;
	IndiceTxIn %= TXBUFFER_SIZE;

	if ( StartUART0_TX == 0 )
	{
		StartUART0_TX = 1;
		START_UART0_TX;
	}
}

/**
 * @fn uint8_t PopTx(void)
 * @brief
 *
 * @return
 */
uint8_t PopTx( void )
{
	uint8_t dato = UART_NO_DATA;

	if ( IndiceTxIn != IndiceTxOut )
	{
		dato = ( uint8_t ) BufferUART0_TX[IndiceTxOut];
		IndiceTxOut ++;
		IndiceTxOut %= TXBUFFER_SIZE;
	}
	return dato;
}

/**
 * @fn void PushRx(uint8_t)
 * @brief
 *
 * @param dato
 */
void PushRx( uint8_t dato )
{
	BufferUART0_RX[IndiceRxIn] = dato;
	IndiceRxIn ++;
	IndiceRxIn %= RXBUFFER_SIZE;
}

uint8_t PopRx( void )
{

	uint8_t dato = UART_NO_DATA;

	if ( IndiceRxIn != IndiceRxOut )
	{
		dato = (uint8_t) BufferUART0_RX[IndiceRxOut];
		IndiceRxOut ++;
		IndiceRxOut %= RXBUFFER_SIZE;
	}
	return dato;
}


/**
 * @fn int8_t EnviarString(const char*, uint32_t)
 * @brief
 *
 * @param str
 * @param len
 * @return
 */
int8_t EnviarString (const char *str, uint32_t len)
{
	uint32_t i;

	if(len>=TXBUFFER_SIZE)
		return -1;

	for( i = 0 ; i<len ; i++ )
		PushTx( str[i] );

	return 0;
}

/**
 * @fn int8_t RecibirString(char*, uint32_t)
 * @brief
 *
 * @param buffer
 * @param len
 * @return
 */
int8_t RecibirString(char *buffer, uint32_t len)
{
    static uint32_t i = 0;
    uint8_t dato;
    int8_t error = -1;

    while ((dato=PopRx()) != UART_NO_DATA)
    {
    	if (dato == '\n')
        {
            buffer[i] = '\0';
            i=0;
            error = 0;
            break;
        }

        buffer[i] = dato;
        i++;
        if (i >= (len - 1))
        {
            buffer[i] = '\0';
            i=0;
            error = -2;
            break;
        }
    }

    return error;
}
