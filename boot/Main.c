#include "stdint.h"
#include "HalUart.h"

static void Hw_init(void);

void main(void)
{
	Hw_init();

	uint8_t ch, i = 100;

	while (i--) {
		ch = Hal_uart_get_char();
		Hal_uart_put_char(ch);
	}
}

static void Hw_init(void)
{
	Hal_uart_init();
}
