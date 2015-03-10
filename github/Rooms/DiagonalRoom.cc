
#include "DiagonalRoom.h"
#include "./../Globals.h"
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------
// #DiagonalRoom() (Constructor)
//------------------------------------------------------
DiagonalRoom::DiagonalRoom(bool isVisible, bool* whichExits, string description){
  m_roomType = DIAGONAL_ROOM;
  m_maxExits = 4;

  m_visibility = isVisible;

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
  // m_description is inherited from Room
}
//------------------------------------------------------
// #~DiagonalRoom() (Destructor)
//------------------------------------------------------
DiagonalRoom::~DiagonalRoom(){
}

//------------------------------------------------------
// #directionToIndex()
//------------------------------------------------------
int DiagonalRoom::directionToIndex(int whichDirection) const{
  return (whichDirection-NE)/E;
}
