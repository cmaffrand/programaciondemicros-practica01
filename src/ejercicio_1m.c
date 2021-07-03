/*=============================================================================
 * Author: Carlos Maffrand <carlosmaffrand5@gmail.com>
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

	   // Crear varias variables del tipo booleano

	   // Crear varias variables del tipo entero
	   const gpioMap_t psecuencia[] = {LEDB, LED1, LED2, LED3};
	   const uint8_t ultimoLed = sizeof(psecuencia)/sizeof(gpioMap_t);
	   uint8_t estado = 0;
	   // Crear varias variables del tipo booleano
	   bool_t dirValue    = FALSE;
	   bool_t timeChange   = FALSE;

	   apagarLeds();

   // ----- Repeat for ever -------------------------
   while( true ) {

	   if (delayRead(&NonBlockingDelay) == TRUE) {
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

		   if (!(apagarLeds())) {while(true){}}
			if (!(encenderLed(psecuencia[estado]))) {while(true){}}
			//  Finaliza la secuencia por error.

			// Se vuelve a activar el cambio de base de tiempo
			timeChange   = FALSE;
	   }
	   // Si no se cumple el delay pooling de botones.
		 else {
			if (timeChange == FALSE) {
				if (leerTecla( TEC3 ) == OFF) {
					delayTime = 750;
					delayConfig( &NonBlockingDelay, delayTime );
				}
				if (leerTecla( TEC2 ) == OFF) {
					delayTime = 150;
					delayConfig( &NonBlockingDelay, delayTime );
				}
				timeChange   = TRUE;
			}
			if (leerTecla( TEC1 ) == OFF) dirValue = TRUE;
			if (leerTecla( TEC4 ) == OFF) dirValue = FALSE;
		 }


   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
