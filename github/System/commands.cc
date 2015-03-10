
#include "commands.h"
#include "./../Globals.h"
#include "./../Rooms.h"
#include "./../Characters.h"
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------
// #executeCommand
//------------------------------------------------------
bool executeCommand(const ::string* argv, const std::string* argvUpper, const int argc, const Character* character, const int offset){
  if(offset < argc){
    if(argvUpper[offset] == commandEXIT){
      return executeEXIT(argv, argvUpper, argc, offset);
    }
    else if(argvUpper[offset] == commandHELP){
      return executeHELP(argv, argvUpper, argc, offset);
    }
    else if(argvUpper[offset] == commandLOOK){
      return executeLOOK(argv, argvUpper, argc, character, offset);
    }
    else if(argvUpper[offset] == commandGO){
      return executeGO(argv, argvUpper, argc, character, offset);
    }
    else{
      cout << "Invalid command: \"" << argv[offset] << "\"" << endl;

      return false;
    }
  }
  else{
    return false;
  }
}

//------------------------------------------------------
// #executeEXIT
//------------------------------------------------------
bool executeEXIT(const string* argv, const string* argvUpper, const int argc, const int offset){
  bool exitFlag = false;

  if(argc == offset+1){
    cout << "Exiting ..." << endl
      << endl;

    return true;
  }
  else{
    cout << invalidArguments << commandEXIT << " takes exactly 0 arguments." << endl;
  }

  return exitFlag;
}

//------------------------------------------------------
// #executeHELP
//------------------------------------------------------
bool executeHELP(const string* argv, const string* argvUpper, const int argc, const int offset){
  int i;

  const string indent1 = "--";
  const string indent2 = "----";

  if(argc == offset+1){
    cout << "Valid commands:" << endl;
    cout << endl;

    cout << indent1 << "Commands with 0 arguments:" << endl;
    for(i=0; i<commands0argc; i++){
      cout << indent2 << commands0arg[i] << endl;
    }
    cout << endl;

    cout << indent1 << "Commands with 1 argument:" << endl;
    for(i=0; i<commands1argc; i++){
      cout << indent2 << commands1arg[i] << endl;
    }

    return true;
  }
  else if(argc == offset+2){
    if(argvUpper[offset+1] == commandEXIT){
      cout << indent1 << commandEXIT << " : " << helpEXIT << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandHELP){
      cout << indent1 << commandHELP << " " << argsHELP << " : " << helpHELP << endl;
      cout << indent2 << "0 arguments : Displays every valid COMMAND" << endl;
      cout << indent2 << "1 argument  : Displays info about a COMMAND" << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandLOOK){
      cout << indent1 << commandLOOK << " : " << helpLOOK << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandGO){
      cout << indent1 << commandGO << " " << argsGO<< " : " << helpGO << endl;

      return true;
    }
    else{
      cout << "Invalid command argument: \"" << argv[offset+1] << "\"" << endl;

      return false;
    }
  }
  else{
    cout << invalidArguments << commandHELP << " takes exactly 0 or 1 argument." << endl;
    return true;
  }
}

//------------------------------------------------------
// #executeLOOK
//------------------------------------------------------
bool executeLOOK(const string* argv, const string* argvUpper, const int argc, const Character* character, const int offset){
  if(argc == offset+1){
    cout << "You look around ..." << endl;
    character->displayCurrentRoom();

    return true;
  }
  else{
    cout << invalidArguments << commandLOOK << " takes exactly 0 arguments." << endl;

    return false;
  }
}

//------------------------------------------------------
// #executeGO
//------------------------------------------------------
bool executeGO(const string* argv, const string* argvUpper, const int argc, const Character* character, const int offset){
  int whichDirection;

  string directionString;
  Room* currentRoom;

  if(argc == offset+2){
    whichDirection = stringToCompassDirection(argvUpper[1]);

    if(whichDirection<N || whichDirection>NNW){
      cout << "Invalid direction argument: \"" << argv[1] << "\"" << endl;

      return false;
    }
    else{
      directionString = compassDirectionToString(whichDirection, true);
      currentRoom = character->getCurrentRoom();
      cout << "You try to go " << directionString << " ..." << endl;

      if(!currentRoom->exitExists(whichDirection)
          || currentRoom->isExitHidden(whichDirection)
          ||(!currentRoom->isVisible()
            && !currentRoom->isExitAccessible(whichDirection)
            )
          ){
        cout << "There is no apparent exit to the " << directionString << "." << endl;

        return true;
      }
      else if(currentRoom->isExitBlocked(whichDirection)){
        cout << "The " << directionString << " exit is blocked." << endl;

        return true;
      }
      else if(currentRoom->isVisible()
          && !currentRoom->isExitAccessible(whichDirection)
          ){
        cout << "The " << directionString << " exit is inaccessible." << endl;

        return true;
      }
      else{
        cout << "You go " << directionString << "." << endl;
        character->setCurrentRoom(currentRoom->getRoom(whichDirection));
        character->displayCurrentRoom();

        return true;
      }
    }
  }
  else{
    cout << invalidArguments << commandGO << " takes exactly 1 argument." << endl;

    return false;
  }
}
