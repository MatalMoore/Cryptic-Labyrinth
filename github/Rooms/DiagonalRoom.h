
#ifndef DIAGONALROOM_H
#define DIAGONALROOM_H

#include "Room.h"
#include "./../Globals.h"
#include <iostream>
#include <string>

class DiagonalRoom: public Room{
  public:
    DiagonalRoom(const bool isVisible=true, bool* whichExits=NULL, const std::string description="");
    ~DiagonalRoom();

    virtual int directionToIndex(const int whichDirection) const;
    
    virtual int getRoomExitDirection(const int whichDirection) const{
      int roomExits[] = {NE,SE,SW,NW};
      return roomExits[whichDirection];
    }

  protected:
};

#endif
