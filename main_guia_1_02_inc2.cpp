#include "mbed.h" // inclusión de libreria mbed.h
#include "arm_book_lib.h" // inclusión de libreria arm_book_lib.h

int main()
{
    DigitalIn gasDetector(D2); // (llamada al constructor) declaro pin D2 como entrada y le asocio el nombre gasDetector

    DigitalOut alarmLed(LED1); // (llamada al constructor) declaro LED1 como salida y le asocio el nombre alarmLed

    gasDetector.mode(PullDown); // utilizo el metodo "mode" del objeto gasDetector para configurarle la resistencia de pulldown


    alarmLed = OFF; // la clase tiene el operador "=" sobrecargado para asociarle un estado al objeto
    int n = 0; // inicializamos un int para usarlo de contador

    while (true) { // loop que se repetira continuamente en la placa
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
