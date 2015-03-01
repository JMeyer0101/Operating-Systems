//
//  UNIX_shell.cpp
//  project 2: UNIX shell with history feature
//
//  Created by Jason Meyer on 2/16/15.
//  Copyright (c) 2015 Jason Meyer. All rights reserved.
//


#include "UNIX_shell.h"


UNIX_shell::UNIX_shell(){   //constructor, initialize instance variables

    exitstatus = false;
    userName = getlogin();
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    hostName = hostname;
    histIndex=0;
    concatCommand="";
    argsIndex=0;
    homedir = string(getcwd(NULL,0));
    cout<<"     ::     UNIX SHELL    :: "<<endl;
    cout<< endl;
    cout << userName + "@" + hostName + ":~/" ;

};

void UNIX_shell::getArgs(string check, char * args[]){ ///get a command from user using istream and ' ' as delimiter


    concatCommand="";  //re-init values
    argsIndex = 0;



     if(check[0] == 'e'&&check[1] == 'x'&&check[2] == 'i'&&check[3] == 't'){ ///if user enters exit, set exit bool to true

        exitstatus=true;
        check ="";
//
        return ;

    }
    else if(check[0]=='!'&&check[1]!='!'&&check.length()!=1&& exitstatus==false&&check!="exit")     ///checks for !# expressions
    {

        this->histArg(check, args); ///defined below
       // return;
       return;
    }



    else if(check == "!"&&check!="exit"){  ///error handling
    history.push_back(check);
    histIndex++;
    return;
    } else if(check == "cd.."||check=="cd."){
    history.push_back(check);
    histIndex++;
    return;
    }


    else if(check=="cd"&&exitstatus==false&&check!="exit"){ /// home directory chdir handling
    history.push_back(check);
    histIndex++;
  //  cout<<"HOMEDIR CHECK"<<endl;
    std::string myText(homedir);
    std::istringstream iss(myText);
    std::string token;
    argsIndex=0;
    while(getline(iss, token, ' '))
    {
          args[argsIndex] = strdup(token.c_str());
          argsIndex++;
    }
    args[argsIndex]= '\0';

                    int directory = chdir(args[0]);  ///check for valid directory

                        if(directory == -1){
                            perror("");

                            }
                return;
    }
///end homdir cd check



if(check == "history"&&exitstatus==false) ///if the user enters "history", display history with number vals
            {



                int histcount = history.size();
                if (history.size()==0) { cout << "[empty]" << endl; }

                else if(history.size()==1){
                cout << "1 "<<history[0] << endl;

                }
                else if(history.size()>10)
                {
                int histcount = history.size();                  ///if history greater than 10, only show the previous ten entries
                int j = histcount -1;
                   for(int i =0;i<10;i++)
                   {
                        cout <<histcount--<< " "<< history[j] << endl;
                        j--;
                   }
                }
                else
                {       //display history
                    for (vector<string>::reverse_iterator
                        i = history.rbegin();
                        i != history.rend(); ++i)
                    {  cout <<histcount--<< " "<< *i << endl; }
                }


                return;
            }






else if (check == "!!"&&exitstatus==false){ //check for !! case, execute previous command


 if(history.size()==0){
    cout<<"No commands in history"<<endl;
    return;
}
check = history[histIndex-1];
//cout<<"CHECK IS "<<check<<endl;
 if(history[histIndex-1]=="cd"){   //if prev history is cd, chdir to homdir

  //  cout<<"HOMEDIR CHECK"<<endl;
    std::string myText(homedir);
    std::istringstream iss(myText);
    std::string token;
    argsIndex=0;
    while(getline(iss, token, ' '))
    {
          args[argsIndex] = strdup(token.c_str());
          argsIndex++;
    }
    args[argsIndex]= '\0';

                    int directory = chdir(args[0]);  ///check for valid directory

                        if(directory == -1){
                            perror("");

                            }

                argsIndex =0;

                return;
    }
if(exitstatus==false&&check!="cd.."&&check!="exit"){   //case fore regular previous history input


        argsIndex = 0;


        string myText(history[histIndex-1]);

        std::istringstream iss(myText);
        string token;
        while(getline(iss, token, ' '))
        {
              args[argsIndex] = strdup(token.c_str());
              argsIndex++;
        }
        args[argsIndex]= NULL;


        if(check[0] == 'c' && check[1]=='d'&&check!="cd"&&exitstatus==false)
                    {

                    args[argsIndex]= '\0';

                        int directory = chdir(args[1]);  ///check for valid directory

                            if(directory == -1){
                                perror("");

                                }

                            return;

            }

        if(check[0]!='l'&&check[1]!='s')
        {
        check = args[argsIndex-1];
        }
        if(check =="&")
       {
       args[argsIndex-1] = '\0';          //dont wait for child check


       }



            pid = fork();
            if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            //return 1;
            }
            else if (pid == 0 ) { /* child process */

            execvp(args[0],args);
            exit(EXIT_FAILURE);  //if the child process fails, exit the child process.
            }
            else if(check!= "&"){/* parent will wait for the child to complete */

                wait(NULL);

                }
            else
            {
                return;
            }

    }
    return;
}//end !! check


    if(check == "exit"){ ///if user enters exit, set exit bool to true

        exitstatus = true;
       cout << "exit = true"<<endl;
       cout << "attempting exit"<<endl;
      //  this->getArgs(args);
      return;
      }

if(check!="exit"){
this->regularCheck(check,args);         ///check a normal, non chdir or history function input
return;
}
 // cout<<"END"<<endl;
  return;

};

void UNIX_shell::initShell(){       //initialize the shell and display a prompt

    userName = getlogin();
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    hostName = hostname;
    histIndex=0;
    argsIndex=0;
    homedir = string(getcwd(NULL,0));
    cout<<"::<begin osh>::"<<homedir<<endl;
    cout << userName + "@" + hostName + ":~/" ;

};


void UNIX_shell::histArg(string check, char * args[]){//handle user history selection
/// memset(&args[0], '\0', sizeof(args)); //neccesary?
   // cout<<"CHECK IS::" << check << endl;




    if(check[0]!='c'&& check[1]!='d'&& exitstatus == false){   ///handle non chdir cases

       // cout<<"History size ::"<<history.size()<<endl;
       // cout<<"History index ::"<<histIndex<<endl;


            int numberwang = atoi(check.substr(1,2).c_str());

            if(history.size()==0)
            {
            cout<<"No such command in history"<<endl;
            return;
            }
            else if(numberwang>(histIndex)){
            cout<<"No such command in history"<<endl;
            return;
            }




                check =history[numberwang-1];

                if(check == "!"){                       ///error handling
                    history.push_back(check);
                    histIndex++;
                    return;
                    } else if(check == "cd.."||check == "cd."){
                    history.push_back(check);
                    histIndex++;
                    return;
                    }

                if(check=="cd"){////if previous history entry == cd

  //  cout<<"HOMEDIR CHECK"<<endl;
    std::string myText(homedir);
    std::istringstream iss(myText);
    std::string token;
    argsIndex=0;
    while(getline(iss, token, ' '))
    {
          args[argsIndex] = strdup(token.c_str());
          argsIndex++;
    }
    args[argsIndex]= '\0';

                    int directory = chdir(args[0]);  ///check for valid directory

                        if(directory == -1){
                            perror(" ");

                            }
                return;
    }


            std::string myText(check);
            std::istringstream iss(myText);
            std::string token;
            argsIndex=0;
            while(getline(iss, token, ' '))
            {
                  args[argsIndex] = strdup(token.c_str());
                  argsIndex++;

            }
            args[argsIndex]= '\0';




            /////////////////////////////////////////////////////
        if(check[0] == 'c' && check[1] =='d'&& check!="cd"&&exitstatus==false)
            {

                    // cout<< "CD CHECK FOR !# INPUT" << endl;

                int directory = chdir(args[1]);  ///check for valid directory

                    if(directory == -1){
                        perror("");

                        }

                return;
            }





    if(check[0]!='!'){  //if the userinput is not a history selection

   if(check[0]!='l'&&check[1]!='s')
        {
        check = args[argsIndex-1];
        }

       if(check =="&")
       {
       args[argsIndex-1] = '\0';          //dont wait for child check


       }



            pid = fork();
            if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            //return 1;
            }
            else if (pid == 0 ) { /* child process */

            execvp(args[0],args);
            exit(EXIT_FAILURE);
            }
            else if(check!= "&"){/* parent will wait for the child to complete */

                wait(NULL);

                }
            else
            {

            }
            //return;

        };
///////////////////////////////////////////////////////////////////////////////////

}//end if not cd
//cout << "REACHED END " << endl;

return;////////////////////////////////////////////////////

  };


void UNIX_shell::regularCheck(string check, char * args[]){  ///checks for normal user input and pushes to args for exec
//cout<<check<<endl;

if(check!="exit"){


    if (check.size() ==0&&exitstatus==false){  ///check for empty input


        return;
    }
    else if(exitstatus==false&&check!="cd.."&&check!="exit"){

    argsIndex = 0;
    string myText(check);
            std::istringstream iss(myText);
            string token;
            argsIndex=0;
            while(getline(iss, token, ' '))
            {
                    concatCommand.append(token + " ");
                  args[argsIndex] = strdup(token.c_str());
                  argsIndex++;

            }
            args[argsIndex]= '\0';

     if (check != "history"&&exitstatus==false&&check!="!!"&&check[0]!='!')
            {

            history.push_back(concatCommand);///push user string to history
            histIndex++;
            concatCommand="";


            }



    }





///CD CHECK
     if(check[0] == 'c' && check[1] =='d'&& exitstatus==false&&check!="cd")
            {

                int directory = chdir(args[1]);  ///check for valid directory

                    if(directory == -1){
                        perror("");

                        }

                    return;
            }

 if(exitstatus==false&&check!="cd..")
    {

        ///fork a child process
        if(check[0]!='l'&&check[1]!='s')
        {
        check = args[argsIndex-1];
        }
      //  cout<< check<<endl;
       if(check =="&")
       {
       args[argsIndex-1] = '\0';


       }

           /// cout << check + "::final then fork"<< endl;

            pid = fork();


            if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed");
            //return 1;
            }
            else if (pid == 0 ) { /* child process */

            execvp(args[0],args);
            perror("");
            exit(EXIT_FAILURE);
            }
            else if(check!= "&"){/* parent will wait for the child to complete */

                wait(NULL);


              //  cout <<"Child Complete" << endl;
                }
            else
            {

            }
            return;
        }


    }//endif check=exit

};







