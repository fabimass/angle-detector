/*
===============================================================================
 Autores     : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripción : Definiciones para implementación del módulo acelerómetro
 MPU6050.
===============================================================================
*/

#ifndef ACELEROMETRO_H_
#define ACELEROMETRO_H_

#include <board.h>

/* Cantidad de muestras tomadas */
#define MUESTRAS	5

/* Valores referencia */
#define ANALOG_REF_1G		2780
#define ANALOG_REF_0G		1850
#define DIGITAL_REF_1G   	17300
#define DIGITAL_REF_0G		2785

/* Pines */
#define SDA_PORT           	0
#define SDA_PIN 	   	   	0
#define SCL_PORT			0
#define SCL_PIN  	   	   	1
#define SENS_DETECT_PORT	0
#define SENS_DETECT_PIN		8
#define CANAL_X_PORT		1
#define CANAL_X_PIN 		30
#define CANAL_Y_PORT		1
#define CANAL_Y_PIN 		31
#define CANAL_Z_PORT		0
#define CANAL_Z_PIN 		2
#define SLEEP_PORT			0
#define SLEEP_PIN			22
#define G_SELECT_PORT		2
#define G_SELECT_PIN		13
#define DET_0G_PORT			0
#define DET_0G_PIN			28

/* Registros del MPU6050 */
#define SLAVE_ADDRESS		0x68
#define ACCEL_XOUT_H		0x3B
#define ACCEL_XOUT_L		0x3C
#define ACCEL_YOUT_H		0x3D
#define ACCEL_YOUT_L		0x3E
#define ACCEL_ZOUT_H		0x3F
#define ACCEL_ZOUT_L		0x40
#define ACCEL_CONFIG		0x1C
#define PWR_MGMT_1			0x6B
#define WHO_AM_I			0x75

/* Canales de ADC para MMA7361 */
#define CANAL_X 			ADC_CH4
#define CANAL_Y  			ADC_CH5
#define CANAL_Z  			ADC_CH7


/* Sensores utilizados */
typedef enum {
	MMA_7361,
	MPU_6050
}ACCEL_SENSOR;

/* Estructura para los datos de aceleración */
typedef struct {
	uint32_t  x;
	uint32_t  y;
	uint32_t  z;
}ACCEL_DATA;


/* Detección del sensor */
ACCEL_SENSOR detectar_acelerometro(void);

/* Inicialización de I2C y del módulo acelerómetro MPU6050 */
void inicializar_MPU6050(void);

/* Lectura de aceleración por I2C */
ACCEL_DATA leer_acel_digital(void);

/* Inicialización de ADC y del módulo acelerómetro MMA7361 */
void inicializar_MMA7361(void);

/* Lectura de aceleración por ADC */
ACCEL_DATA leer_acel_analogico(void);

/* Calcula el promedio de las muestras tomadas */
ACCEL_DATA promedio(ACCEL_DATA *vector);


#endif /* ACELEROMETRO_H_ */
