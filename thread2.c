#include "proj2.h"

extern pthread_mutex_t mutex;		
extern pthread_cond_t reading_done;
extern pthread_cond_t writing_done;

extern int  current;
extern char buffer[];

void * devDriver(void * arg)
{

    int i;
    int n = 0;
    char ch;
    char buff[7];

    while(1){
        for (i=0;i<7;i++){
            ch = getchar();
            if (ch!= EOF)
                buff[i] = ch;
            else {
                buff[i] = ch;
                bufferWriter(buff);
                return 0;
            }
        }
            bufferWriter(buff);
    }


/*    while(n < 1) {

        for(i=0;i<7;i++){
            scanf("%c", &ch);
            printf("%c",ch);
//            ch = getchar();
            buff[i] = ch;
            //ch = 
        }
        bufferWriter(buff);
        n++;
    }
    */

	// read seven characters from the input file into an array
	// and use bufferWritter() with that array as the parameter
	// to store those characters in the buffer shared between 
	// threads; do this repeatedly until EOF is reached.  
	// note that EOF needs to be stored in the buffer as well. 

	return 0;
}


// bufferWriter() stores the seven characters in array data into the  
// shared buffer

void bufferWriter(char data[])
{
   	pthread_mutex_lock(&mutex);

	// wait if the current set of characters is finished yet
	if (current < 7) 
		pthread_cond_wait(&reading_done, &mutex);
 	strncpy(buffer, data, 7);
	current = 0;
	// signal to reader when the next set of characters is ready
	pthread_cond_signal(&writing_done);

  	pthread_mutex_unlock(&mutex);
}

