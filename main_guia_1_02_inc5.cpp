//=====[Librerias]=============================================================
#include "mbed.h"
#include "arm_book_lib.h" 

//=====[Funcion main, punto de entrada al prender o resetear.]========
/**
* Inicializa y declara los outputs/inputs e implemente el comportmaiento del sistmea.
* @param ninguno
* @return el retorno de un valor significa el exito de la corrida del programa. 
*/
int main()
{
    //=====[Declaracion e inicializacion de los objetos publicos globales]===============
    DigitalIn gasDetector(D5); /**< Cambio el pin de salida digital */

    DigitalOut alarmLed(LED2); /**< Cambio el led usado */

    gasDetector.mode(PullDown); 


    alarmLed = OFF;
    int n = 0;

    while (true) {
        n++; 
        printf("Iteracion numero %d \n", n); // sigo imprimiendo iteraciones por consola
        if ( gasDetector == ON ) {
            alarmLed = ON; 
        }
        
        if ( gasDetector == OFF ) {
            alarmLed = OFF;
        }
    }
  
  return 0;
}
