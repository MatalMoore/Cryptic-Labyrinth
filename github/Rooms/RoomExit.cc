
#include "./../Globals.h"
#include "./../Characters.h"
#include "RoomExit.h"
#include "Room.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

unsigned int RoomExit::s_nextRoomExitID;
unsigned int RoomExit::s_roomExitCount = 0;
unsigned int RoomExit::s_roomExitMax;
RoomExit** RoomExit::s_roomExits;

//------------------------------------------------------
// #RoomExit (Constructor)
//------------------------------------------------------
RoomExit::RoomExit(bool isBlocked, bool isHidden, Room* room1, Room* room2){
  if(s_roomExitCount == 0){
    s_nextRoomExitID = 0;
    s_roomExitMax = 100;
    s_roomExits = new RoomExit*[s_roomExitMax];
    if(SHOW_MESSAGES){
      cerr << "s_roomExits: Allocated" << endl
        << endl;
    }
  }

  m_type = ROOM_EXIT;

  s_roomExitCount++;

  stringstream charsOfID;

  charsOfID.width(4);
  charsOfID.fill('0');

  m_roomExitID = s_nextRoomExitID++;
  if(m_roomExitID>=s_roomExitMax){
    RoomExit** roomExitsHold = new RoomExit*[s_roomExitMax*2];
    for(int i=0; i<s_roomExitMax; i++){
      roomExitsHold[i] = s_roomExits[i];
      roomExitsHold[s_roomExitMax+i] = NULL;
      s_roomExits[i] = NULL;
    }
    delete[] s_roomExits;
    s_roomExits = roomExitsHold;
    s_roomExitMax *= 2;
  }
  s_roomExits[m_roomExitID] = this;

  charsOfID << m_roomExitID;
  charsOfID >> m_name;

  m_name.insert(0, "RoomExit");

  if(SHOW_MESSAGES){
    cerr << m_name << ": Creating" << endl;
  }

  m_isBlocked = isBlocked;
  m_isHidden = isHidden;
  m_room1 = room1;
  m_room2 = room2;
  m_room1Direction = NO_DIRECTION;
  m_room2Direction = NO_DIRECTION;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Created" << endl
      << endl;
  }
}
//------------------------------------------------------
// #~RoomExit (Destructor)
//------------------------------------------------------
RoomExit::~RoomExit(){
  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleting" << endl;
  }

  if(m_room1!=NULL){
    m_room1->unlinkRooms(m_room1->getRoomExitDirection(this), false);
  }
  else if(m_room2!=NULL){
    m_room1->unlinkRooms(m_room2->getRoomExitDirection(this), false);
  }

  s_roomExits[m_roomExitID] = NULL;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleted" << endl
      << endl;
  }

  if(s_roomExitCount == 0){
    delete[] s_roomExits;
    if(SHOW_MESSAGES){
      cerr << "s_roomExits: Deallocated" << endl
        << endl;
    }
  }
}

//------------------------------------------------------
// #setBlocked
//------------------------------------------------------
void RoomExit::setBlocked(bool boolean){
  m_isBlocked = boolean;
}
//------------------------------------------------------
// #setHidden
//------------------------------------------------------
void RoomExit::setHidden(bool boolean){
  m_isHidden = boolean;
}
//------------------------------------------------------
// #setRoom1
//------------------------------------------------------
void RoomExit::setRoom1(Room* room){
  //cerr << this << ": Room1 set to " << room << endl;
  m_room1 = room;
}
//------------------------------------------------------
// #setRoom2
//------------------------------------------------------
void RoomExit::setRoom2(Room* room){
  //cerr << this << ": Room2 set to " << room << endl;
  m_room2 = room;
}
//------------------------------------------------------
// #setRoom1Direction
//------------------------------------------------------
void RoomExit::setRoom1Direction(int whichDirection){
  m_room1Direction = whichDirection;
}
//------------------------------------------------------
// #setRoom2Direction
//------------------------------------------------------
void RoomExit::setRoom2Direction(int whichDirection){
  m_room2Direction = whichDirection;
}

//------------------------------------------------------
// #isCurrentRoom
//------------------------------------------------------
bool RoomExit::isCurrentRoom(Room* room) const{
  return (m_room1==room || m_room2==room);
}
//------------------------------------------------------
// #isAdjacentRoom
//------------------------------------------------------
bool RoomExit::isAdjacentRoom(Room* room) const{
  return (!isCurrentRoom(room)
      &&(m_room1->isAdjacentRoom(room)
        || m_room2->isAdjacentRoom(room)
        )
      );
}

//------------------------------------------------------
// #isBlocked
//------------------------------------------------------
bool RoomExit::isBlocked(){
  return m_isBlocked;
}
//------------------------------------------------------
// #isHidden
//------------------------------------------------------
bool RoomExit::isHidden(){
  return m_isHidden;
}
//------------------------------------------------------
// #getRoom1
//------------------------------------------------------
Room* RoomExit::getRoom1(){
  return m_room1;
}
//------------------------------------------------------
// #getRoom2
//------------------------------------------------------
Room* RoomExit::getRoom2(){
  return m_room2;
}
//------------------------------------------------------
// #getRoom1Direction
//------------------------------------------------------
int RoomExit::getRoom1Direction(){
  return m_room1Direction;
}
//------------------------------------------------------
// #getRoom2Direction
//------------------------------------------------------
int RoomExit::getRoom2Direction(){
  return m_room2Direction;
}

//------------------------------------------------------
// #display
//------------------------------------------------------
void RoomExit::display(std::ostream& o) const{
  o << "\n";
  o << "------------------------------------------------\n";
  o << getName() << "\n";
  o << "\n";
  o << "Room1: ";
  if(m_room1 != NULL){
    o << m_room1->getName() << " -" << m_room1->getRoomType() << "-\n";
  }
  else{
    o << "Null\n";
  }
  o << "Room2: ";
  if(m_room2 != NULL){
    o << m_room2->getName() << " -" << m_room2->getRoomType() << "-\n";
  }
  else{
    o << "Null\n";
  }
  o << "\n";
  o << "Blocked: ";
  if(m_isBlocked){
    o << "yes\n";
  }
  else{
    o << "no\n";
  }
  o << "Hidden: ";
  if(m_isHidden){
    o << "yes\n";
  }
  else{
    o << "no\n";
  }
  o << "------------------------------------------------";
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool RoomExit::activate(int action, int state, int direction, Object* target, int extra){
  int exitDirection;
  string exitDirectionString;

  Room* currentRoom = Character::PLAYER->getCurrentRoom();
  bool currentRoomFlag = isCurrentRoom(currentRoom);

  if(currentRoomFlag){
    exitDirection = currentRoom->getRoomExitDirection(this);
    exitDirectionString = compassDirectionToString(exitDirection, true);
  }

  switch(action){
    case BLOCK_SET:
      if(currentRoomFlag){
        if(state && !isBlocked()){
          cout << "The "
            << exitDirectionString
            << " exit slides open."
            << endl;
        }
        else if(!state && isBlocked()){
          cout << "The "
            << exitDirectionString
            << " exit slides shut."
            << endl;
        }
      }
      setBlocked(state);
      return true;

    case HIDE_SET:
      setHidden(state);
      return true;

    case BLOCK_TOGGLE:
      if(currentRoomFlag){
        if(isBlocked()){
          cout << "The "
            << exitDirectionString
            << " exit slides open."
            << endl;
        }
        else{
          cout << "The "
            << exitDirectionString
            << " exit slides shut."
            << endl;
        }
      }
      setBlocked(!isBlocked());
      return true;

    case HIDE_TOGGLE:
      setHidden(!isHidden());
      return true;

    default:
      return Object::activate(action, state, direction, target, extra);
  }
}

//------------------------------------------------------
// #operator<<
//------------------------------------------------------
std::ostream& operator<<(std::ostream& o, RoomExit& roomExit){
  roomExit.display(o);
  return o;
}
