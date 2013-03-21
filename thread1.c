#include "proj2.h"

extern pthread_mutex_t mutex;
extern pthread_cond_t reading_done;
extern pthread_cond_t writing_done;
	
extern int  current;			 
extern char buffer[];

void * controller(void * arg)
{
	// igore the parameter arg which is not useful in this project

    char chars[30];
    char command[7];
    int i;
    int j;
    char ch;
    while(1){
        for(i=0;i<30;i++){
            ch=bufferReader();
            if(!isprint(ch)){
                printf("\nError: non-displayable character\n");
                continue;
            }
            if (ch == '['){
                //displayText(chars);

                j = 0;
                while(1){
                    ch = bufferReader();
                    if (j > 6){
                        break;
                    } 
                    if (ch == ']'){
                        execComm(command);
                        break;
                    }
                    command[j] = ch;
                    j++;
                }
            }
            if (ch!=EOF)
                chars[i] = ch;
            else{
                chars[i] = ch;
                displayText(chars);
                return 0;
            }
        }
        displayText(chars);
    }

/*
    int i;
    char ch;
    for(i=0; i<30; i++) {
        ch = bufferReader();
        printf("%c", ch);
    }
*/

	// use bufferReader() to receive one character from the buffer
	// shared between threads and process it; do this repeatedly
	// until EOF is encountered. also define functions displayText() 
	// and execComm() to perform the required actions.

	return 0;
}

void execComm (char comm []){
    if (!strcmp(comm,"[NEWLNN]"))
        printf("\n");
    else
        printf("\n{Error: unrecognizable command}\n");
}

//displays on the screen text (including error messages) that is given as the parameter. Since the VDU can display up to thirty characters per line, the length of array line should not exceed the maximum. 
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

