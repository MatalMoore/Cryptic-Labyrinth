
#include "RoundRoom.h"
#include "./../Globals.h"
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------
// #RoundRoom() (Constructor)
//------------------------------------------------------
RoundRoom::RoundRoom(bool isVisible, bool* whichExits, string description){
  m_roomType = ROUND_ROOM;
  m_maxExits = 8;

  m_visibility = true;

  if(whichExits == NULL){
    m_whichExits = new bool[getMaxExits()];
    for(int i=0; i<getMaxExits(); i++)
      m_whichExits[i] = false;
  }
  else{
    m_whichExits = whichExits;
  }
  m_exits = new RoomExit*[getMaxExits()];
  for(int i=0; i<getMaxExits(); i++){
    if(exitExists(getRoomExitDirection(i))){
      m_exits[i] = new RoomExit();
    }
    else{
      m_exits[i] = NULL;
    }
  }
  if(description.empty()){
    m_description = "You are in a round room.";
  }
  else{
    m_description = description;
  }
}
//------------------------------------------------------
// #~RoundRoom() (Destructor)
//------------------------------------------------------
RoundRoom::~RoundRoom(){
}

//------------------------------------------------------
// #directionToIndex()
//------------------------------------------------------
int RoundRoom::directionToIndex(int whichDirection) const{
  return whichDirection/2; 
}
