#include <xc.h>
//#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "IR.h"
#include <libpic30.h>
#include "ChangeClk.h"
#include "UART2.h"
#define BIT_SEQUENCE_LENGTH 32

static bool flagVolChan = 0; // flags used to switch between volume and channel
static bool flagONOFF = 0;// used to switch between displaying that the TV is on and off. Assumes TV starts out being on

// arrays that contain the bit values for the respective instructions
static bool power[BIT_SEQUENCE_LENGTH] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1};
static bool channelUpArr[BIT_SEQUENCE_LENGTH] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1};
static bool channelDownArr[BIT_SEQUENCE_LENGTH] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1};
static bool volumeUpArr[BIT_SEQUENCE_LENGTH] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
static bool volumeDownArr[BIT_SEQUENCE_LENGTH] = {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1};

//creates the carrier at 38kHz and specific timing which is sent as us
void carrier(uint16_t cycle) {
    uint16_t newCycle = (cycle)*5 / 66;// used to create specific timing that is sent
    uint16_t i = 0;
    while (i < newCycle) {// used to produce a 38 kHz signal
        __delay32(30);
        LATBbits.LATB9 = !LATBbits.LATB9;
        i++;
    }
}

//creates start bit 
void startBit() {
    carrier(4500); // sends 4.5 ms for timing for signal
    LATBbits.LATB9 = 0;
    __delay32(18000); // delays for 4.5 ms at 0
}

// makes a 1 bit pulse
void oneBit() {
    carrier(560); // sends 0.56 ms for timing for signal
    LATBbits.LATB9 = 0;
    __delay32(6760); // delays for 1.69 ms at 0
}

//makes a 0 bit pulse
void zeroBit() {
    carrier(560); // sends 0.56 ms for timing for signal 
    LATBbits.LATB9 = 0;
    __delay32(2240); // delays for 0.56 ms at 0
}


//cycles through power array to produce the correct bit sequence to turn the TV on and off
void powerCycle() {
    uint16_t i;
    startBit(); // calls the start bit
    for (i = 0; i < BIT_SEQUENCE_LENGTH; i++) { // cycles through the array to create a 1 or 0 bit
        if (power[i])
            oneBit();
        else
            zeroBit();
    }
    zeroBit(); // calls stop bit
}

//cycles through volume up array to produce the correct bit sequence to turn the volume up
void volumeUp() {
    uint16_t i;
    startBit(); // calls the start bit
    for (i = 0; i < BIT_SEQUENCE_LENGTH; i++) {  // cycles through the array to create a 1 or 0 bit
        if (volumeUpArr[i])
            oneBit();
        else
            zeroBit();
    }
    zeroBit();
}

//cycles through volume down array to produce the correct bit sequence to turn the volume down
void volumeDown() {
    uint16_t i;
    startBit(); // calls the start bit
    for (i = 0; i < BIT_SEQUENCE_LENGTH; i++) {  // cycles through the array to create a 1 or 0 bit
        if (volumeDownArr[i])
            oneBit();
        else
            zeroBit();
    }
    zeroBit();// calls stop bit
}

//cycles through channel up array to produce the correct bit sequence to turn the channel up
void channelUp() {
    uint16_t i;
    startBit(); // calls the start bit
    for (i = 0; i < BIT_SEQUENCE_LENGTH; i++) {  // cycles through the array to create a 1 or 0 bit
        if (channelUpArr[i])
            oneBit();
        else
            zeroBit();
    }
    zeroBit(); // calls stop bit
}

//cycles through channel down array to produce the correct bit sequence to turn the channel down
void channelDown() {
    uint16_t i;
    startBit(); // calls the start bit
    for (i = 0; i < BIT_SEQUENCE_LENGTH; i++) {  // cycles through the array
        if (channelDownArr[i])
            oneBit();
        else
            zeroBit();
    }
    zeroBit(); // calls stop bit
}

// initialized the inputs and outputs
void initializeIO() {
    T2CONbits.TCS = 0; // Selects internal clock as the timer 
    T2CONbits.T32 = 0; // sets Timer2 and Timer3 separate
    T2CONbits.TCS = 0; // Continue timer operation when in idle mode

    IPC1bits.T2IP = 5; // Sets interrupt priority level to 5
    IPC4bits.CNIP = 7; // Sets interrupt priority levels to 7

    CNEN1bits.CN0IE = 1;
    CNEN1bits.CN1IE = 1;
    CNEN2bits.CN30IE = 1;

    //Enables timer interrupt 
    IEC0bits.T2IE = 1;
    //Enables the change notification interrupt 
    IEC1bits.CNIE = 1;

    //Clears interrupt bit before operation
    IFS0bits.T2IF = 0;
    IFS1bits.CNIF = 0;

  
    TRISAbits.TRISA2 = 1; //Initializes  pin A2 as an input
    TRISAbits.TRISA4 = 1; //Initializes  pin A4 as an input 
    TRISBbits.TRISB4 = 1; //Initializes  pin B4 as an input 
    TRISBbits.TRISB9 = 0; //Initializes  pin B9 as an output 
    TRISBbits.TRISB8 = 0; //Initializes  pin B8 as an output 
    LATBbits.LATB8 = 0;   //sets pin to 0 

    CNPU2bits.CN30PUE = 1; // turns on pull up resistor for A2
    CNPU1bits.CN0PUE = 1; // turns on pull up resistor for A4
    CNPU1bits.CN1PUE = 1; // turns on pull up resistor for B4

}

//uses CN interrupt to detect if a button is pressed and changed between the states.
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void) {
    NewClk(8); // sets clock to 8 MHz as all cycles calculated for it and for UART display
    uint16_t i = 0;
    while (PORTBbits.RB4 == 0 && i <= 3000) { //checks to see if PB3 is pressed for 3 seconds or more
        __delay32(4000);
        i++;
    }

    if (i >= 3000) { // goes through power instructions if PB3 pressed for 3 seconds or more
        Disp2String("\rPB3 is pressed for 3 sec or more  ");
        powerCycle(); // calls function to turn on/off tv
        if (flagONOFF) {// display instruction assumes TV starts out being on
            Disp2String(" TV ON                     ");
            flagONOFF = !flagONOFF;
        } else {
            Disp2String(" TV OFF                    ");
            flagONOFF = !flagONOFF;
        }
    }
    else if (i >= 1 && i < 3000) { // switches between volume and power if PB3 is pressed for less than 3 seconds
        Disp2String("\rPB3 is pressed for less than 3 sec  ");
        flagVolChan = !flagVolChan;
        if (!flagVolChan) { // intitially starts out in channel mode
            Disp2String(" Switched to channel mode");
        } else {
            Disp2String(" Switched to volume mode ");
        }
    }       
    else { // changes volume/channel up and down if PB1 or PB2 is pressed depending on which mode is selected from PB3
        if (!flagVolChan) {
            while (PORTAbits.RA2 == 0) { 
                Disp2String("\rPB1 is pressed  ");
                Disp2String(" Channel mode: Channel Up                     ");
                channelUp(); // calls function to increase channel
                __delay32(200000); // 50 ms time used between adjacent transmissions
            }
            while (PORTAbits.RA4 == 0) {
                Disp2String("\rPB2 is pressed  ");
                Disp2String(" Channel mode: Channel down                   ");
                channelDown(); // calls function to decrease channel
                __delay32(200000);  // 50 ms time used between adjacent transmissions
            }
        } else {
            while (PORTAbits.RA2 == 0) {
                Disp2String("\rPB1 is pressed  ");
                Disp2String(" Volume mode: Volume Up                     ");
                volumeUp(); // calls function to increase volume
                __delay32(200000);  // 50 ms time used between adjacent transmissions
            }
            while (PORTAbits.RA4 == 0) {
                Disp2String("\rPB2 is pressed  ");
                Disp2String(" Volume mode: Volume down                   ");
                volumeDown(); // calls function to decrease volume
                __delay32(200000);  // 50 ms time used between adjacent transmissions
            }
        }
    }
    NewClk(32); // switches clock back to 32 kHz when done to conserve power
    IFS1bits.CNIF = 0; // clears interrupt flag

}
