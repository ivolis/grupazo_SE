#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    DigitalIn gasDetector(D2); // declaro pin D2 como entrada y le asocio el nombre gasDetector (constructor)
    // En C se asocia gpio_t a D2 como tipo de dato
    DigitalOut alarmLed(LED1); // declaro LED1 como salida (constructor)

    gasDetector.mode(PullDown); // utilizo el metodo "mode" del objeto gasDetector para configurarle la resistencia de pulldown
    // en este caso hay que declarar el prototipo y la implementacion

    alarmLed = OFF; // la clase tiene el operador "=" sobrecargado para asociarle un estado al objeto
    int n = 0; // inicializamos un int para usarlo de contador

    while (true) {
        n++; // incrementamos el contador
        printf("Iteracion numero %d \n", n); // se imprime el contador
        if ( gasDetector == ON ) {
            alarmLed = ON; // si se detecta un 1 en el pin D2, se prende LED1
        }
        
        if ( gasDetector == OFF ) {
            alarmLed = OFF; // idem pero con 0
        }
    }
}