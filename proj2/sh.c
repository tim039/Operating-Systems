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
  int j;
  int numPaths;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;
 // char ** arguments =  calloc(MAXARGS, sizeof(char*));
  char **path = calloc(MAXARGS, sizeof(char*));
 // char* cmdpath = calloc(PROMPTMAX, sizeof(char));

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
  struct pathelement *temp = pathlist;

  /* putting pathlist into a char* const*/

//put each path in element of an array
  for(j = 0; temp->next != NULL; j++) {

	path[j] = temp->element;
	temp = temp->next; 
 }
 path[j] = NULL;
 numPaths = j - 1;


  while ( go )
  {
    /* print your prompt */


	printf(" %s", owd);
	printf("> ");



    /* get command line and process */


	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len-1] = '\0';	
		strcpy(commandline, buffer);
	}
	

    /* check for each built in command and implement */
 

	char * exit = "exit";
	
	if (strcmp(commandline, exit) == 0) {
		break;
	}
	
	

	const char delim[2] = " ";
	char *token;

	token = strtok(commandline, delim);
	args[0] = which(token,path,numPaths); 		


	for(j=1; token != NULL; j++) {
	
		token = strtok(NULL, delim);
		args[j] = token;
	}
	args[j] = NULL;	

	if(execve(args[0], args, path) == -1) {// ;

		printf("failed");

	}

	else {
		printf("works");
	}
	//	execve(arguments[0],arguments);

     /*  else  program to exec */
   // {
       /* find it */
       /* do fork(), execve() and waitpid() */

/*      else
        fprintf(stderr, "%s: Command not found.\n", args[0]);
    }*/
  }
//	free(cmdpath);
	free(args);
	free(prompt);
	free(commandline);
	free(owd);
	//free(arguments);
	free(path);


 	return 0;
} /* sh() */


char *which(char *command, char **path,int numPaths)
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

	char *cmdpath;

      


		for(int j = 0; j < numPaths; j++) {
	
		size_t len1 = strlen(path[j]), len2 = strlen("/"), len3 = strlen(command);
		char *concat1 = malloc(len1 + len2 + 1);
		char *concat2 = malloc(len1 + len2 + len3 + 1);
		
		memcpy(concat1, path[j], len1);
		memcpy(concat1 + len1, "/", len2 + 1);

		memcpy(concat2, concat1, len1 + len2);
		memcpy(concat2 + len1 + len2, command, len3 + 1);		
		
		if(access(concat2, X_OK) == 0) {

			cmdpath = concat2;			
			break;
		}

		free(concat1);
		free(concat2);
	}


	return cmdpath;

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

