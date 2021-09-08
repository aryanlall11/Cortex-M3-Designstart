#include "m3_for_arty.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xuartlite.h"

#define LED_CHANNEL 1
#define LED_MASK 0x03

static XGpio Gpio_Led;
static XUartLite UART0_instance;

int main()
{
	int status = XUartLite_Initialize(&UART0_instance, XPAR_AXI_UARTLITE_0_DEVICE_ID);

	NVIC_ClearAllPendingIRQ();

	print("Hello World\r\n");

	status = XGpio_Initialize(&Gpio_Led, XPAR_AXI_GPIO_0_DEVICE_ID);

        XGpio_SetDataDirection(&Gpio_Led, LED_CHANNEL, ~LED_MASK);

	XGpio_DiscreteWrite(&Gpio_Led, LED_CHANNEL, 0x0);

	while ( 1 )
	{
		XGpio_DiscreteWrite(&Gpio_Led, LED_CHANNEL, 1);
		for(int i=0;i<500000;i++);
		XGpio_DiscreteWrite(&Gpio_Led, LED_CHANNEL, 0);
		for(int i=0;i<500000;i++);
	}
	return 0;
}
