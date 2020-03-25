/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

extern void vApplicationStackOverflowHook(
	xTaskHandle *pxTask,
	signed portCHAR *pcTaskName);

void
vApplicationStackOverflowHook(
  xTaskHandle *pxTask __attribute((unused)),
  signed portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	
}

static void
gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO12);
	gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);
	gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO14);
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);
	gpio_set_mode(GPIOB,GPIO_MODE_INPUT,GPIO_CNF_INPUT_PULL_UPDOWN,GPIO10);
}

static void
task1(void *args __attribute((unused))) {

	for (;;) {
		gpio_toggle(GPIOB,GPIO12);
		vTaskDelay(pdMS_TO_TICKS(500));
		gpio_toggle(GPIOB,GPIO13);
		vTaskDelay(pdMS_TO_TICKS(500));
		gpio_toggle(GPIOB,GPIO14);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void
task2(void *args __attribute((unused))) {

	while (1) 
	{
		gpio_set(GPIOC, GPIO13); // LED off
		if (gpio_get(GPIOB, GPIO10)) //if Button on
			gpio_clear(GPIOC, GPIO13); //LED on

	}
}

int
main(void) {

	rcc_clock_setup_in_hse_8mhz_out_72mhz(); 

	gpio_setup();

	xTaskCreate(task1,"LED",100,NULL,configMAX_PRIORITIES-1,NULL);
	xTaskCreate(task2,"BUTTONN",100,NULL,configMAX_PRIORITIES-1,NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}
