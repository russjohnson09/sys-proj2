#include "proj2.h"

#include <time.h>
#include<stdio.h>
#include<stdlib.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t reading_done;
extern pthread_cond_t writing_done;
	
extern int  current;			 
extern char buffer[];

void process(char);

int linepos = 0;

void * controller(void * arg)
{
    char ch;
    int i = 0;
    int j;

    char command[7];

    while(1) {
        if (linepos == 30){
            printf("\n");
            linepos = 0;
        }
        ch = bufferReader();
        if (ch!=EOF)
            process(ch);                
        else
            break;
        linepos++;
    }
	return 0;
}

void process (char ch) {
    if (isprint(ch))
        if (ch == '[')
            execComm();
        else
            printf("%c", ch);

    else
        printf("\nError: non-displayable character\n");

}

void execComm (){
    char comm[5];
    int i;
    char ch;
    for (i = 0; i < 5; i++) {
        ch = bufferReader();
        comm[i] = ch;
    }
    if (bufferReader() == ']'){
        if (!strcmp(comm, "NEWLN")){
            printf("\n");
        }
        else if (!strcmp(comm, "DELAY")){
            sleep(1);
        }
        else if (!strcmp(comm, "DBNLN")){
            printf("\n\n");
        }
        else{
            printf("\nError: unrecognized command\n");
        }
    }
}


void displayText (char line []){
    printf("%s\n", line);
}


// bufferReader() returns one character from the shared buffer 

char bufferReader()
{
   	char ch;
   
   	pthread_mutex_lock( &mutex );

	// wait if the next set of characters is not ready yet
   	if (current == 7) 
		pthread_cond_wait( &writing_done, &mutex );
   	ch = buffer[current++];

	// signal to writer if the current set of characters is finished  
   	if (current == 7)
		pthread_cond_signal(&reading_done);

   	pthread_mutex_unlock( &mutex );

   	return ch;
}

