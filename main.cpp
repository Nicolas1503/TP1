#include "mbed.h"
#include "arm_book_lib.h"

#define LED1 PA_1
#define BUTTON1 PA_2
#define USBTX PB_6
#define USBRX PB_7
#define A0 PA_0

DigitalIn BOTON(BUTTON1);
DigitalOut PinRele(LED1);

UnbufferedSerial uartUsb(USBTX, USBRX, 9600);

AnalogIn potentiometer(A0);

bool regadorState    = OFF;
bool Overtimeregador = OFF;

bool overTimeState = OFF;

float potentiometerReading = 0.0;
float lm35TempC = 0.7;

void inputsInit();
void outputsInit();

void RegadorSetting();
void RegadorStart();
void RegadorStop();
void uartTask();

int main(void)
{
    inputsInit();
    outputsInit();

    while (true) {

        //RegadorSetting();
        //RegadorStart();
        //RegadorStop();
        uartTask();
        //delay(TIME_INCREMENT_MS);

        /*if ( BOTON == ON ) {
            PinRele = ON;
            serial_port.write("1", 1);
        }
        
        if ( BOTON == OFF ) {
            PinRele = OFF;
            serial_port.write("0", 1);
        }
        */
    }
    
}
void inputsInit()
{
   BOTON.mode(PullUp);
}

void outputsInit()
{
    PinRele = OFF;
}

void uartTask()
{
    char receivedChar = '\0';
    char str[100];
    int stringLength;
    if( uartUsb.readable() ) {
        uartUsb.read( &receivedChar, 1 );
        switch (receivedChar) {
        case 'p':
        case 'P':
            potentiometerReading = potentiometer.read();
            sprintf ( str, "Potentiometer: %.2f\r\n", potentiometerReading );
            stringLength = strlen(str);
            uartUsb.write( str, stringLength );
            break;

        case 'f':
        case 'F':
            sprintf ( str, "Temperature: %.2f \xB0 C\r\n", lm35TempC );
            stringLength = strlen(str);
            uartUsb.write( str, stringLength );
            break;

        }
    }
}
