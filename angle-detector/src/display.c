/*
===============================================================================
 Autores     : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripción : Biblioteca de funciones para implementación de displays
 7 segmentos del tipo cátodo común a partir de los C-561.
===============================================================================
*/


#include <display.h>

/* Inicialización de pines vinculados a los displays */
void Display_InitDisplays(void)
{
	Chip_IOCON_PinMux(LPC_IOCON, SEG_A_PORT, SEG_A_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_A_PORT,SEG_A_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_B_PORT, SEG_B_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_B_PORT,SEG_B_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_C_PORT, SEG_C_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_C_PORT,SEG_C_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_D_PORT, SEG_D_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_D_PORT,SEG_D_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_E_PORT, SEG_E_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_E_PORT,SEG_E_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_F_PORT, SEG_F_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_F_PORT,SEG_F_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, SEG_G_PORT, SEG_G_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,SEG_G_PORT,SEG_G_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, UNIDAD_PORT, UNIDAD_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,UNIDAD_PORT,UNIDAD_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,UNIDAD_PORT,UNIDAD_PIN,false);

	Chip_IOCON_PinMux(LPC_IOCON, DECENA_PORT, DECENA_PIN, IOCON_MODE_INACT, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,DECENA_PORT,DECENA_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO,DECENA_PORT,DECENA_PIN,false);

	//Chip_GPIO_SetPinDIROutput(LPC_GPIO,CENTENA_PORT,CENTENA_PIN);
	//Chip_GPIO_SetPinState(LPC_GPIO,CENTENA_PORT,CENTENA_PIN,false);
}

/* Apaga el display */
void Display_TurnOff (display_t display)
{
	switch(display)
		{
		 case 0:
			 Chip_GPIO_SetPinState(LPC_GPIO,UNIDAD_PORT,UNIDAD_PIN,false);
			 break;

		 case 1:
			 Chip_GPIO_SetPinState(LPC_GPIO,DECENA_PORT,DECENA_PIN,false);
			 break;

		 case 2:
			 Chip_GPIO_SetPinState(LPC_GPIO,CENTENA_PORT,CENTENA_PIN,false);
			 break;
		}
}

/* Enciende el display */
void Display_TurnOn (display_t display)
{
	switch(display)
		{
		 case 0:
			 Chip_GPIO_SetPinState(LPC_GPIO,UNIDAD_PORT,UNIDAD_PIN,true);
			 break;

		 case 1:
			 Chip_GPIO_SetPinState(LPC_GPIO,DECENA_PORT,DECENA_PIN,true);
			 break;

		 case 2:
			 Chip_GPIO_SetPinState(LPC_GPIO,CENTENA_PORT,CENTENA_PIN,true);
			 break;
		}
}

/* Apaga todos los segmentos */
void Display_Clean(void)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,false);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,false);
}

/* Muestra un 0 */
void Display_Print0 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 1 */
void Display_Print1 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 2 */
void Display_Print2 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 3 */
void Display_Print3 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 4 */
void Display_Print4 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 5 */
void Display_Print5 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 6 */
void Display_Print6 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 7 */
void Display_Print7 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 8 */
void Display_Print8 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_E_PORT,SEG_E_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra un 9*/
void Display_Print9 (display_t display)
{
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_A_PORT,SEG_A_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_B_PORT,SEG_B_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_C_PORT,SEG_C_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_D_PORT,SEG_D_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_F_PORT,SEG_F_PIN,true);
	Chip_GPIO_SetPinState(LPC_GPIO,SEG_G_PORT,SEG_G_PIN,true);

	Display_TurnOn(display);
}

/* Muestra en la combinación de displays un valor que puede ser de
 * más de una cifra. */
void Display_PrintValue (uint32_t value)
{
	static uint32_t display = 0;
	uint32_t unidades = 0;
	uint32_t decenas = 0;
	uint32_t centenas = 0;

	if(value > 0)
	{
		centenas=value/100;
		decenas=(value%100)/10;
		unidades=(value%100)%10;
	}

	if(display)
	{
		Display_TurnOff(UNIDAD);
		Display_Clean();
		switch(decenas)
		{
					 case 0:
						 Display_Print0(DECENA);
						 break;

					 case 1:
						 Display_Print1(DECENA);
						 break;

					 case 2:
						 Display_Print2(DECENA);
						 break;

					 case 3:
						 Display_Print3(DECENA);
						 break;

					 case 4:
						 Display_Print4(DECENA);
						 break;

					 case 5:
						 Display_Print5(DECENA);
						 break;

					 case 6:
						 Display_Print6(DECENA);
						 break;

					 case 7:
						 Display_Print7(DECENA);
						 break;

					 case 8:
						 Display_Print8(DECENA);
						 break;

					 case 9:
						 Display_Print9(DECENA);
						 break;
		}

		display = 0;
	}
	else
	{
		Display_TurnOff(DECENA);
		Display_Clean();
		switch(unidades)
		{
						 case 0:
							 Display_Print0(UNIDAD);
							 break;

						 case 1:
							 Display_Print1(UNIDAD);
							 break;

						 case 2:
							 Display_Print2(UNIDAD);
							 break;

						 case 3:
							 Display_Print3(UNIDAD);
							 break;

						 case 4:
							 Display_Print4(UNIDAD);
							 break;

						 case 5:
							 Display_Print5(UNIDAD);
							 break;

						 case 6:
							 Display_Print6(UNIDAD);
							 break;

						 case 7:
							 Display_Print7(UNIDAD);
							 break;

						 case 8:
							 Display_Print8(UNIDAD);
							 break;

						 case 9:
							 Display_Print9(UNIDAD);
							 break;
		}

		display = 1;
	}

	/*switch(centenas)
		{
		 case 0:
			 Display_Print0(CENTENA);
			 break;

		 case 1:
			 Display_Print1(CENTENA);
			 break;

		 case 2:
			 Display_Print2(CENTENA);
			 break;

		 case 3:
			 Display_Print3(CENTENA);
			 break;

		 case 4:
			 Display_Print4(CENTENA);
			 break;

		 case 5:
			 Display_Print5(CENTENA);
			 break;

		 case 6:
			 Display_Print6(CENTENA);
			 break;

		 case 7:
			 Display_Print7(CENTENA);
			 break;

		 case 8:
			 Display_Print8(CENTENA);
			 break;

		 case 9:
			 Display_Print9(CENTENA);
			 break;
		}*/

}

