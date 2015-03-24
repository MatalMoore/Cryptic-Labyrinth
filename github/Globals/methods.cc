
#include "methods.h"
#include "constants.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//------------------------------------------------------
// #stringsToSequence
//------------------------------------------------------
string stringsToSequence(const string* strings, int numberOfStrings){
  if(numberOfStrings < 2){
    return strings[0];
  }

  int i;
  stringstream sstream;

  sstream << strings[0];

  if(numberOfStrings > 2){
    for(i=1; i<numberOfStrings-1; i++){
      sstream << ", " << strings[i];
    }
    sstream << ", and " << strings[i];
  }
  else{
    sstream << " and " << strings[1];
  }

  return sstream.str();
}
//------------------------------------------------------
// #compassDirectionToString
//------------------------------------------------------
string compassDirectionToString(int compassDirection, bool giveFullName){
  if(compassDirection<NO_DIRECTION || compassDirection>=DIRECTION_MAX){
    return "N/A";
  }
  else if(giveFullName){
    return DIRECTION_ARRAY_LONG[compassDirection-NO_DIRECTION];
  }
  else{
    return DIRECTION_ARRAY_SHORT[compassDirection-NO_DIRECTION];
  }
}
//------------------------------------------------------
// #uppercase
//------------------------------------------------------
std::string uppercase(std::string value){
  int size = value.size();
  int offset = 'a'-'A';
  string returnString = value;

  for(int i=0; i<size; i++){
    if(returnString[i]>='a' && returnString[i]<='z'){
      returnString[i] -= offset;
    }
  }

  return returnString;
}

//------------------------------------------------------
// #oppositeDirection
//------------------------------------------------------
int oppositeDirection(int compassDirection){
  return (compassDirection + DIRECTION_MAX/2) % DIRECTION_MAX;
}
//------------------------------------------------------
// #rotateDirection
//------------------------------------------------------
int rotateDirection(int compassDirection, int interval){
  int newDirection;

  if(!isGoodDirection(compassDirection)){
    return NO_DIRECTION;
  }

  if(compassDirection == CENTER){
    return CENTER;
  }

  interval %= DIRECTION_MAX;

  if(interval == 0){
    return compassDirection;
  }

  newDirection = (compassDirection + interval) % DIRECTION_MAX;

  if(newDirection < 0){
    newDirection += DIRECTION_MAX;
  }

  return newDirection;
}
//------------------------------------------------------
// #stringToCompassDirection
//------------------------------------------------------
int stringToCompassDirection(string value){
  int i;
  string upperString = uppercase(value);

  if(upperString.size() > 3){
    for(i=0; i<DIRECTION_MAX-NO_DIRECTION; i++){
      if(upperString == uppercase(DIRECTION_ARRAY_LONG[i])){
        return i+NO_DIRECTION;
      }
    }
  }
  else{
    for(i=0; i<DIRECTION_MAX-NO_DIRECTION; i++){
      if(upperString == uppercase(DIRECTION_ARRAY_SHORT[i])){
        return i+NO_DIRECTION;
      }
    }
  }

  return NO_DIRECTION;
}

//------------------------------------------------------
// #isNaturalDirection
//------------------------------------------------------
bool isNaturalDirection(int whichDirection){
  return (
      whichDirection>=N
      && whichDirection<DIRECTION_MAX
      && whichDirection%2==N%2
      );
}
//------------------------------------------------------
// #isGoodDirection
//------------------------------------------------------
bool isGoodDirection(int whichDirection){
  return (
      whichDirection==CENTER
      ||(whichDirection>=N
        && whichDirection<DIRECTION_MAX
        )
      );
}
