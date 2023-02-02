//This program is the first go with working ADC and Main loop
//In theroy this program should work

#include <p18F252.h> // PIC device specific definitions
#include <xc.h>     // XC8 compiler specifics
#include <stdio.h> // standard C I/O library
#include <stdlib.h> // standard C library

//Configuration statements if required

#pragma config OSC = HS //Oscillator = Set High Speed
#pragma config PWRT = OFF //Power Up Timer disabled
#pragma config WDT = OFF //Watchdog timer disabled
#pragma config LVP = OFF //Low Voltage ICSP disabled

//Definitions

#define _XTAL_FREQ 24000000 // external oscillator frequency in Hertz, used by __delay_ms

//Define a helpful name for the pin we are using
#define OUTPUT PORTBbits.RB0

//Output port setup
#define OUTPUT_CFG TRISB

//Global Variables

//Function declarations

void delay(void);
void config_ADC(void);
void leftADC(void);
void rightADC(void);
void midADC(void);
void motorControl(int,int,int,int);


int leftSensor;
int midSensor;
int rightSensor;
int motorRdirection = 0;
int motorRspeed = 0;
int motorLdirection = 0;
int motorLspeed = 0;
int sensorValue;


//Main

void main(void){
	TRISB = 0x00;
	//Sets the bits on portB to 0 so the variable watch when simulating resets so we can see the change.
	PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    PORTBbits.RB2 = 0;
    PORTBbits.RB3 = 0;

	    while(1){
			TRISB = 0x00; //set port B as output
			config_ADC(); //Load the ADC
			leftADC(); //calls function
			config_ADC(); //Load the ADC
			midADC(); //calls function
			config_ADC(); //load ADC
			rightADC(); //calls for the ADC value from right sensor
			
			sensorValue = leftSensor + midSensor + rightSensor; 

			switch(sensorValue){
				case(000):
					motorRdirection = 1; //turn right motor on
					motorRspeed = 0; //motor On
					motorLdirection = 0; //Motor in reverse
					motorLspeed = 0; //motor on On

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(100):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 1;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(010):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(001):
					motorRdirection = 1;
					motorRspeed = 1;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(101):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(110):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(011):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;

				case(111):
					motorRdirection = 1;
					motorRspeed = 0;
					motorLdirection = 1;
					motorLspeed = 0;

					motorControl(motorRdirection, motorRspeed, motorLdirection, motorLspeed);
					break;
        }
    }
	return 0;
}

void config_ADC(void){ //ADC setup
	TRISA = 0xFF; // port A, all bits, inputs
	ADCON1bits.ADFM = 0; // left justification
	ADCON1bits.PCFG = 0b0000; // Port A is set as analogue
	ADCON1bits.ADCS2 = 0;
	ADCON0bits.ADCS1 = 1;
	ADCON0bits.ADCS0 = 0; // ADC clock = Fsoc/32

}

void leftADC(void){
    ADCON0bits.ADON = 1; //Turns on ADC
	ADCON0bits.CHS = 0b000; //(0b000 = channel 0) selects channel
	delay();
	PORTC = 0;
	GO_DONE = 1; //start conversion
	while(GO_DONE); //wait for conversion
	if (ADRESH < 128){
		leftSensor = 100; //store value in PORTC
	}
	return leftSensor;
}

void midADC(void){
	ADCON0bits.ADON = 1; //Turns on ADC
    ADCON0bits.CHS = 0b001; //(0b000 = channel 1) selects channel 2
	delay();
	PORTC = 0;
	GO_DONE = 1; //start conversion on channel 1
	while(GO_DONE); //wait for conversion
	if(ADRESH < 128){
		midSensor = 10;
	}
	return midSensorSensor;
}


void rightADC(void){
	ADCON0bits.ADON = 1; //Turns on ADC
	ADCON0bits.CHS = 0b000; //(0b010 = channel 2) selects channel 2
	delay();
	PORTC = 0;
	GO_DONE = 1; //start conversion on channel 0
	while(GO_DONE); //wait for conversion
	if(ADRESH < 128){
		rightSensor = 1;
	}
	return rightSensor;
}

void motorControl(int motorRdirection,int motorRspeed,int motorLdirection,int motorLspeed){
    PORTBbits.RB0 = motorRdirection;
    PORTBbits.RB1 = motorRspeed;
    PORTBbits.RB2 = motorLdirection;
    PORTBbits.RB3 = motorLspeed;//Was setting as the value of motorRspeed instead
}    


//The delay routine. A very basic delay using nested for loops.

void delay(void){
	unsigned int a;
	unsigned int b;
		for(a=0;a<50;a++){
			for(b=0;b<100;b++){
			}
		}
}
