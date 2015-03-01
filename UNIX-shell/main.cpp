//  CS433
//  UNIX_shell.cpp
//  project 2: UNIX shell with history feature
//
//  Created by Jason Meyer on 2/16/15.
//  Copyright (c) 2015 Jason Meyer and Keith Adams. All rights reserved.
//
//  This program creates a shell for the user to browse their system and execute commands.
//  The main purpose of this program for our class is to demonstrate the functionality
//  of the fork() wait(), and exec() family of functions from the unix  library,
//  as well as demonstrating how parent and child processes are created and interact.
//  In main, we take input from the user, and pass it to the function getArgs()
//  Getargs also calls regularCheck(), which checks the input that reaches the criteria for a normal
//  command.  inside of getargs, a check for simple history functionality is implemented.
//  Along with regularcheck(), getargs() also calls the function setHist() which gets called
//  under a specific condition of a user inputing a command that contains an exclamation
//  point followed by a number.
//  All three of these major funtions implement istringstream to convert the user command strings
//  into suitable null terminated strings to pass into our char*args[] under the predefined
//  conditions. The args[] array is then passed as a parameter to the execvp()
//  function after a call to fork().
//  If the user enters a command followed by a &, the parent process does not wait
//  for the child to finish, if the user enters "exit" the program exits,
//
//  Compile using command: make
//  or : g++ UNIX_shell.cpp main.cpp



#include "UNIX_shell.h"


int main(void)
{
    UNIX_shell myShell;
    char * args[256];


     string check = "";           ///check is used to determine !! and !# calls, etc.

   while(myShell.exitstatus==false)///while !exit
    {
    std::getline(std::cin, check);      ///get input from the user



    myShell.getArgs(check,args);  ///pass the input to args, calls fork exec and wait()


    if(myShell.exitstatus==false){/// if !exit, then user prompt.

            cout << myShell.userName + "@" + myShell.hostName + ":~"  + getcwd(NULL, 0) + "/"  ;

        }

    }

return 0;


};
