
#ifndef ROOM_H
#define ROOM_H

#include "RoomExit.h"
#include "./../Superclasses.h"
#include "./../Globals.h"
#include <iostream>
#include <string>

class RoomExit;

class Room: public Container{
  public:
    Room(const bool isVisible=true, bool* whichExits=NULL, const std::string description="");
    virtual ~Room();

    //------------------------------------------------------
    // 'whichDirection' refers to a compass direction
    //------------------------------------------------------
    virtual void setExit(const int whichDirection, RoomExit* roomExit);
    void setExitBlocked(const int whichDirection, const bool boolean=true) const;
    void setExitHidden(const int whichDirection, const bool boolean=true) const;
    void setRoom(const int whichDirection, Room* room) const;
    void setVisible(const bool isVisible);
    void createRoom(const int whichDirection);
    void deleteRoom(const int whichDirection, const bool isExitDeleted=true);

    //------------------------------------------------------
    // 'OPPOSITE' indicates the opposite direction of
    //  'whichDirection'
    //------------------------------------------------------
    virtual void linkRooms(const int whichDirection, Room* room=NULL, const int toWhichDirection=OPPOSITE, RoomExit* roomExit=NULL);

    void unlinkRooms(const int whichDirection, const bool isExitDeleted = true);

    bool exitExists(const int whichDirection) const;
    bool roomExists(const int whichDirection) const;
    bool isInputValid(const int whichDirection) const;
    virtual bool isExitBlocked(const int whichDirection) const;
    bool isExitHidden(const int whichDirection) const;
    virtual bool isExitAccessible(const int whichDirection) const;
    bool isThisRoom1OfExit(const int whichDirection) const;
    bool isVisible() const;
    bool areThereNoExits() const;
    bool areAllExitsHidden() const;

    int getMaxExits() const;

    RoomExit* getExit(const int whichDirection) const;
    Room* getRoom(const int whichDirection) const;

    std::string exitsToString() const;
    std::string getRoomType() const;

    virtual int directionToIndex(const int whichDirection) const;
    virtual int getRoomExitDirection(RoomExit* exit) const;
    virtual int getRoomExitDirection(const int whichExitIndex) const{
      int roomExits[] = {N,E,S,W};
      return roomExits[whichExitIndex];
    }

    virtual void displayExits(std::ostream& o) const;
    virtual void display(std::ostream& o) const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    static unsigned int getNextRoomID(){return s_nextRoomID;}
    static unsigned int getRoomCount(){return s_roomCount;}
    static unsigned int getRoomMax(){return s_roomMax;}
    static Room* getRoomFromID(unsigned int roomID){return s_rooms[roomID];}

  protected:
    bool m_visibility;
    bool* m_whichExits;
    int m_maxExits;
    RoomExit** m_exits;

    unsigned int m_roomID;
    std::string m_roomType;

    static unsigned int s_nextRoomID;
    static unsigned int s_roomCount;
    static unsigned int s_roomMax;
    static Room** s_rooms;

    //------------------------------------------------------
    // methods that output an error message
    //------------------------------------------------------
    void displayInvalidInput(const int whichDirection, const std::string methodName) const;
    void displayNullInput(const int whichDirection, const std::string methodName) const;
};

std::ostream& operator<<(std::ostream& o, Room& room);

#endif
