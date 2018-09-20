#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>     //print name of current/working directory
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

int sh( int argc, char **argv, char **envp ){  

  char buffer[BUFFERSIZE];
  int len;

  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;


  uid = getuid();			//user IDq
  password_entry = getpwuid(uid);      /* get passwd info (struct with user info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/  



  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )  {
    perror("getcwd");
    exit(2);
  }



  owd = calloc(strlen(pwd) + 1, sizeof(char)); //allocated space for pwd
  memcpy(owd, pwd, strlen(pwd));	//copies pwd to owd
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {
    /* print your prompt */

    /* get command line and process */

    /* check for each built in command and implement */

	printf(" %s", owd);
	printf("> ");

	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len-1] = '\0';	
		command = (char *) malloc(len);
		strcpy(command, buffer);
	}
	 

	char * exit = "exit";
	
	if (strcmp(command, exit) == 0) {
		break;
	}
	
	int totalNumArgs = 5;
	int numArgs = 0;
///	char **args = (char **) malloc(sizeof(char **));	
	

	for(int i = 0, j = 0; i < len; i++) {
		if(command[i] != ' ') {
			(args[numArgs])[j] = command[i];
			j++;
		} 
		
		else {
			i++;
			j = 0;
			numArgs++;
		}
	}

		execv(args[0], args);

     /*  else  program to exec */
   // {
       /* find it */
       /* do fork(), execve() and waitpid() */

/*      else
        fprintf(stderr, "%s: Command not found.\n", args[0]);
    }*/
  }
	free(command);
	free(args);
	free(prompt);
	free(commandline);
	free(owd);


 	return 0;
} /* sh() */


char *which(char *command, struct pathelement *pathlist )
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

