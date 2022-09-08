
#include "mbed.h" // inclusión de libreria mbed.h
#include "arm_book_lib.h" // inclusión de libreria arm_book_lib.h

int main()
{

    // Init Input.
    gpio_t gpio_in;
    gpio_init_in(&gpio_in, D2);
    gpio_mode(&gpio_in, PullDown);

    // Init output
    gpio_t gpio_out;
    gpio_init_out(&gpio_out, LED1);

    DigitalOut alarmLed(LED1);

    printf("hello world\n");

    alarmLed = OFF;
    int counter = 0;
    while (true) {

        // If input is ON, turn ON the output
        if ( gpio_read(&gpio_in) == ON ) {
            gpio_write(&gpio_out, ON);
        }
        
        // If input is OFF, turn OFF the output
        if ( gpio_read(&gpio_in) == OFF ) {
            gpio_write(&gpio_out, OFF);
        }
        printf("%i\n", counter);
        counter ++;
    }
}
