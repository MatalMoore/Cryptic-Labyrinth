
#include "Room.h"
#include "RotatingRoom.h"
#include "./../Globals.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

unsigned int Room::s_nextRoomID;
unsigned int Room::s_roomCount = 0;
unsigned int Room::s_roomMax;
Room** Room::s_rooms;

//------------------------------------------------------
// #Room (Constructor)
//------------------------------------------------------
Room::Room(bool isVisible, bool* whichExits, string description){
  if(s_roomCount == 0){
    s_nextRoomID = 0;
    s_roomMax = 100;
    s_rooms = new Room*[s_roomMax];
    if(SHOW_MESSAGES){
      cerr << "s_rooms: Allocated" << endl
        << endl;
    }
  }

  s_roomCount++;

  m_type = ROOM;

  m_roomType = ROOM;
  m_maxExits = 4;

  stringstream charsOfID;

  charsOfID.width(4);
  charsOfID.fill('0');

  m_roomID = s_nextRoomID++;
  if(m_roomID >= s_roomMax){
    Room** roomsHold = new Room*[s_roomMax*2];
    for(int i=0; i<s_roomMax; i++){
      roomsHold[i] = s_rooms[i];
      roomsHold[s_roomMax+i] = NULL;
      s_rooms[i] = NULL;
    }
    delete[] s_rooms;
    s_rooms = roomsHold;
    s_roomMax *= 2;
  }
  s_rooms[m_roomID] = this;

  charsOfID << m_roomID;
  charsOfID >> m_name;

  m_name.insert(0, "Room");

  if(SHOW_MESSAGES){
    cerr << m_name << ": Creating" << endl;
  }

  m_visibility = isVisible;

  if(whichExits == NULL){
    m_whichExits = new bool[getMaxExits()];
    for(int i=0; i<getMaxExits(); i++){
      m_whichExits[i] = false;
    }
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

  m_title = "room";
  m_descriptor = "a";

  if(description.empty()){
    m_description = "You are in a square room.";
  }
  else{
    m_description = description;
  }

  if(SHOW_MESSAGES){
    cerr << m_name << ": Created" << endl
      << endl;
  }
}
//------------------------------------------------------
// #~Room (Destructor)
//------------------------------------------------------
Room::~Room(){
  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleting" << " -" << getRoomType() << "-" << endl;
  }

  //cerr << "maxExits: " << getMaxExits() << endl;
#if 0
  cerr << "Before:" << endl;
  for(int i=0; i<getMaxExits(); i++){
    if(m_exits[i] != NULL){
      cerr << i << ": ";
      if(m_exits[i]->getRoom1() == NULL){
        cerr << "NULL";
      }
      else{
        cerr << m_exits[i]->getRoom1()->getName();
      }

      cerr << " - ";

      if(m_exits[i]->getRoom2() == NULL){
        cerr << "NULL";
      }
      else{
        cerr << m_exits[i]->getRoom2()->getName();
      }

      cerr << endl;
    }
  }
#endif

  for(int i=0; i<getMaxExits(); i++){
    if(m_exits[i] != NULL){
      if(m_exits[i]->getRoom1() == this){
        m_exits[i]->setRoom1(NULL);

        if(m_exits[i]->getRoom2() == NULL){
          delete m_exits[i];
          m_exits[i] = NULL;
        }
      }
      else if(m_exits[i]->getRoom2() == this){
        m_exits[i]->setRoom2(NULL);

        if(m_exits[i]->getRoom1() == NULL){
          delete m_exits[i];
          m_exits[i] = NULL;
        }
      }
    }
  }

#if 0
  cerr << "After:" << endl;
  for(int i=0; i<getMaxExits(); i++){
    if(m_exits[i] != NULL){
      cerr << i << ": ";
      if(m_exits[i]->getRoom1() == NULL){
        cerr << "NULL";
      }
      else{
        cerr << m_exits[i]->getRoom1()->getName();
      }
      cerr << " - ";
      if(m_exits[i]->getRoom2() == NULL){
        cerr << "NULL";
      }
      else{
        cerr << m_exits[i]->getRoom2()->getName();
      }
      m_exits[i]->getRoom2();
      cerr << endl;
    }
  }
#endif

  s_rooms[m_roomID] = NULL;
  delete[] m_exits;

  s_roomCount--;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleted" << endl
      << endl;
  }

  if(s_roomCount == 0){
    delete[] s_rooms;
    if(SHOW_MESSAGES){
      cerr << "s_rooms: Deallocated" << endl
        << endl;
    }
  }
}

//------------------------------------------------------
// #setExit
//------------------------------------------------------
void Room::setExit(int whichDirection, RoomExit* roomExit){
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "setExit");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
  m_exits[directionToIndex(whichDirection)] = roomExit;
  m_whichExits[directionToIndex(whichDirection)] = (roomExit!=NULL);
}
//------------------------------------------------------
// #setExitBlocked
//------------------------------------------------------
void Room::setExitBlocked(int whichDirection, bool boolean) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "setExitBlocked");

    return;
  }
  if(!exitExists(whichDirection)){
    displayNullInput(whichDirection, "setExitBlocked");

    return;
  }
  m_exits[directionToIndex(whichDirection)]->setBlocked(boolean);
}
//------------------------------------------------------
// #setExitHidden
//------------------------------------------------------
void Room::setExitHidden(int whichDirection, bool boolean) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "setExitHidden");

    return;
  }
  if(!exitExists(whichDirection)){
    displayNullInput(whichDirection, "setExitHidden");

    return;
  }
  m_exits[directionToIndex(whichDirection)]->setHidden(boolean);
}
//------------------------------------------------------
// #setRoom
//------------------------------------------------------
void Room::setRoom(int whichDirection, Room* room) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "setRoom");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
  if(exitExists(whichDirection))
    if(isThisRoom1OfExit(whichDirection)){
      m_exits[directionToIndex(whichDirection)]->setRoom2(room);
    }
    else{
      m_exits[directionToIndex(whichDirection)]->setRoom1(room);
    }
  else{
    displayNullInput(whichDirection, "setRoom");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
}
//------------------------------------------------------
// #setVisible
//------------------------------------------------------
void Room::setVisible(bool isVisible){
  m_visibility = isVisible;
}
//------------------------------------------------------
// #createRoom
//------------------------------------------------------
void Room::createRoom(int whichDirection){
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "createRoom");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
  if(getRoom(whichDirection) != NULL){
    return;
  }
  linkRooms(whichDirection);
}
//------------------------------------------------------
// #deleteRoom
//------------------------------------------------------
void Room::deleteRoom(int whichDirection, bool isExitDeleted){
  RoomExit* roomExitHold = NULL;
  Room* roomHold = NULL;

  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "deleteRoom");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }

  if(exitExists(whichDirection)){
    if(getRoom(whichDirection) != NULL){
      delete getRoom(whichDirection);
      //~Room() sets the apporopriate value to NULL, etc.
    }
    if(isExitDeleted){
      delete m_exits[directionToIndex(whichDirection)];
      //~RoomExit() sets the apporopriate value to NULL, etc.
    }
  }
  else{
    return;
  }
}
//------------------------------------------------------
// #linkRooms
//------------------------------------------------------
void Room::linkRooms(int whichDirection, Room* room, RoomExit* roomExit, int toWhichDirection){
#if 0
  cerr << "==========" << endl;
      cerr << getName() << "->linkRooms("
      << compassDirectionToString(whichDirection)
      << ", " << room->getName() << ", "
      << compassDirectionToString(toWhichDirection)
      << ", " << roomExit << ")" << endl;
  cerr << "==========" << endl;
#endif
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "linkRooms");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
  if(toWhichDirection == OPPOSITE){
    toWhichDirection = oppositeDirection(whichDirection);
  }
  else if(!room->isInputValid(toWhichDirection)){
    room->displayInvalidInput(toWhichDirection, "linkRooms");
    cerr << "Error linking from " << getName() << " - Exiting ..." << endl;
    exit(2);

    return;
  }
  if(roomExists(whichDirection)){
    displayInvalidInput(whichDirection, "linkRooms");
    cerr << "Error: Room exists - Exiting ..." << endl;
    exit(2);

    return;
  }

  if(room == NULL){
    room = new Room;
  }

  //cerr << "Linking " << getName() << " to " << room->getName() << endl;

  if(!room->isInputValid(toWhichDirection)){
    room->displayInvalidInput(toWhichDirection, "linkRooms");
    cerr << "Exiting ..." << endl;
    exit(2);
    delete room;

    return;
  }

  if(roomExit == NULL){
    if(exitExists(whichDirection)){
      if(room->exitExists(toWhichDirection)){
        delete getExit(whichDirection);
      }
      setExit(whichDirection, room->getExit(toWhichDirection));
    }
    else if(room->exitExists(toWhichDirection)){
      setExit(whichDirection, room->getExit(toWhichDirection));
    }
    else{
      setExit(whichDirection, new RoomExit);
      room->setExit(toWhichDirection, getExit(whichDirection));
    }
    getExit(whichDirection)->setRoom1(this);
    getExit(whichDirection)->setRoom2(room);
  }
  else{
    if(roomExit->getRoom1()!=NULL || roomExit->getRoom2()!=NULL){
      cerr << roomExit->getName() << " contains a non-NULL Room" << endl;
      cerr << *roomExit << endl;

      return;
    }

    roomExit->setRoom1(this);
    roomExit->setRoom2(room);

    setExit(whichDirection, roomExit);
    room->setExit(toWhichDirection, roomExit);
  }
}

//------------------------------------------------------
// #linkRooms
//------------------------------------------------------
void Room::linkRooms(int whichDirection, int roomID, RoomExit* roomExit, int toWhichDirection){
  linkRooms(whichDirection, Room::getRoomFromID(roomID), roomExit, toWhichDirection);
}

//------------------------------------------------------
// #linkRooms
//------------------------------------------------------
void Room::linkRooms(int whichDirection, int roomID, int roomExitID, int toWhichDirection){
  linkRooms(whichDirection, Room::getRoomFromID(roomID), RoomExit::getRoomExitFromID(roomExitID), toWhichDirection);
}

//------------------------------------------------------
// #unlinkRooms 
//------------------------------------------------------
void Room::unlinkRooms(int whichDirection, bool isExitDeleted){

  RoomExit* sharedExit = NULL;
  Room* roomHold = NULL;
  int directionHold;

  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "unlinkRooms");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }
  if(getExit(whichDirection) == NULL){
    displayNullInput(whichDirection, "unlinkRooms");
    cerr << "Exiting ..." << endl;
    exit(2);

    return;
  }

  sharedExit = getExit(whichDirection);

  if(sharedExit->getRoom1() == this){
    if(sharedExit->getRoom2() == NULL){
      //cerr << sharedExit->getName() << ": Room2: NULL" << endl;
      return;
    }
    roomHold = sharedExit->getRoom2();
  }
  if(sharedExit->getRoom2() == this){
    if(sharedExit->getRoom1() == NULL){
      //cerr << sharedExit->getName() << ": Room1: NULL" << endl;
      return;
    }
    roomHold = sharedExit->getRoom1();
  }

  setExit(whichDirection, NULL);
  if(roomHold != NULL){
    directionHold = roomHold->getRoomExitDirection(sharedExit);
    roomHold->setExit(directionHold, NULL);
  }

  sharedExit->setRoom1(NULL);
  sharedExit->setRoom2(NULL);

  if(isExitDeleted){
    delete sharedExit;
  }
}

//------------------------------------------------------
// #exitExists
//------------------------------------------------------
bool Room::exitExists(int whichDirection) const{
  return m_whichExits[directionToIndex(whichDirection)];
}
//------------------------------------------------------
// #roomExists
//------------------------------------------------------
bool Room::roomExists(int whichDirection) const{
  if(getRoom(whichDirection) == NULL){
    return false;
  }
  else{
    return true;
  }
}
//------------------------------------------------------
// #isInputValid
//------------------------------------------------------
bool Room::isInputValid(int whichDirection) const{
  for(int i=0; i<getMaxExits(); i++){
    if(getRoomExitDirection(i) == whichDirection){
      return true;
    }
  }

  return false;
}
//------------------------------------------------------
// #isExitBlocked
//------------------------------------------------------
bool Room::isExitBlocked(int whichDirection) const{
  int toWhichDirection;
  Room* roomHold;
  RoomExit* roomExitHold;

  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "isExitBlocked");

    return false;
  }

  if(exitExists(whichDirection)){
    roomHold = getRoom(whichDirection);

    if(roomHold->getRoomType() == ROTATING_ROOM){
      roomExitHold = getExit(whichDirection);
      toWhichDirection = roomHold->getRoomExitDirection(roomExitHold);

      return roomHold->isExitBlocked(toWhichDirection);
    }
    else{
      return m_exits[directionToIndex(whichDirection)]->isBlocked();
    }
  }
  else{
    return false;
  }
}
//------------------------------------------------------
// #isExitHidden
//------------------------------------------------------
bool Room::isExitHidden(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    //displayInvalidInput(whichDirection, "isExitHidden");
    return true;
  }
  if(exitExists(whichDirection)){
    return m_exits[directionToIndex(whichDirection)]->isHidden();
  }
  else{
    return false;
  }
//------------------------------------------------------
// #isExitAccessible
//------------------------------------------------------
}
bool Room::isExitAccessible(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "isExitAccessible");

    return false;
  }

  Room* room = getRoom(whichDirection);

  if(room->getRoomType() == ROTATING_ROOM){
    RoomExit* roomExit = getExit(whichDirection);
    int toWhichDirection = room->getRoomExitDirection(roomExit);

    return room->isExitAccessible(toWhichDirection);
  }
  else{
    return true;
  }
}
//------------------------------------------------------
// #isThisRoom1OfExit
//------------------------------------------------------
bool Room::isThisRoom1OfExit(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "isThisRoom1OfExit");

    return false;
  }

  return m_exits[directionToIndex(whichDirection)]->getRoom1()==this;
}
//------------------------------------------------------
// #isAdjacentRoom
//------------------------------------------------------
bool Room::isCurrentRoom(Room* room) const{
  return (this == room);
}
//------------------------------------------------------
// #isAdjacentRoom
//------------------------------------------------------
bool Room::isAdjacentRoom(Room* room) const{
  if(room == NULL){
    displayNullInput(NO_DIRECTION, "isAdjacentRoom");

    return false;
  }

  for(int i=0; i<m_maxExits; i++){
    if(getRoom(getRoomExitDirection(i)) == room){
      return true;
    }
  }

  return false;
}
//------------------------------------------------------
// #isVisible
//------------------------------------------------------
bool Room::isVisible() const{
  return m_visibility;
}
//------------------------------------------------------
// #areThereNoExits
//------------------------------------------------------
bool Room::areThereNoExits() const{
  for(int i=0; i<getMaxExits(); i++){
    if(m_whichExits[i]){
      return false;
    }
  }

  return true;
}
//------------------------------------------------------
// #areAllExitsHidden
//------------------------------------------------------
bool Room::areAllExitsHidden() const{
  for(int i=0; i<getMaxExits(); i++){
    if(exitExists(getRoomExitDirection(i))){
      if(!isExitHidden(getRoomExitDirection(i))){
        return false;
      }
    }
  }

  return true;
}
//------------------------------------------------------
// #getMaxExits
//------------------------------------------------------
int Room::getMaxExits() const{
  return m_maxExits;
}

//------------------------------------------------------
// #getExit
//------------------------------------------------------
RoomExit* Room::getExit(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "getExit");

    return NULL;
  }

  return m_exits[directionToIndex(whichDirection)];
}
//------------------------------------------------------
// #getRoom
//------------------------------------------------------
Room* Room::getRoom(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "getRoom");

    return NULL;
  }
  if(exitExists(whichDirection)){
    if(isThisRoom1OfExit(whichDirection)){
      return m_exits[directionToIndex(whichDirection)]->getRoom2();
    }
    else{
      return m_exits[directionToIndex(whichDirection)]->getRoom1();
    }
  }
  else{
    return NULL;
  }
}
//------------------------------------------------------
// #exitsToString
//------------------------------------------------------
string Room::exitsToString() const{
  return "wawa";
  if(areAllExitsHidden() || areThereNoExits()){
    return "There are no obvious exits.";
  }
  else{
    string returnString = "Obvious exits are:";
    for(int i=0; i<getMaxExits(); i++){
      if(exitExists(i) && !isExitHidden(i)){
        returnString = returnString + "  " + compassDirectionToString(i);
      }
    }
    for(int i=0; i<getMaxExits(); i++){
      if(exitExists(i) && isExitBlocked(i)){
        string direction = compassDirectionToString(i);
        returnString = returnString + "\n" + direction + " exit is blocked.";
      }
    }
    return returnString;
  }
}
//------------------------------------------------------
// #getRoomType
//------------------------------------------------------
string Room::getRoomType() const{
  return m_roomType;
}

//------------------------------------------------------
// #directionToIndex
//------------------------------------------------------
int Room::directionToIndex(int whichDirection) const{
  return whichDirection/E;
}
//------------------------------------------------------
// #getRoomExitDirection
//------------------------------------------------------
int Room::getRoomExitDirection(RoomExit* exit) const{
  if(exit == NULL){
    displayNullInput(NO_DIRECTION, "getRoomExitDirection");

    return NO_DIRECTION;
  }
  else{
    for(int i=0; i<getMaxExits(); i++){
      if(exit == m_exits[i]){
        return getRoomExitDirection(i);
      }
    }
    cerr << getName() << " does not contain " << exit->getName() << endl;

    return NO_DIRECTION;
  }
}

//------------------------------------------------------
// #displayInvalidInput
//------------------------------------------------------
void Room::displayInvalidInput(int whichDirection, string methodName) const{
  cerr << "Invalid input: "
    << getName()
    << "->"
    << methodName
    << "("
    << compassDirectionToString(whichDirection)
    << ") -"
    << getRoomType()
    << "-"
    << endl;
}
//------------------------------------------------------
// #displayNullInput
//------------------------------------------------------
void Room::displayNullInput(int whichDirection, string methodName) const{
  cerr << "Null pointer: "
    << getName()
    << "->"
    << methodName
    << "("
    << compassDirectionToString(whichDirection)
    << ") -"
    << getRoomType()
    << "-" << endl;
}
//------------------------------------------------------
// #displayExits
//------------------------------------------------------
void Room::displayExits(std::ostream& o) const{
  if(areAllExitsHidden() || areThereNoExits()){
    o << "There are no obvious exits.";
    return;
  }
  else{
    string* exitStrings = new string[getMaxExits()];
    int whichString = 0;

    o << "Obvious exits are: ";
    for(int i=0; i<getMaxExits(); i++){
      if(
          exitExists(getRoomExitDirection(i))
          && !isExitHidden(getRoomExitDirection(i))
        ){
        exitStrings[whichString] = compassDirectionToString(getRoomExitDirection(i), false);
        whichString++;
      }
    }
    o << stringsToSequence(exitStrings, whichString);
    for(int i=0; i<getMaxExits(); i++){
      if(
          exitExists(getRoomExitDirection(i))
          && isExitBlocked(getRoomExitDirection(i))
          && !isExitHidden(getRoomExitDirection(i))
        ){
        o << "\n";
        o << "The "
          << compassDirectionToString(getRoomExitDirection(i))
          << " exit is blocked.";
      }
    }
  }

  return;
}
//------------------------------------------------------
// #displayObjects
//------------------------------------------------------
void Room::displayObjects(std::ostream& o) const{
  if(m_objectCount > 0){
    int whichDirection;
    string holdString;
    Object* holdObject;

    for(int i=0; i<m_objectNext; i++){
      holdObject = m_objects[i];

      if(holdObject == NULL){
        continue;
      }

      whichDirection = holdObject->getPosition();

      o << "There is "
        << holdObject->getDescription()
        << " in the ";

      if(whichDirection==CENTER
          || isNaturalDirection(whichDirection)
        ){
        o << compassDirectionToString(whichDirection, true);
      }
      else{
        o << compassDirectionToString(whichDirection, false);
      }

      o << " of the room";

      holdString = holdObject->getSubDescription();

      if(!holdString.empty()){
        o << " on the "
          << holdString;
      }

      o << ".\n";
    }
  }
  else{
    return;
  }
}
//------------------------------------------------------
// #display
//------------------------------------------------------
void Room::display(std::ostream& o) const{
  o << "\n";
  o << DISPLAY_LINE << "\n";
  o << getDescription() << "\n";
  if(m_objectCount > 0){
    o << "\n";
    displayObjects(o);
  }
  o << "\n";
  displayExits(o);
  o << "\n";
  o << DISPLAY_LINE;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Room::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case BLOCK_SET:
    case HIDE_SET:
    case BLOCK_TOGGLE:
    case HIDE_TOGGLE:
      if(exitExists(direction)){
        return getExit(direction)->activate(action, state, direction, target, extra);
      }
      else{
        return false;
      }

    case VISIBLE_SET:
      setVisible(state);
      return true;

    default:
      return Container::activate(action, state, direction, target, extra);
  }
}

//------------------------------------------------------
// #operator<<
//------------------------------------------------------
std::ostream& operator<<(std::ostream& o, Room& room){
  if(room.isVisible()){
    room.display(o);
  }
  else{
    o << "\n";
    o << DISPLAY_LINE << "\n";
    o << "You are in some kind of room.\n";
    o << "\n";
    o << "The room is dark.\n";
    o << "You cannot see whether there are any exits.\n";
    o << DISPLAY_LINE;
  }

  return o;
}
