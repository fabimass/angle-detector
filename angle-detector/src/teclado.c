/*
===============================================================================
 Autores     : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripción : Biblioteca de funciones para implementación de teclado
 matricial
===============================================================================
*/


#include <teclado.h>


/* Realiza la lectura del taclado */
uint32_t leer_teclado(void)
{

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA1_PORT,FILA1_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN))
	   return 1;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA1_PORT,FILA1_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN))
	   return 2;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA1_PORT,FILA1_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN))
	   return 3;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA1_PORT,FILA1_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN))
       return ACEPTAR;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA2_PORT,FILA2_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN))
       return 4;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA2_PORT,FILA2_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN))
       return 5;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA2_PORT,FILA2_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN))
       return 6;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA2_PORT,FILA2_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN))
       return NADA;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA3_PORT,FILA3_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN))
       return 7;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA3_PORT,FILA3_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN))
       return 8;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA3_PORT,FILA3_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN))
       return 9;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA3_PORT,FILA3_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN))
       return NADA;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA4_PORT,FILA4_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN))
       return NADA;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA4_PORT,FILA4_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN))
       return 0;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA4_PORT,FILA4_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN))
       return NADA;

   if (Chip_GPIO_GetPinState(LPC_GPIO,FILA4_PORT,FILA4_PIN) && Chip_GPIO_GetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN))
       return NADA;

   /* Si llega aca no se pulsó ningún botón */
   return NADA;
}

/* Encendido secuencial de columnas */
void ciclo_teclado(void)
{
	static uint32_t var=0;

    switch(var)
    {

    case 0:
    	   var ++;
    	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN,1);
    	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN,0);
    	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN,0);
    	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN,0);
    	   break;

    case 1:
       	   var ++;
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN,1);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN,0);
       	   break;
    case 2:
       	   var ++;
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN,1);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN,0);
       	   break;

    case 3:
       	   var=0;
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN,0);
       	   Chip_GPIO_SetPinState(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN,1);
       	   break;
    default:
    	break;
    }
}


/* Inicialización de pines vinculados al teclado */
void inicializar_teclado(void)
{
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,COLUMNA1_PORT,COLUMNA1_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,COLUMNA2_PORT,COLUMNA2_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,COLUMNA3_PORT,COLUMNA3_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,COLUMNA4_PORT,COLUMNA4_PIN);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO,FILA1_PORT,FILA1_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,FILA2_PORT,FILA2_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,FILA3_PORT,FILA3_PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,FILA4_PORT,FILA4_PIN);

	/* Resistencias de pull-down internas */
	Chip_IOCON_PinMux(LPC_IOCON,FILA1_PORT,FILA1_PIN,MD_PDN,IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON,FILA2_PORT,FILA2_PIN,MD_PDN,IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON,FILA3_PORT,FILA3_PIN,MD_PDN,IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON,FILA4_PORT,FILA4_PIN,MD_PDN,IOCON_FUNC0);
}
