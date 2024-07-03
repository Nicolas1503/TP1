#include "mbed.h"
#include "arm_book_lib.h"

#define LED1 PA_1
#define BUTTON1 PA_2

int main()
{
    DigitalIn BOTON(BUTTON1);

    DigitalOut PinRele(LED1);

    BOTON.mode(PullUp);

    PinRele = OFF;

    while (true) {
        if ( BOTON == ON ) {
            PinRele = ON;
        }
        
        if ( BOTON == OFF ) {
            PinRele = OFF;
        }
    }
    
}
