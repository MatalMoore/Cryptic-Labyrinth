
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
bool executeCommand(const string* argv, const string* argvUpper, int argc, const Character* character, int offset){
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
    else if(argvUpper[offset] == commandUSE){
      return executeUSE(argv, argvUpper, argc, character, offset);
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
bool executeEXIT(const string* argv, const string* argvUpper, int argc, int offset){
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
bool executeHELP(const string* argv, const string* argvUpper, int argc, int offset){
  int i;

  const string indent1 = "--";
  const string indent2 = "----";

  const string help[] = {commandHELP, commandHELP};

  if(argc == offset+1){
    executeHELP(help, help, 2);
    cout << endl;

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
    cout << endl;

    cout << indent1 << "Commands with 2 arguments:" << endl;
    for(i=0; i<commands2argc; i++){
      cout << indent2 << commands2arg[i] << endl;
    }
    cout << endl;

    cout << indent1 << "Commands with 3 arguments:" << endl;
    for(i=0; i<commands3argc; i++){
      cout << indent2 << commands3arg[i] << endl;
    }

    return true;
  }
  else if(argc == offset+2){
    if(argvUpper[offset+1] == commandEXIT){
      cout << indent1
        << commandEXIT
        << " :"
        << endl;

      cout << indent2
        << helpEXIT
        << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandHELP){
      cout << indent1
        << commandHELP
        << " "
        << argsHELP
        << " :"
        << endl;

      cout << indent2
        << helpHELP
        << endl;

      cout << endl;

      cout << indent2
        << "0 arguments : Displays every valid COMMAND"
        << endl;

      cout << indent2
        << "1 argument  : Displays info about a COMMAND"
        << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandLOOK){
      cout << indent1
        << commandLOOK
        << " :"
        << endl;

      cout << indent2
        << helpLOOK
        << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandGO){
      cout << indent1
        << commandGO
        << " "
        << argsGO
        << " :"
        << endl;

      cout << indent2
        << helpGO
        << endl;

      return true;
    }
    else if(argvUpper[offset+1] == commandUSE){
      cout << indent1
        << commandUSE
        << " "
        << argsUSE
        << " :"
        << endl;

      cout << indent2
        << helpUSE
        << endl;

      cout << endl;

      cout << indent2
        << "STRING and/or DIRECTION is used for disambiguation."
        << endl;

      return true;
    }
    else{
      cout << "Invalid command argument: \""
        << argv[offset+1]
        << "\""
        << endl;

      return false;
    }
  }
  else{
    cout << invalidArguments
      << commandHELP
      << " takes exactly 0 or 1 argument."
      << endl;
    return true;
  }
}

//------------------------------------------------------
// #executeLOOK
//------------------------------------------------------
bool executeLOOK(const string* argv, const string* argvUpper, int argc, const Character* character, int offset){
  if(argc == offset+1){
    cout << "You look around ..." << endl;
    character->displayCurrentRoom();

    return true;
  }
  else{
    cout <<invalidArguments
      << commandLOOK
      << " takes exactly 0 arguments."
      << endl;

    return false;
  }
}

//------------------------------------------------------
// #executeGO
//------------------------------------------------------
bool executeGO(const string* argv, const string* argvUpper, int argc, const Character* character, int offset){
  int whichDirection;

  string directionString;
  Room* currentRoom;

  if(argc == offset+2){
    whichDirection = stringToCompassDirection(argvUpper[1]);

    if(whichDirection<N || whichDirection>NNW){
      cout << "Invalid direction argument: \""
        << argv[1]
        << "\""
        << endl;

      return false;
    }
    else{
      directionString = compassDirectionToString(whichDirection, true);
      currentRoom = character->getCurrentRoom();
      cout << "You try to go "
        << directionString
        << " ..." <<
        endl;

      if(!currentRoom->exitExists(whichDirection)
          || currentRoom->isExitHidden(whichDirection)
          ||(!currentRoom->isVisible()
            && !currentRoom->isExitAccessible(whichDirection)
            )
          ){
        cout << "There is no apparent exit to the "
          << directionString
          << "."
          << endl;

        return true;
      }
      else if(currentRoom->isExitBlocked(whichDirection)){
        cout << "The "
          << directionString
          << " exit is blocked."
          << endl;

        return true;
      }
      else if(currentRoom->isVisible()
          && !currentRoom->isExitAccessible(whichDirection)
          ){
        cout << "The "
          << directionString
          << " exit is inaccessible."
          << endl;

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
    cout << invalidArguments
      << commandGO
      << " takes exactly 1 argument."
      << endl;

    return false;
  }
}

//------------------------------------------------------
// #executeUSE
//------------------------------------------------------
bool executeUSE(const string* argv, const string* argvUpper, int argc, const Character* character, int offset){
  bool directionInputFlag;

  int holdDirection;

  string holdTitle;
  string holdSubDescription;

  Object* holdObject;
  Room* currentRoom;

  if(argc == offset+2){
    holdTitle = argv[offset+1];

    currentRoom = character->getCurrentRoom();

    holdObject = currentRoom->getObject(argv[offset+1]);

    if(holdObject == NULL){
      cout << invalidArguments
        << "There is no unique OBJECT called \""
        << holdTitle
        << "\""
        << endl;

      return false;
    }
    else{
      cout << "You use the "
        << uppercase(holdTitle)
        << "."
        << endl;

      return holdObject->activate(DEFAULT_ACTION);
    }
  }
  else if(argc == offset+3){
    holdTitle = argv[offset+2];
    holdDirection = stringToCompassDirection(argv[offset+1]);

    currentRoom = character->getCurrentRoom();

    directionInputFlag = isGoodDirection(holdDirection);

    if(directionInputFlag){
      holdObject = currentRoom->getObject(holdTitle, holdDirection);
    }
    else{
      holdSubDescription = argv[offset+1];
      holdObject = currentRoom->getObject(holdTitle, NO_DIRECTION, holdSubDescription);
    }

    if(holdObject == NULL){
      cout << invalidArguments
        << endl;
      cout << "  There is no unique OBJECT called \""
        << holdTitle
        << "\" ";
      if(directionInputFlag){
        cout << "in the "
          << compassDirectionToString(holdDirection, true);
      }
      else{
        cout << "on the \""
          << holdSubDescription
          << "\"";
      }
      cout << endl;
      cout << endl;

      return false;
    }
    else{
      cout << "You use the "
        << uppercase(holdTitle)
        << "."
        << endl;

      return holdObject->activate(DEFAULT_ACTION);
    }
  }
  else if(argc == offset+4){
    holdTitle = argv[offset+3];
    holdDirection = stringToCompassDirection(argv[offset+1]);
    holdSubDescription = argv[offset+2];

    currentRoom = character->getCurrentRoom();

    holdObject = currentRoom->getObject(holdTitle, holdDirection, holdSubDescription);

    if(holdObject == NULL){
      cout << invalidArguments
        << endl;
      cout << "  There is no unique OBJECT called \""
        << holdTitle
        << "\" in the "
        << compassDirectionToString(holdDirection, true)
        << " on the \""
        << holdSubDescription
        << "\""
        << endl;

      return false;
    }
    else{
      cout << "You use the "
        << uppercase(holdTitle)
        << "."
        << endl;

      return holdObject->activate(DEFAULT_ACTION);
    }
  }
  else{
    cout << invalidArguments
      << commandUSE
      << " takes exactly 1, 2, or 3 arguments."
      << endl;

    return false;
  }
}
