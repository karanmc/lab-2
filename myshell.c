/*

MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems *
Copyright (C) 2015, James Morisson, Karan Chandwaney (100472699), Tenzin Lungten
All rights reserved.
*/
// Put macros or constants here using #define
#define BUFFER_LEN 256
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"
// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
  // Input buffer and and commands
  char buffer[BUFFER_LEN] = { 0 };
  char command[BUFFER_LEN] = { 0 };
  char arg[BUFFER_LEN] = { 0 };
  char cwd[BUFFER_LEN] = { 0 };
  char line[BUFFER_LEN] = { 0 };
  char output[BUFFER_LEN] = { 0 };
  char shell[BUFFER_LEN] = { 0 };

  int paused = 0;


  FILE *readme;

  // Parse the commands provided using argc and argv
  // Perform an infinite loop getting command input from users
  getcwd(shell, sizeof(shell));
  strcat(shell,": ");//store shells working directory
  fputs(shell,stderr);
  while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
  {
      // Perform string tokenization to get the command and argument
      strcpy(arg,"");
      strcpy(command,"");

      sscanf(buffer,"%s %s",command,arg); // Parse the commands provided using argc and argv

      // Check the command and execute the operations for each command
          //pause has priority, we want to check if paused or not before checking if its actually a command
      if (strcmp(command,"pause")== 0 && paused != 1 && strcmp(arg, "") == 0){
          paused = 1;
      }
      else if (paused == 1){
          if (strcmp(buffer, "\n") == 0){
              paused = 0;
          }
      }
        // cd command -- change the current directory
      else if (strcmp(command, "cd") == 0)
      {

          if (strcmp(arg,"")!= 0){
              //system("cd");
              //strcat(command," ~");
              //strcat(command,arg);
              //system(command);
              chdir(arg);
          }
          else{
              system("pwd");
          }

      }
      // directory listingc
      else if (strcmp(command, "dir") == 0 && strcmp(arg, "") == 0)
      {
          getcwd(cwd, sizeof(cwd)); //store cwd
          strcpy(command,"cd"); //switch to cd command
          strcat(command," ");
          strcat(command,arg);
          system(command);
          system("ls"); // display all files (linux) within cwd
          strcat(command," ");
          strcat(command,cwd);
          system(command);//cd back to stored cwd

      }
      //enviorment variables
      else if (strcmp(command, "environ") == 0 && strcmp(arg, "") == 0)
      {
          system("printenv"); // again linux terminal usage
      }

      // clear command
      else if (strcmp(command,"clr")== 0 && strcmp(arg, "") == 0){
          //system("cls"); // windows terminal usage
          system("reset"); // linux terminal usage
      }
      // quit command -- exit the shell
      else if (strcmp(command, "quit") == 0 && strcmp(arg, "") == 0)
      {
          return EXIT_SUCCESS;
      }
      // echo command -- repeat back argument then move to next line with \n
      else if (strcmp(command, "echo") == 0 )
      {
          //strcat(arg,"\n");
          fputs(arg,stderr);
          fputs("\n",stderr);
      }
      else if (strcmp(command, "help") == 0 && strcmp(arg, "") == 0){

          if (access("README.md",F_OK)!=-1){

              readme = fopen("README.md", "r");
              fgets(line,BUFFER_LEN,readme);
              strcpy(output,line);
              while (!feof(readme)){
                  strcat(output,line);
                  fgets(line,BUFFER_LEN,readme);
              }
              fclose(readme);
          }
          else{
              strcat(output,"Readme file was not found in cwd\n");

          }
          fputs(output,stderr);
          strcpy(output,"");

      }
      // Unsupported command
      else
      {
          fputs("Unsupported command, use help to display the manual\n", stderr);
      }

      getcwd(shell, sizeof(shell));
      strcat(shell,": ");//store shells working directory
      fputs(shell,stderr);
  }
return EXIT_SUCCESS;
}
