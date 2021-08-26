/*
===============================================================================
 Autores      : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripción : Definiciones para implementación de teclado matricial
===============================================================================
*/

#ifndef TECLADO_H_
#define TECLADO_H_

#include <board.h>

/* Definiciones de implementación */
#define ACEPTAR 11
#define NADA	12

/* Asignación de pines */
#define FILA1_PORT  2
#define FILA1_PIN   11

#define FILA2_PORT  2
#define FILA2_PIN   10

#define FILA3_PORT  2
#define FILA3_PIN   8

#define FILA4_PORT  2
#define FILA4_PIN   7

#define COLUMNA1_PORT  2
#define COLUMNA1_PIN   6

#define COLUMNA2_PORT  2
#define COLUMNA2_PIN   5

#define COLUMNA3_PORT  2
#define COLUMNA3_PIN   4

#define COLUMNA4_PORT  2
#define COLUMNA4_PIN   3

/* Funciones para el teclado */
uint32_t leer_teclado(void);
void ciclo_teclado(void);
void inicializar_teclado(void);

#endif /* TECLADO_H_ */
