#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * controller();
char bufferReader ();
void execComm ();
void displayText (char ch);
void * devDriver(void * arg);
void bufferWriter(char data[]) ;

