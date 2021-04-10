/* 
 * File:   main.c
 * Author: marwa
 *
 * Created on November 28, 2020, 1:28 PM
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
#include "IR.h"
#include "UART2.h"


//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled


// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //
/*
 * 
 */


int main(int argc, char** argv) {
    NewClk(32); // sets clock to 32kHz to intitially conserve power
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    initializeIO();

    while (1) {
        Idle(); // stays idle to conserve power when nothing is triggered
    }
    return (EXIT_SUCCESS);
}
