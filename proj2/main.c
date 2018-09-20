#include "sh.h"
#include <signal.h>
#include <stdio.h>

void sig_handler(int signal); 

int main( int argc, char **argv, char **envp )
{
  /* put signal set up stuff here */

/*char **test = (char **) malloc (sizeof(char **));
test[0] = " hello";
test[1] = " bye";



if((test[0])[0] == ' ') {//(test[1])[0]) {
	printf("Hell Yeah");
}
else {
printf("%s",test[1]);
}
*/

 return sh(argc, argv, envp);
}

void sig_handler(int signal)
{
  /* define your signal handler */
}

