
#ifndef ROUNDROOM_H
#define ROUNDROOM_H

#include "Room.h"
#include "./../Globals.h"
#include <iostream>
#include <string>

class RoundRoom: public Room{
  public:
    RoundRoom(const bool isVisible=true, bool* whichExits=NULL, const std::string description="");
    ~RoundRoom();

    virtual int directionToIndex(const int whichDirection) const;
    
    virtual int getRoomExitDirection(const int whichDirection) const{
      const int roomExits[] = {N,NE,E,SE,S,SW,W,NW};
      return roomExits[whichDirection];
    }
    
  protected:
};

#endif
