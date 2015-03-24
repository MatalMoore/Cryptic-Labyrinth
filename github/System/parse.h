
#ifndef PARSE_H
#define PARSE_H

#include "commands.h"
#include "./../Globals.h"
#include "./../Rooms.h"
#include "./../Characters.h"
#include <string>
using namespace std;

//------------------------------------------------------
// #parse
//------------------------------------------------------
bool parse(const string input){

  int argc;
  int substringStart;
  int size;
  int whichDirection;
  int i;

  bool isValid = true;
  bool exitFlag = false;

  Room* currentRoom;

  string directionString;
  string stringHold;

  string* argv = new string[ARGC_MAX];
  string* argvUpper = new string[ARGC_MAX];

  argc = 0;
  substringStart = 0;
  size = input.size();

  // Getting each substring that is surrounded by ' '
  for(i=0; i<size && argc<ARGC_MAX; i++){
    if(input[i]==' ' || i+1==size){
      // If this is not included, the last character is
      //  omitted if it is not a space
      if(i+1==size && input[i]!=' '){
        i++;
      }
      //
      stringHold = input.substr(substringStart, i-substringStart);
      substringStart = i+1;
      if(stringHold.size() == 0){
        continue;
      }
      argv[argc] = stringHold;
      argc++;
    }
  }

  for(i=0; i<argc; i++){
    argvUpper[i] = uppercase(argv[i]);
  }

  if(argc >= 1){
    isValid = executeCommand(argv, argvUpper, argc, Character::PLAYER);

    if(argvUpper[0] == commandEXIT){
      exitFlag = isValid;
    }
  }
  else{
    isValid = false;
  }

  if(!isValid){
    cout << "Invalid input: \"";

    for(i=0; i<argc-1; i++){
      cout << argv[i] << " ";
    }
    if(argc > 0){
      cout << argv[argc-1];
    }
    cout << "\"" << endl;
  }

  delete[] argvUpper;
  delete[] argv;

  return exitFlag;
}

#endif
