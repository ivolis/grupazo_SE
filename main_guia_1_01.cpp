#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    DigitalIn gasDetector(D2);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);

    alarmLed = OFF;
    int n = 0; // inicializo el contador de iteraciones

    while (true) {
        n++; // aumento en 1 el contador de iteraciones
        printf("Iteracion numero %d \n", n); // imprimo por consola un mensaje
        if ( gasDetector == ON ) {
            alarmLed = ON;
        }
        
        if ( gasDetector == OFF ) {
            alarmLed = OFF;
        }
    }
}
