//
//  shell.h
//  project 2: UNIX shell with history feature
//
//  Created by Jason Meyer on 2/16/15.
//  Copyright (c) 2015 Jason Meyer. All rights reserved.
//

#ifndef UNIX_shell_h
#define UNIX_shell_h

#include <sstream>
#include <vector>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sstream>
#include <cstring>
#include <sys/types.h>
 #include <sys/stat.h>
using std::string;
using std::vector;
using std::cout;
using std::endl;



class UNIX_shell{



    vector<string> history; //history stack for storing commands
    string homedir;
    pid_t pid;    //process ID for child process


public:

    string userName;
    string hostName;
    UNIX_shell();  //default constructor
    void initShell() ;//initialize the shell and display the cwd on the screen
    void getArgs(string check,char * args[]); //get a command from user using isstream, fork, exec and wait
    string concatCommand;
    bool exitstatus; /* flag to determine when to exit program */
    int argsIndex;
    int histIndex;

private:

void histArg(string check, char * args[]) ; //execute a specific user arg from the history stack, called in getargs
void regularCheck(string check, char * args[]);//execute a normal user command
};
#endif
