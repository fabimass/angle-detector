/*
===============================================================================
 Autores     : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripción : Definiciones para implementación de displays 7 segmentos del tipo
 cátodo común a partir de los C-561.
===============================================================================
*/

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <board.h>

/* Asignación de pines */
#define SEG_A_PORT 		2
#define SEG_A_PIN 		1

#define SEG_B_PORT 		2
#define SEG_B_PIN 		2

#define SEG_C_PORT 		2
#define SEG_C_PIN 		0

#define SEG_D_PORT 		0
#define SEG_D_PIN 		11

#define SEG_E_PORT 		0
#define SEG_E_PIN 		10

#define SEG_F_PORT 		0
#define SEG_F_PIN 		5

#define SEG_G_PORT 		0
#define SEG_G_PIN 		4

#define UNIDAD_PORT		0
#define UNIDAD_PIN	 	15

#define DECENA_PORT		0
#define DECENA_PIN		17

#define CENTENA_PORT	2
#define CENTENA_PIN		6

/* Displays */
typedef enum{
	UNIDAD,
	DECENA,
	CENTENA
}display_t;

/* Funciones 7 segmentos */

/* Inicializaciones de pines vinculados al control de los displays 7 segmentos */
void Display_InitDisplays(void);

/* Apaga un display poniendo su pin común en estado alto (por ser cátodo común) */
void Display_TurnOff (display_t Display);

/* Enciende un display poniendo su pin común en estado bajo (por ser cátodo común) */
void Display_TurnOn (display_t Display);

/* Apaga todos los segmentos de los display*/
void Display_Clean (void);

/* Imprime un 0 en el display seleccionado */
void Display_Print0 (display_t Display);

/* Imprime un 1 en el display seleccionado */
void Display_Print1 (display_t Display);

/* Imprime un 2 en el display seleccionado */
void Display_Print2 (display_t Display);

/* Imprime un 3 en el display seleccionado */
void Display_Print3 (display_t Display);

/* Imprime un 4 en el display seleccionado */
void Display_Print4 (display_t Display);

/* Imprime un 5 en el display seleccionado */
void Display_Print5 (display_t Display);

/* Imprime un 6 en el display seleccionado */
void Display_Print6 (display_t Display);

/* Imprime un 7 en el display seleccionado */
void Display_Print7 (display_t Display);

/* Imprime un 8 en el display seleccionado */
void Display_Print8 (display_t Display);

/* Imprime un 9 en el display seleccionado */
void Display_Print9 (display_t Display);

/* Realiza la conversión necesaria para imprimir un número
 * de hasta 3 cifras utilizando los 3 displays disponibles*/
void Display_PrintValue(uint32_t value);


#endif /* DISPLAY_H_ */
