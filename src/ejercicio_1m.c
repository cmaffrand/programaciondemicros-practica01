/*=============================================================================
 * Authors: Carlos Maffrand 	<carlosmaffrand5@gmail.com>
 *			Hernan Gomez Molino	<hernangomezmolino@gmail.com>
 * Date: 2021/07/02
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "ejercicio_1m.h"

/*=====[Definition macros of private constants]==============================*/

const gpioMap_t secuencia[] = {LEDB, LED1, LED2, LED3};
const uint8_t ultimoLed = sizeof(secuencia)/sizeof(gpioMap_t);

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
