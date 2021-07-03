/*=============================================================================
 * Program: Ejercicio_1
 * Date: 2021/06/30
 *===========================================================================*/

//#include "app.h"
#include "sapi.h"
delay_t myDelay;

int main( void )
{
   boardConfig();
   delayConfig( &myDelay, 150 );
   int estado = 0;
   int sentido = 1; // 0 Izquierda, 1 Derecha

  while( TRUE ) {
     if( delayRead( &myDelay ))
        if (sentido)
        {
          switch (estado){
             case 0:{
                  gpioWrite(LEDB, ON);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, OFF);
                  estado = 1;
                    }
                  break;
            case 1:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, ON);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, OFF);
                  estado = 2;
                   }
                  break;
            case 2:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, ON);
                  gpioWrite(LED3, OFF);
                  estado = 3;
                   }
                  break;
            case 3:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, ON);
                  estado = 0;
                   }
                 break;
                     }
                  }
         else {
            switch (estado){
             case 0:{
                  gpioWrite(LEDB, ON);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, OFF);
                  estado = 3;
                    }
                  break;
            case 1:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, ON);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, OFF);
                  estado = 0;
                   }
                  break;
            case 2:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, ON);
                  gpioWrite(LED3, OFF);
                  estado = 1;
                   }
                  break;
            case 3:{
                  gpioWrite(LEDB, OFF);
                  gpioWrite(LED1, OFF);
                  gpioWrite(LED2, OFF);
                  gpioWrite(LED3, ON);
                  estado = 2;
                   }
                  break;
                     }
                  }
      if (gpioRead( TEC1 ) == 0 && sentido != 0)
         {sentido = 0;
            estado --;
            if (estado == -1)
               estado =3;}

      if (gpioRead( TEC2 ) == 0)
         delayConfig( &myDelay, 150 );

      if (gpioRead( TEC3 ) == 0)
         delayConfig( &myDelay, 750 );

      if (gpioRead( TEC4 ) == 0 && sentido != 1)
         {sentido = 1;
            estado ++;
            if (estado == 4)
               estado =0;}

      }
  return 0;
}
