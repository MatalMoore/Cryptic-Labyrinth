
#ifndef ROOMEXIT_H
#define ROOMEXIT_H

#include "Room.h"
#include "./../Superclasses.h"
#include <iostream>

class Room;

class RoomExit: public Object{
  public:
    RoomExit(bool isBlocked=false, bool isHidden=false, Room* Room1=NULL, Room* Room2=NULL);
    ~RoomExit();

    void setBlocked(bool boolean);
    void setHidden(bool boolean);
    void setRoom1(Room* Room);
    void setRoom2(Room* Room);
    void setRoom1Direction(int whichDirection);
    void setRoom2Direction(int whichDirection);

    bool isBlocked();
    bool isHidden();
    Room* getRoom1();
    Room* getRoom2();
    int getRoom1Direction();
    int getRoom2Direction();

    virtual void display(std::ostream& o) const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    static unsigned int getNextRoomExitID(){return s_nextRoomExitID;}
    static unsigned int getRoomExitCount(){return s_roomExitCount;}
    static unsigned int getRoomExitMax(){return s_roomExitMax;}
    static RoomExit* getRoomExitFromID(unsigned int roomExitID){return s_roomExits[roomExitID];}

  private:
    bool m_isBlocked;
    bool m_isHidden;
    Room* m_room1;
    Room* m_room2;
    int m_room1Direction;
    int m_room2Direction;

    unsigned int m_roomExitID;

    static unsigned int s_nextRoomExitID;
    static unsigned int s_roomExitCount;
    static unsigned int s_roomExitMax;
    static RoomExit** s_roomExits;
};

std::ostream& operator<<(std::ostream& o, RoomExit& roomExit);

#endif
