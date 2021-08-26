
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "acelerometro.h"
#include "teclado.h"
#include "display.h"

#define RESOLUCION	2

xQueueHandle qAcelerometro;
xQueueHandle qTeclado;
xQueueHandle qDisplay;
xQueueHandle qBuzzer;


static vTaskMaster (void)
{
	uint32_t numero;
	uint32_t inclinacion;
	uint32_t estado;

	while(1)
	{
		/* Recibe la inclinación medida */
		xQueueReceive(qAcelerometro,&inclinacion,portMAX_DELAY);

		/* Mira el numero ingresado por teclado */
		xQueuePeek(qTeclado,&numero,portMAX_DELAY);

		/* Transmite la inclinación buscada a la tarea de manejo de displays */
		xQueueOverwrite(qDisplay,&numero);

		/* Puse esto porque habia problemas para detectar 0 grados */
		inclinacion += RESOLUCION;
		numero += RESOLUCION;

		/* Realiza la comparación entre la inclinación medida y la deseada */
		if((inclinacion >= (numero - RESOLUCION)) && (inclinacion <= (numero + RESOLUCION)))
		{
			/* Hace sonar el buzzer */
			estado = 1;
			xQueueOverwrite(qBuzzer,&estado);
		}
		else
		{
			/* Apaga el buzzer */
			estado = 0;
			xQueueOverwrite(qBuzzer,&estado);
		}
	}
}


static vTaskTeclado (void)
{

	uint32_t numero=0;
	uint32_t actual;
	uint32_t anterior=0;


   while(1)
   {
	   actual = leer_teclado();
	   if(actual != NADA)
	   {
		   /* Antirrebote */
		   vTaskDelay(50/portTICK_RATE_MS);

		   actual = leer_teclado();

		   if(actual != NADA)
		   	   {
			   	   if(actual == ACEPTAR)
			   	   {
			   		   xQueueOverwrite(qTeclado,&numero);
			   	   }
			   	   else
			   	   {
			   		   numero = anterior * 10 + actual;
			   		   anterior = actual;
			   	   }
		   	   }

		   /* Espera que suelte el botón */
		   while(actual != NADA)
			   actual = leer_teclado();
	   }

	   ciclo_teclado();
   }
}


static vTaskAcelerometro (void)
{
	ACCEL_DATA accel;
	ACCEL_DATA vector[MUESTRAS];
	double gamma;
	uint32_t i;
	uint32_t result;

	/* Puse esta demora porque el acelerometro digital no llegaba a prenderse antes de inicializarlo */
	vTaskDelay(1000/portTICK_RATE_MS);

	/* Inicializa el acelerómetro */
	if(detectar_acelerometro() == MPU_6050)
		inicializar_MPU6050();
	if(detectar_acelerometro() == MMA_7361)
		inicializar_MMA7361();

	while(1)
	{
		/* Frecuencia de adquisición de datos */
		vTaskDelay(250/portTICK_RATE_MS);

		/* Se toman varias muestras de la aceleración */

		if(detectar_acelerometro() == MPU_6050)
		{
			for(i=0;i<MUESTRAS;i++)
			{
				vector[i] = leer_acel_digital();
			}
		}

		if(detectar_acelerometro() == MMA_7361)
		{
			for(i=0;i<MUESTRAS;i++)
			{
				vector[i] = leer_acel_analogico();
			}
		}

		/* Se toma un promedio */
		accel = promedio(vector);

		/* Se calcula la inclinación */
		/* El eje utilizado depende de la posición del acelerómetro en la placa */

		if(detectar_acelerometro() == MPU_6050)
		{
			if(accel.x > DIGITAL_REF_0G)
				accel.x -= DIGITAL_REF_0G; // Se hace corresponder el cero con 0g
			else
				accel.x = DIGITAL_REF_0G - accel.x;

			if(accel.x > (DIGITAL_REF_1G - DIGITAL_REF_0G))
				accel.x = (DIGITAL_REF_1G - DIGITAL_REF_0G); // no puede ser mayor que la referencia de 1g

			gamma = acos( (double)accel.x / (DIGITAL_REF_1G - DIGITAL_REF_0G) );
		}

		if(detectar_acelerometro() == MMA_7361)
		{
			accel.z -= ANALOG_REF_0G; // Se hace corresponder el cero con 0g

			if(accel.z > (ANALOG_REF_1G - ANALOG_REF_0G)) // no puede ser mayor que la referencia de 1g
				accel.z = (ANALOG_REF_1G - ANALOG_REF_0G);

			gamma = acos( (double)accel.z / (ANALOG_REF_1G - ANALOG_REF_0G) );
		}

		/* Conversión a grados */
		gamma = gamma * 180 / 3.14;

		result = (uint32_t)gamma;

		/* Pone los datos en una cola */
		xQueueSendToBack(qAcelerometro, &result, portMAX_DELAY);
	}
}


static vTaskBuzzer (void)
{
	uint32_t estado;

	while(1)
	{
		/* Recibe la orden de prender o no el buzzer */
		xQueuePeek(qBuzzer,&estado,portMAX_DELAY);

		if(estado == 1)
		{
			/* Togglea el buzzer */
			Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 9);
		}

		if(estado == 0)
		{
			/* Apaga el buzzer */
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, false);
		}

		/* Demora para la intermitencia */
		vTaskDelay(100/portTICK_RATE_MS);
	}
}


static vTaskDisplay (void)
{
	uint32_t numero;

	while(1)
	{
		/* Frecuencia de encendido de los displays */
		vTaskDelay(10/portTICK_RATE_MS);

		/* Lee el valor a mostrar */
		xQueuePeek(qDisplay,&numero,portMAX_DELAY);

		/* Muestra el valor */
		Display_PrintValue(numero);
	}
}



int main (void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Setea el pin que detecta el acelerómetro usado */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, SENS_DETECT_PORT, SENS_DETECT_PIN);

	/* Inicializa el buzzer */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 9);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, false);

	/* Inicializa el teclado */
	inicializar_teclado();

	/* Inicializa el display */
	Display_InitDisplays();

	/* Creación de colas */
	qAcelerometro = xQueueCreate(1,sizeof(uint32_t));
	qTeclado = xQueueCreate(1,sizeof(uint32_t));
	qDisplay = xQueueCreate(1,sizeof(uint32_t));
	qBuzzer = xQueueCreate(1,sizeof(uint32_t));


	/* Creación de tareas */
	xTaskCreate(vTaskMaster, (char *) "vTaskMaster",
		        configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
		        (xTaskHandle *) NULL);
	xTaskCreate(vTaskAcelerometro, (char *) "vTaskAcelerometro",
	        	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
	        	(xTaskHandle *) NULL);
	xTaskCreate(vTaskTeclado, (char *) "vTaskTeclado",
		        configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
		        (xTaskHandle *) NULL);
	xTaskCreate(vTaskBuzzer, (char *) "vTaskBuzzer",
			    configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			    (xTaskHandle *) NULL);
	xTaskCreate(vTaskDisplay, (char *) "vTaskDisplay",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Arranca el scheduler */
	vTaskStartScheduler();

	while(1);
}
