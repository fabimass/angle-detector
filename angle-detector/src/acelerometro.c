/*
===============================================================================
 Autores     : Contartese Nicolás - Fariñas Deborah - Massotto Fabián
 Descripcion : Biblioteca de funciones para implementación del módulo
 acelerómetro MPU6050.
===============================================================================
*/


#include <acelerometro.h>

/* Buffer de escritura I2C */
unsigned char I2C_Buffer_Tx[10];
/* Buffer de lectura I2C */
unsigned char I2C_Buffer_Rx[10];
/* Estructura para la configuración de ADC */
static ADC_CLOCK_SETUP_T ADCSetup;
/* Flag para la conversión ADC */
volatile uint32_t ADC_FLAG = 0;


/* Detección del sensor */
ACCEL_SENSOR detectar_acelerometro(void)
{
	if(Chip_GPIO_GetPinState(LPC_GPIO, SENS_DETECT_PORT, SENS_DETECT_PIN))
		return MPU_6050;
	else
		return MMA_7361;
}


/* Interrupción de I2C */
void I2C1_IRQHandler(void)
{
	Chip_I2C_MasterStateHandler(I2C1);
}


/* Inicialización de I2C y del módulo acelerómetro MPU6050 */
void inicializar_MPU6050(void)
{
	/* Configura los pines de I2C */
	Chip_IOCON_PinMux(LPC_IOCON, SDA_PORT, SDA_PIN, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, SCL_PORT, SCL_PIN, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_EnableOD(LPC_IOCON, SDA_PORT, SDA_PIN);
	Chip_IOCON_EnableOD(LPC_IOCON, SCL_PORT, SCL_PIN);
	/* Inicializa el módulo */
	Chip_I2C_Init(I2C1);
	/* Establece el clock */
	Chip_I2C_SetClockRate(I2C1, 100000);
	/* Handler de I2C */
	Chip_I2C_SetMasterEventHandler (I2C1, Chip_I2C_EventHandler);
	/* Habilita la interrupción */
	NVIC_EnableIRQ(I2C1_IRQn);

	/* Se configura el acelerómetro para que trabaje en el rango de 2g */
	I2C_Buffer_Tx[0] = ACCEL_CONFIG;
	I2C_Buffer_Tx[1] = 0x00;
	Chip_I2C_MasterSend (I2C1, SLAVE_ADDRESS, I2C_Buffer_Tx, 2);

	/* Saca al módulo del modo sleep */
	I2C_Buffer_Tx[0] = PWR_MGMT_1;
	I2C_Buffer_Tx[1] = 0x00;
	Chip_I2C_MasterSend (I2C1, SLAVE_ADDRESS, I2C_Buffer_Tx, 2);
}


/* Lectura de aceleración por I2C */
ACCEL_DATA leer_acel_digital(void)
{
	ACCEL_DATA accel;

	I2C_Buffer_Tx[0] = ACCEL_XOUT_H;
	/* Se posiciona en el registro */
	Chip_I2C_MasterSend (I2C1, SLAVE_ADDRESS, I2C_Buffer_Tx, 1);
	/* Se leen los 6 valores de aceleración */
	Chip_I2C_MasterRead (I2C1, SLAVE_ADDRESS, I2C_Buffer_Rx, 6);

	/* Composición entre las partes alta y baja */
	accel.x = (I2C_Buffer_Rx[0] << 8) + I2C_Buffer_Rx[1];
	accel.y = (I2C_Buffer_Rx[2] << 8) + I2C_Buffer_Rx[3];
	accel.z = (I2C_Buffer_Rx[4] << 8) + I2C_Buffer_Rx[5];

	return accel;
}


/* Inicialización de ADC y del módulo acelerómetro MMA7361 */
void inicializar_MMA7361(void)
{
	/* Configura los pines de ADC */
	Chip_IOCON_PinMux(LPC_IOCON, CANAL_X_PORT, CANAL_X_PIN, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, CANAL_Y_PORT, CANAL_Y_PIN, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, CANAL_Z_PORT, CANAL_Z_PIN, IOCON_MODE_INACT, IOCON_FUNC2);

	/* Despierta al módulo */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, SLEEP_PORT, SLEEP_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO, SLEEP_PORT, SLEEP_PIN, true);

	/* Se configura el acelerómetro para que trabaje en el rango de 1.5g */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, G_SELECT_PORT, G_SELECT_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO, G_SELECT_PORT, G_SELECT_PIN, false);

	/* Detección de 0G en los tres ejes */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, DET_0G_PORT, DET_0G_PIN);

	/* Inicializa el ADC */
	Chip_ADC_Init(LPC_ADC, &ADCSetup);

	/* Muestras por segundo */
	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, ADC_MAX_SAMPLE_RATE);

}


/* Lectura de aceleración por ADC */
ACCEL_DATA leer_acel_analogico(void)
{
	uint16_t adc_data;
	ACCEL_DATA accel;

	/* Habilita el canal para la medición de X */
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Y, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Z, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_X, ENABLE);
	/* Inicia la conversión ADC */
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	/* Espera que termine la conversión */
	while(Chip_ADC_ReadStatus(LPC_ADC, CANAL_X, ADC_DR_DONE_STAT) != SET);
	/* Lee el valor de ADC */
	Chip_ADC_ReadValue(LPC_ADC, CANAL_X, &adc_data);
	accel.x = adc_data;

	/* Habilita el canal para la medición de Y */
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_X, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Z, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Y, ENABLE);
	/* Inicia la conversión ADC */
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	/* Espera que termine la conversión */
	/* Lee el valor de ADC */
	while(Chip_ADC_ReadStatus(LPC_ADC, CANAL_Y, ADC_DR_DONE_STAT) != SET);
	Chip_ADC_ReadValue(LPC_ADC, CANAL_Y, &adc_data);
	accel.y = adc_data;

	/* Habilita el canal para la medición de Z */
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_X, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Y, DISABLE);
	Chip_ADC_EnableChannel(LPC_ADC, CANAL_Z, ENABLE);
	/* Inicia la conversión ADC */
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	/* Espera que termine la conversión */
	while(Chip_ADC_ReadStatus(LPC_ADC, CANAL_Z, ADC_DR_DONE_STAT) != SET);
	/* Lee el valor de ADC */
	Chip_ADC_ReadValue(LPC_ADC, CANAL_Z, &adc_data);
	accel.z = adc_data;

	return accel;
}


/* Calcula el promedio de las muestras tomadas */
ACCEL_DATA promedio(ACCEL_DATA *vector)
{
	ACCEL_DATA acumulador;
	ACCEL_DATA aux;
	uint32_t i;

	acumulador.x = 0;
	acumulador.y = 0;
	acumulador.z = 0;

	for(i=0;i<MUESTRAS;i++)
	{
		aux = vector[i];
		acumulador.x += aux.x;
		acumulador.y += aux.y;
		acumulador.z += aux.z;
	}

	acumulador.x = acumulador.x / MUESTRAS;
	acumulador.y = acumulador.y / MUESTRAS;
	acumulador.z = acumulador.z / MUESTRAS;

	return acumulador;
}
