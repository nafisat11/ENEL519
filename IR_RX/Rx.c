/* 
 * File:   Rx.c
 * Author: Matteo M
 *
 * Created on December 11, 2020, 12:35 PM
 */

#include <p24F16KA101.h>
#include "UART2.h"
#include<stdbool.h>

#define BIT_SEQUENCE_LENGTH 32

static uint16_t power[BIT_SEQUENCE_LENGTH] =      {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1};
static uint16_t channelUp[BIT_SEQUENCE_LENGTH] =  {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1};
static uint16_t channelDown[BIT_SEQUENCE_LENGTH]= {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1};
static uint16_t volumeUp[BIT_SEQUENCE_LENGTH]=    {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1};
static uint16_t volumeDown[BIT_SEQUENCE_LENGTH]=  {1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1};

bool CN_flag = false;
bool bit_sequence_flag = false;
bool start_sequence_flag = false;
uint16_t curr_timer_count = 0;

uint16_t bit_sequence[BIT_SEQUENCE_LENGTH];

int j = 0;

void initializeIO()
{  
    // turn timer off
    T2CONbits.TON = 0;
    // Selects the internal clock as the timer clock source
    T2CONbits.TCS = 0;
    //Sets prescaler to 1
    T2CONbits.TCKPS = 00;
    //Sets Timer2 value to 0
    TMR2 = 0;
    // Sets interrupt priority level as maximum
    IPC4bits.CNIP = 7;
    
    CNEN1bits.CN6IE = 1;
    //Enables the change notification interrupt 
    IEC1bits.CNIE = 1;
    //Clearing the interrupt bit before operation
    IFS1bits.CNIF = 0;
    
    //Initializes  pin B9 as an output
    TRISBbits.TRISB9 = 0;
    //Sets the initial output to 0 
    LATBbits.LATB9 = 0 ;
 
    //Sets pins A2, A4, and B4 as button inputs
    TRISBbits.TRISB2 = 1;  
}

// Function used to compare elements at the same index of 2 arrays
bool array_comp(uint16_t arr1[BIT_SEQUENCE_LENGTH], uint16_t arr2[BIT_SEQUENCE_LENGTH])
{
    int i;
    for(i = 0; i < 32; i++)
    {
        if(arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

//Decoding sequence used to compare received signal with binary encoded signal
void decode_bitsequence(uint16_t bit_sequence[BIT_SEQUENCE_LENGTH])
{
    
    if(array_comp(bit_sequence, power) == true)
        Disp2String("TV ON/Off command received                     0xE0E040BF\r");
    else if(array_comp(bit_sequence, channelUp) == true)
        Disp2String("Channel mode: Channel up received              0xE0E048B7\r");
    else if(array_comp(bit_sequence, channelDown) == true)
        Disp2String("Channel mode: Channel down received            0xE0E008F7\r");
    else if(array_comp(bit_sequence, volumeUp) == true)
        Disp2String("Volume mode: Volume up received                0xE0E0E01F\r");
    else if(array_comp(bit_sequence, volumeDown) == true)
        Disp2String("Volume mode: Volume down received              0xE0E0D02F\r");
    else
        Disp2String("Nothing                                                  \r");
}

//function used to decode each portion of a signal to a corresponding bit sequence
void process_timer()
{
    // Enters function each time a falling edge change notification has occurred
    if(CN_flag == true) 
        {
            //checks until start pulse is received
            if(curr_timer_count > 8800 && curr_timer_count < 9200)
            {
                start_sequence_flag = true;
                return;
            }
            //once start pulse is received, begin decoding signal into bits
            if(start_sequence_flag == true)
            {
                if(curr_timer_count > 900 && curr_timer_count < 1300)
                    bit_sequence[j] = 0;
                if(curr_timer_count > 2000 && curr_timer_count < 2400)
                    bit_sequence[j] = 1;
                j++;
                // once a full bit sequence is read, set flag to notify completion
                if(j == BIT_SEQUENCE_LENGTH)
                {
                    bit_sequence_flag = true;
                    j = 0;
                    start_sequence_flag = false;
                }
            }
            //once bit sequence is complete, determine command associated with bit sequence
            if(bit_sequence_flag == true)
            {
                decode_bitsequence(bit_sequence);
                bit_sequence_flag = false;
            }
            CN_flag = false; 
        }
}

// change notification ISR used to get the amount of time that has passed between each falling edge of the signal
void __attribute__((interrupt, no_auto_psv))_CNInterrupt(void) 
{
    if(PORTBbits.RB2 == 0)
    {
        T2CONbits.TON = 0;
        curr_timer_count = TMR2/4;
        CN_flag = true;
        TMR2 = 0;
        T2CONbits.TON = 1;
    }
    IFS1bits.CNIF = 0;
}