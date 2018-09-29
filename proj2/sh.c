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


  while ( go == 1 )
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
 

	char * exitStatus = "exit";
	if (strcmp(commandline, exitStatus) == 0) {
		break;
	}
	
	

	const char delim[2] = " ";
	char *token;

	token = strtok(commandline, delim);
//	args[0] = which(token,path,numPaths); 		
	args[0] = token;

	for(j=1; token != NULL; j++) {
	
		token = strtok(NULL, delim);
		args[j] = token;
	}
	args[j] = NULL;	


	if(strcmp(args[0], "where") == 0) {
		printf("%s\n", where(args[1], pathlist));
	
	}
	
	else if(strcmp(args[0], "which") == 0) {
		printf("%s\n", which(args[1], pathlist));
	}

	else if(strcmp(args[0], "cd") == 0) {
		char *directory = args[1];
		int ret;
		ret = chdir(directory);
		
		if((owd = getcwd(NULL, PATH_MAX+1)) == NULL) {
			perror("getcwd");
			exit(2);
		}

		// - returns to prev directory

	}

	else if(strcmp(args[0], "pwd") == 0) {
		printf("%s\n", getcwd(NULL, PATH_MAX+1));
	}


	else if(strcmp(args[0], "list") == 0) {
		list(args[1]);
	}


	else if(strcmp(args[0], "pid") == 0) {
		printf("PID: %d\n", getpid());
	}


	else if(strcmp(args[0], "kill") == 0) {
		if (args[1][0] == '-') {
			kill(args[2], args[1]);
		}
		else {
			kill(args[2], 0);
		}
	}

/*	
	else if(strcmp(args[0], "prompt") == 0) {
		prompt();
	}

	
	else if(strcmp(args[0], "printenv") == 0) {
		printenv();
	}


	else if(strcmp(args[0], "alias") == 0) {
		alias();
	}


	else if(strcmp(args[0], "history") == 0) {
		history();
	}


	else if(strcmp(args[0], "setenv") == 0) {
		setenv();
	}
	*/
	else {
	
		pid_t childpid = fork();
	
		if(childpid == -1) {
			printf("can't fork\n");
			exit(EXIT_FAILURE);
		}
	
		else if(childpid == 0) {
			execve(which(args[0],pathlist), args, path); 
			exit(0);
		}
		
		else {

			waitpid(childpid, &status, 0);
		}

	}

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


char *which(char *command, struct pathelement *pathlist)
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

	char *cmdpath;
	struct pathelement *temp = pathlist;
	int numPaths;
	char **path = calloc(MAXARGS, sizeof(char*));
	int i;

	for(i = 0; temp->next != NULL; i++) {

		path[i] = temp->element;
		temp = temp->next; 
 
	}
 	numPaths = i;

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
	free(path);
	
	if(cmdpath != NULL) {
		return cmdpath;
	}
	else {
		return NULL;
	}

} /* which() */

char *where(char *command, struct pathelement *pathlist)
{
  /* similarly loop through finding all locations of command */
 /* where() */

	char **cmdpath = calloc(MAXARGS, sizeof(char*));
	struct pathelement *temp = pathlist;
	int numPaths;
	char **path = calloc(MAXARGS, sizeof(char*));
	int i;
	int size = 0;
	char* allPaths = calloc(MAXARGS, sizeof(char));;	


	for(i = 0; temp->next != NULL; i++) {

		path[i] = temp->element;
		temp = temp->next; 
 
	}
 	numPaths = i;

	
	for(int j = 0, k = 0; j < numPaths; j++) {
	
		size_t len1 = strlen(path[j]), len2 = strlen("/"), len3 = strlen(command);
		char *concat1 = malloc(len1 + len2 + 1);
		char *concat2 = malloc(len1 + len2 + len3 + 1);
			
	
		memcpy(concat1, path[j], len1);
		memcpy(concat1 + len1, "/", len2 + 1);
	
		memcpy(concat2, concat1, len1 + len2);
		memcpy(concat2 + len1 + len2, command, len3 + 1);		
	
		if(access(concat2, X_OK) == 0) {
			size_t catLen = strlen(concat2), colonLen = strlen(":"), allPathsLen = strlen(allPaths);
			char *concat3 = malloc(catLen + colonLen + 1);
			
			memcpy(concat3, concat2, catLen);
			memcpy(concat3 + catLen,":",colonLen + 1);
			
			memcpy(allPaths + allPathsLen, concat3, catLen + colonLen + 1);

			k++;
			
		}
	
//		free(concat1);
//		free(concat2);
	}
		
		free(path);

		return allPaths;

}




void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */

	if(dir == NULL) {
		dir = ".";
	}

	DIR *directory;	
	directory = opendir(dir);
	struct dirent *dp;	

	if(directory == NULL) {
		perror("Error! Unable to open directory. \n");
	//	exit(1);
		return;
	}

	while((dp=readdir(directory)) != NULL) {
		
		printf("%s\n", dp->d_name);
	}	
	
	closedir(directory);


} /* list() */








