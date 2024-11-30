#include "Uart.h"

void UartInit(long u32_UartBaudRate)
{
    unsigned int u32_BaudPreScale = (((F_CPU / (u32_UartBaudRate * 16UL))) - 1);

    /* Set the baudrate */
    UBRR0L = u32_BaudPreScale;
    UBRR0H = u32_BaudPreScale >> 8;
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void UartTransmit(char data)
{
    /* Wait until not busy */
    while ( !( UCSR0A & _BV ( UDRE0 ) ) );
    /* Send input byte */
    UDR0 = data;
    /* Wait until not busy */
    while ( !( UCSR0A & _BV ( UDRE0 ) ) );
}

void UartTransmitString(const char *str)
{
	unsigned char j=0;
	
	while (str[j])		/* Send string till null */
	{
		UartTransmit(str[j]);	
		j++;
	}
}


char UartDataAvalable ( void )
{
    return UCSR0A & _BV ( RXC0 );
}

unsigned char UartReceive(void)
{
    while (!UartDataAvalable());	/* Wait for data to be received */
    return UDR0;				/* Get and return received data from buffer */
}

void UartReceiveString(char *str)
{
    unsigned char data;
    do
    {
        data = UartReceive();
        *str = data;
        str++;
    } while (data != '\0');
}