#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * controller();

char bufferReader ();
// returns the next input character from the buffer if the buffer is not empty.

// executes a command that is given as the parameter. If parameter comm contains string “NEWLN”, for example, this function will print the newline character on the screen.
void execComm ();

//displays on the screen text (including error messages) that is given as the parameter. Since the VDU can display up to thirty characters per line, the length of array line should not exceed the maximum. 
void displayText (char line []);

//thread2.c

void * devDriver(void * arg);
// writes a block of seven characters into the buffer as soon as the buffer becomes empty. 
void bufferWriter(char data[]) ;

