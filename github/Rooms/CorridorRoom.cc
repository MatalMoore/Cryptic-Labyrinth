
#include "CorridorRoom.h"
#include "./../Globals.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//------------------------------------------------------
// #CorridorRoom() (Constructor)
//------------------------------------------------------
CorridorRoom::CorridorRoom(int initialDirection, bool isVisible, bool* whichExits, string description){
  int direction0 = initialDirection;
  int direction1 = oppositeDirection(initialDirection);

  int minDirection = min(direction0, direction1);
  int maxDirection = max(direction0, direction1);

  stringstream sstream;

  m_roomType = CORRIDOR_ROOM;
  m_maxExits = 2;

  m_visibility = isVisible;

  if(isNaturalDirection(initialDirection)){
    m_direction = initialDirection;
  }
  else{
    displayInvalidInput(initialDirection, "CorridorRoom");
    m_direction = N;
  }

  if(whichExits == NULL){
    m_whichExits = new bool[m_maxExits];
    for(int i=0; i<m_maxExits; i++)
      m_whichExits[i] = false;
  }
  else{
    m_whichExits = whichExits;
  }

  m_exits = new RoomExit*[m_maxExits];

  m_title = "corridor";
  m_descriptor = "a";

  if(description.empty()){
    sstream  <<  "You are in a corridor.\n"
      << "The corridor runs "
      << compassDirectionToString(minDirection)
      << " to "
      << compassDirectionToString(maxDirection)
      << ".";

    m_description = sstream.str();
  }
  else{
    m_description = description;
  }
}
//------------------------------------------------------
// #~CorridorRoom() (Destructor)
//------------------------------------------------------
CorridorRoom::~CorridorRoom(){
}

//------------------------------------------------------
// #setDirection()
//------------------------------------------------------
void CorridorRoom::setDirection(int whichDirection){
  int direction0 = whichDirection;
  int direction1 = oppositeDirection(direction0);

  int minDirection = min(direction0, direction1);
  int maxDirection = max(direction0, direction1);

  stringstream sstream;

  m_direction = whichDirection;

  sstream << "You are in a corridor.\n"
    << "The corridor runs "
    << compassDirectionToString(minDirection)
    << " to "
    << compassDirectionToString(maxDirection)
    << ".";

  m_description = sstream.str();
}
//------------------------------------------------------
// #getDirection()
//------------------------------------------------------
int CorridorRoom::getDirection() const{
  return m_direction;
}

//------------------------------------------------------
// #directionToIndex()
//------------------------------------------------------
int CorridorRoom::directionToIndex(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "diretionToIndex");
    cerr << "Using index 0" << endl;

    return 0;
  }

  if(whichDirection == m_direction){
    return 0;
  }
  else{
    return 1;
  }
}
