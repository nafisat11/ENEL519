/*
 * File:   main.c
 * Author: Nafisa
 *
 * Created on September 29, 2020, 11:02 AM
 */


#include "xc.h"

void main(void) {
    TRISAbits.TRISA0 = 1; //Sets RA0-GPIO2 as input
    TRISAbits.TRISA1 = 1; //Sets RA1-GPIO3 as input
    TRISAbits.TRISA4 = 1; //Sets RA4-GPIO10 as input
    TRISAbits.TRISA6 = 1; //Sets RA6-GPIO14 as input
    
    TRISBbits.TRISB0 = 0; //Sets RB0-GPIO4 as output
    TRISBbits.TRISB1 = 0; //Sets RB1-GPIO5 as output
    TRISBbits.TRISB2 = 0; //Sets RB2-GPIO6 as output
    TRISBbits.TRISB4 = 0; //Sets RB4-GPIO9 as output
    TRISBbits.TRISB7 = 0; //Sets RB7-GPIO11 as output
    TRISBbits.TRISB8 = 0; //Sets RB8-GPIO12 as output
    TRISBbits.TRISB9 = 0; //Sets RB9-GPIO13 as output
    TRISBbits.TRISB12 = 0; //Sets RB12-GPIO15 as output
    
    while(1)
    {
        if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA4 == 0 && PORTAbits.RA6 == 1))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 0; //Sets RB1 LOW
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA4 == 1 && PORTAbits.RA6 == 0))
        {
            LATBbits.LATB0 = 0; //Sets RB0 LOW
            LATBbits.LATB1 = 0; //Sets RB1 LOW
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA4 == 1 && PORTAbits.RA6 == 1))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 0; //Sets RB1 LOW
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA4 == 0 && PORTAbits.RA6 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 1; //Sets RB1 HIGH
            LATBbits.LATB2 = 1; //Sets RB2 HIGH
            LATBbits.LATB4 = 1; //Sets RB4 HIGH
            LATBbits.LATB7 = 1; //Sets RB7 HIGH
            LATBbits.LATB8 = 1; //Sets RB8 HIGH
            LATBbits.LATB9 = 1; //Sets RB9 HIGH
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA4 == 0 && PORTAbits.RA6 == 1))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 1; //Sets RB1 HIGH
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA4 == 1 && PORTAbits.RA6 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 1; //Sets RB1 HIGH
            LATBbits.LATB2 = 1; //Sets RB2 HIGH
            LATBbits.LATB4 = 1; //Sets RB4 HIGH
            LATBbits.LATB7 = 1; //Sets RB7 HIGH
            LATBbits.LATB8 = 1; //Sets RB8 HIGH
            LATBbits.LATB9 = 1; //Sets RB9 HIGH
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA4 == 1 && PORTAbits.RA6 == 1))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 0; //Sets RB1 LOW
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else if((PORTAbits.RA0 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA4 == 0 && PORTAbits.RA6 == 0))
        {
            LATBbits.LATB0 = 1; //Sets RB0 HIGH
            LATBbits.LATB1 = 1; //Sets RB1 HIGH
            LATBbits.LATB2 = 1; //Sets RB2 HIGH
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
        else
        {
            LATBbits.LATB0 = 0; //Sets RB0 LOW
            LATBbits.LATB1 = 0; //Sets RB1 LOW
            LATBbits.LATB2 = 0; //Sets RB2 LOW
            LATBbits.LATB4 = 0; //Sets RB4 LOW
            LATBbits.LATB7 = 0; //Sets RB7 LOW
            LATBbits.LATB8 = 0; //Sets RB8 LOW
            LATBbits.LATB9 = 0; //Sets RB9 LOW
            LATBbits.LATB12 = 0; //Sets RB12 LOW
        }
    }
    return;
}
