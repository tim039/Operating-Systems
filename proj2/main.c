#include "sh.h"
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signal); 

int main( int argc, char **argv, char **envp )
{
  /* put signal set up stuff here */
char *test = malloc(sizeof(char));
test = "hello";
//free(test);

printf("%s\n", test);


 return sh(argc, argv, envp);
}

void sig_handler(int signal)
{
  /* define your signal handler */
}

