#include "sh.h"
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signal); 
//char *concatenate(size_t size, char *array[size], const char *joint);

int main( int argc, char **argv, char **envp )
{
  /* put signal set up stuff here */

 return sh(argc, argv, envp);
}

void sig_handler(int signal)
{
  /* define your signal handler */
}

/*
char *concatenate(size_t size, char *array[size], const char *joint){
    size_t jlen, lens[size];
    size_t i, total_size = (size-1) * (jlen=strlen(joint)) + 1;
    char *result, *p;


    for(i=0;i<size;++i){
        total_size += (lens[i]=strlen(array[i]));
    }
    p = result = malloc(total_size);
    for(i=0;i<size;++i){
        memcpy(p, array[i], lens[i]);
        p += lens[i];
        if(i<size-1){
            memcpy(p, joint, jlen);
            p += jlen;
        }
    }
    *p = '\0';
    return result;
}
*/

