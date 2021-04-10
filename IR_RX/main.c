/*
 * File:   main.c
 * Author: Matteo M
 *
 * Created on December 11, 2020, 6:11 PM
 */

#include <xc.h>
//#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <libpic30.h>

#include "ChangeClk.h"
#include "Rx.h"

//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled


// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //

#define BIT_SEQUENCE_LENGTH 32
/*
 * 
 */



extern volatile uint16_t curr_timer_count;
extern volatile bool CN_flag;

int main(void) {
    NewClk(8);
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    initializeIO();
    while(1)
    {
        Idle();
        process_timer();
    }
    return 0;
}


    
    
