
#include "./../Globals.h"
#include "./../Rooms.h"
#include "Character.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

unsigned int Character::s_nextCharacterID;
unsigned int Character::s_characterCount = 0;
unsigned int Character::s_characterMax;
Character** Character::s_characters;

const Character* Character::PLAYER = new Character;

//-----------------------------------------------------
// #Character (Constructor)
//------------------------------------------------------
Character::Character(Room* initialRoom, int initialPosition, int initialFacing){
  if(s_characterCount == 0){
    s_nextCharacterID = 0;
    s_characterMax = 100;
    s_characters = new Character*[s_characterMax];
    if(SHOW_MESSAGES){
      cout << "-!- " << SHOW_MESSAGES << " -!-" << endl;
      cerr << "s_characters: Allocated" << endl
        << endl;
    }
  }

  s_characterCount++;

  m_characterType = CHARACTER;

  stringstream charsOfID;

  charsOfID.width(4);
  charsOfID.fill('0');

  m_characterID = s_nextCharacterID++;
  if(m_characterID >= s_characterMax){
    Character** charactersHold = new Character*[s_characterMax*2];
    for(int i=0; i<s_characterMax; i++){
      charactersHold[i] = s_characters[i];
      charactersHold[s_characterMax+i] = NULL;
      s_characters[i] = NULL;
    }
    delete[] s_characters;
    s_characters = charactersHold;
    s_characterMax *= 2;
  }
  s_characters[m_characterID] = this;

  charsOfID << m_characterID;
  charsOfID >> m_name;

  m_name.insert(0, "Character");

  if(SHOW_MESSAGES){
    cerr << m_name << ": Creating" << endl;
  }

  m_currentRoom = initialRoom;
  m_position = initialPosition;
  m_facing = initialFacing;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Created" << endl
      << endl;
  }
}
//------------------------------------------------------
// #~Character (Destructor)
//------------------------------------------------------
Character::~Character(){
  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleting -" << getCharacterType() << "-" << endl;
  }

  s_characters[m_characterID] = NULL;

  s_characterCount--;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleted" << endl
      << endl;
  }

  if(s_characterCount == 0){
    delete[] s_characters;
    if(SHOW_MESSAGES){
      cerr << "s_characters: Deallocated" << endl
        << endl;
    }
  }
}

//------------------------------------------------------
// #setPosition
//------------------------------------------------------
void Character::setPosition(int whichDirection) const{
  if(whichDirection<CENTER || whichDirection>NNE){
    cerr << "Error: Cannot set position of " << getName() << " to " << compassDirectionToString(whichDirection) << endl;
    return;
  }
  m_position = whichDirection;
}
//------------------------------------------------------
// #setFacing
//------------------------------------------------------
void Character::setFacing(int whichDirection) const{
  if(whichDirection<N || whichDirection>NNE){
    cerr << "Error: Cannot set facing of " << getName() << " to " << compassDirectionToString(whichDirection) << endl;
    return;
  }
  m_facing = whichDirection;
}
//------------------------------------------------------
// #setCurrentRoom
//------------------------------------------------------
void Character::setCurrentRoom(Room* room) const{
  if(room == NULL){
    cerr << "Error: Cannot set current room  of " << getName() << " to NULL" << endl;
    return;
  }
  m_currentRoom = room;
}

//------------------------------------------------------
// #isCurrentRoom
//------------------------------------------------------
bool Character::isCurrentRoom(Room* room) const{
  return (m_currentRoom == room);
}
//------------------------------------------------------
// #isAdjacentRoom
//------------------------------------------------------
bool Character::isAdjacentRoom(Room* room) const{
  if(m_currentRoom == NULL){
    return false;
  }
  else{
    return m_currentRoom->isAdjacentRoom(room);
  }
}

//------------------------------------------------------
// #getPosition
//------------------------------------------------------
unsigned int Character::getPosition() const{
  return m_position;
}
//------------------------------------------------------
// #getFacing
//------------------------------------------------------
unsigned int Character::getFacing() const{
  return m_facing;
}
//------------------------------------------------------
// #getCurrentRoom
//------------------------------------------------------
Room* Character::getCurrentRoom() const{
  return m_currentRoom;
}

//------------------------------------------------------
// #positionToString
//------------------------------------------------------
string Character::positionToString() const{
  return compassDirectionToString(m_position, true);
}
//------------------------------------------------------
// #facingToString
//------------------------------------------------------
string Character::facingToString() const{
  return compassDirectionToString(m_facing, true);
}

//------------------------------------------------------
// #displayCurrentRoom
//------------------------------------------------------
void Character::displayCurrentRoom() const{
  if(getCurrentRoom() == NULL){
    return;
  }
  cout << *getCurrentRoom() << endl;
}

//------------------------------------------------------
// #getCharacterType
//------------------------------------------------------
string Character::getCharacterType() const{
  return m_characterType;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Character::activate(int action, int state, int direction, Room* target, int extra){
  switch(action){
    case POSITION_SET:
      setPosition(state);
      return true;

    case FACE_SET:
      setFacing(state);
      return true;

    case ROOM_SET:
      setCurrentRoom(target);
      return true;

    default:
      return Container::activate(action, state, direction, target);
  }
}
