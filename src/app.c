/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar las variables y estructuras del retardo no bloqueante.
   tick_t delayTime    = 150;
   delay_t NonBlockingDelay;
   delayConfig( &NonBlockingDelay, delayTime );

   // Crear varias variables del tipo booleano
   bool_t dirValue    = FALSE;
   bool_t ledValueA    = 1;
   bool_t ledValue1    = 0;
   bool_t ledValue2    = 0;
   bool_t ledValue3    = 0;
   bool_t ledMem       = 0;

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

	   // Si se cumple el delay no bloqueante asigno salidas.
	   if (delayRead(&NonBlockingDelay) == TRUE) {
		   if (dirValue == FALSE) {
			  // Rotacion a la derecha
			  ledMem    = ledValueA;
			  ledValueA = ledValue1;
			  ledValue1 = ledValue2;
			  ledValue2 = ledValue3;
			  ledValue3 = ledMem;
		  }
		  else {
			  // Rotacion a la izquierda
			  ledMem    = ledValueA;
			  ledValueA = ledValue3;
			  ledValue3 = ledValue2;
			  ledValue2 = ledValue1;
			  ledValue1 = ledMem;
		  }
    	  // Asigación de salidas
		  gpioWrite( LEDA, ledValueA );
		  gpioWrite( LED1, ledValue1 );
		  gpioWrite( LED2, ledValue2 );
		  gpioWrite( LED3, ledValue3 );
      }
	   // Si no se cumple el delay pooling de botones.
      else {
    	  if (gpioRead( BUTTON3 ) == OFF) {
    		  delayTime = 750;
    		  delayConfig( &NonBlockingDelay, delayTime );
    	  }
		  if (gpioRead( BUTTON2 ) == OFF) {
			  delayTime = 150;
			  delayConfig( &NonBlockingDelay, delayTime );
		  }
		  if (gpioRead( BUTTON1 ) == OFF) dirValue = TRUE;
		  if (gpioRead( BUTTON4 ) == OFF) dirValue = FALSE;
      }

   }

   return 0;
}