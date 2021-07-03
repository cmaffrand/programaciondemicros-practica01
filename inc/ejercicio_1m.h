/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/02
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __EJERCICIO_1M_H__
#define __EJERCICIO_1M_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

const gpioMap_t secuencia[] = {LEDB, LED1, LED2, LED3};
const uint8_t ultimoLed = sizeof(secuencia)/sizeof(gpioMap_t);

/*=====[Public function-like macros]=========================================*/

static bool_t encenderLed( gpioMap_t led )
{
   bool_t ret_val     = 1;

   if ((led == LEDB) || (led == LED1) || (led == LED2) || (led == LED3)) {
	   gpioWrite( led, 1 );
   }
   else {
	   // No se puede encender ningun led.
	   ret_val     = 0;
	   printf("\n Error: Se intentó encender un led no permitido");
	   }

   return ret_val;
}

static bool_t apagarLeds(void)
{
   bool_t ret_val     = 1;

	gpioWrite( LEDB, 0 );
	gpioWrite( LED1, 0 );
	gpioWrite( LED2, 0 );
	gpioWrite( LED3, 0 );

   return ret_val;
}

static bool_t leerTecla (gpioMap_t tecla)
{
	bool_t ret_val;

   if ((tecla == TEC1) || (tecla == TEC2) || (tecla == TEC3) || (tecla == TEC4)) {
	   ret_val = gpioRead( tecla );
   }
   else {
   // No se puede leer ninguna tecla.
   ret_val     = 1;
   printf("\n Error: Se intentó presionar una tecla no permitida");
   }

	return ret_val;
}

static void activarSecuencia(gpioMap_t * psecuencia, bool_t dirValue) {
	static uint8_t estado = 0;

	if (dirValue == FALSE) {
		// Rotacion a la derecha
		estado++;
		if (estado > ultimoLed-1)  estado = 0;
   }
   else {
	   // Rotacion a la izquierda
	   estado--;
	   if (estado > ultimoLed-1) estado = ultimoLed-1;
   }

   //  Chequeo y llamado de funciones sobre leds
   if (!(apagarLeds())) {
	   printf("\n Error: Secuencia Detenida");
	   while(true){}
   }
   if (!(encenderLed(psecuencia[estado]))) {
	   printf("\n Error:Secuencia Detenida");
	   while(true){}
   }
}

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __EJERCICIO_1M_H__ */
