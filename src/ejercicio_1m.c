/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/02
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "ejercicio_1m.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
	 // Inicializar y configurar la plataforma
	   boardConfig();

	   // Inicializar las variables y estructuras del retardo no bloqueante.
	   tick_t delayTime    = 150;
	   delay_t NonBlockingDelay;
	   delayConfig( &NonBlockingDelay, delayTime );

	   // Crear varias variables
	   gpioMap_t * psecuencia = secuencia;
	   bool_t dirValueFlag    = FALSE;
	   bool_t timeChangeFlag  = FALSE;

   // Mensaje de inició del programa
   printf("Secuencia Comenzada\n");
   // ----- Repeat for ever -------------------------
   while( true ) {

	   if (delayRead(&NonBlockingDelay) == TRUE) {
			activarSecuencia(psecuencia, dirValueFlag);
			// Se vuelve a activar el cambio de base de tiempo
			timeChangeFlag   = FALSE;
	   }
	   // Si no se cumple el delay pooling de botones.
		 else {
			if (timeChangeFlag == FALSE) {
				if (leerTecla( TEC3 ) == OFF) {
					delayTime = 750;
					delayConfig( &NonBlockingDelay, delayTime );
					timeChangeFlag   = TRUE;
				}
				if (leerTecla( TEC2 ) == OFF) {
					delayTime = 150;
					delayConfig( &NonBlockingDelay, delayTime );
					timeChangeFlag   = TRUE;
				}
			}
			if (leerTecla( TEC1 ) == OFF) dirValueFlag = TRUE;
			if (leerTecla( TEC4 ) == OFF) dirValueFlag = FALSE;
		 }


   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
