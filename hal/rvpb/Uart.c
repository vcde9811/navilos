#include "stdint.h"
#include "Uart.h"
#include "HalUart.h"

extern volatile PL011_t* Uart;

void Hal_uart_init(void)
{
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0; // UART off
    Uart->uartcr.bits.TXE = 1; // output on
    Uart->uartcr.bits.RXE = 1; // input on
    Uart->uartcr.bits.UARTEN = 1; // UART on
}

void Hal_uart_put_char(uint8_t ch)
{
	// Waiting while Tx is full.
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void)
{
	uint32_t data;
	// Waiting while Rx is empty
	while(Uart->uartfr.bits.RXFE);
	data = Uart->uartdr.all;
	// If there error flag is on
	if (data & 0xFFFFFF00) {
			Uart->uartrsr.all = 0xFF;
			return 0;
	}
	return (uint8_t)(data & 0xFF);
}
