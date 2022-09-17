//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================
#define TIME_INCREMENT_MS                       10
#define DEBOUNCE_BUTTON_TIME_MS                 40

//=====[Declaration of public data types]======================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

DigitalIn enterButton(BUTTON1);
DigitalOut ledButtomUp(LED1);
DigitalOut ledButtomRisingOrFalling(LED2);
DigitalOut ledButtomDown(LED3);

int accumulatedDebounceButtonTime     = 0;
int numberOfEnterButtonReleasedEvents = 0;
buttonState_t enterButtonState;


//=====[Declarations (prototypes) of public functions]=========================


void inputsInit();
void outputsInit();

void statePrint();


void debounceButtonInit();
bool debounceButtonUpdate();


//=====[Main function, the program entry point after power on or reset]========
int main()
{
    inputsInit();
    outputsInit();
    while (true) {
        statePrint();
        delay(TIME_INCREMENT_MS);
    }
}

//=====[Implementations of public functions]===================================

void inputsInit()
{
    debounceButtonInit();
}


void outputsInit()
{
    ledButtomUp = OFF;
    ledButtomRisingOrFalling = OFF;
    ledButtomDown = OFF;
}



void statePrint()
{
    bool enterButtonReleasedEvent = debounceButtonUpdate(); // No estamos usando el booleano pero llama a la funcion que acutaliza el boton.
    printf("ESTADO: %d \n", enterButtonState);

    switch( enterButtonState ) {

    case BUTTON_UP:
        ledButtomUp = ON;
        ledButtomRisingOrFalling = OFF;
        ledButtomDown = OFF;
        break;

    case BUTTON_FALLING:
        ledButtomRisingOrFalling = ON;
        ledButtomUp = OFF;
        ledButtomDown = OFF;
        break;

    case BUTTON_DOWN:
        ledButtomDown = ON;
        ledButtomRisingOrFalling = OFF;
        ledButtomUp = OFF;
        break;

    case BUTTON_RISING:
        ledButtomRisingOrFalling = ON;
        ledButtomUp = OFF;
        ledButtomDown = OFF;
        break;

    default:
        printf("ERROR\n");
        break;
    }
}

void debounceButtonInit()
{
    if( enterButton ) {
        enterButtonState = BUTTON_DOWN;
    } else {
        enterButtonState = BUTTON_UP;
    }
}

bool debounceButtonUpdate()
{
    bool enterButtonReleasedEvent = false;
    switch( enterButtonState ) {

    case BUTTON_UP:
        if( enterButton ) {
            enterButtonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( enterButton ) {
                enterButtonState = BUTTON_DOWN;
            } else {
                enterButtonState = BUTTON_UP;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !enterButton ) {
            enterButtonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( !enterButton ) {
                enterButtonState = BUTTON_UP;
                enterButtonReleasedEvent = true;
            } else {
                enterButtonState = BUTTON_DOWN;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
    return enterButtonReleasedEvent;
}
