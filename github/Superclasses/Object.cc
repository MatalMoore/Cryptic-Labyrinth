
#include "./../Globals.h"
#include "Object.h"
#include <string>
using namespace std;

Object::Object(string title, string description, string descriptor){
  m_title = title;
  m_description = description;
  m_descriptor = descriptor;

  m_type = OBJECT;

  m_position = NO_DIRECTION;

  m_reference = this;
}

//------------------------------------------------------
// #setName
//------------------------------------------------------
void Object::setName(string name){
  m_name = name;
}
//------------------------------------------------------
// #setTitle
//------------------------------------------------------
void Object::setTitle(string title){
  m_title = title;
}
//------------------------------------------------------
// #setDescriptor
//------------------------------------------------------
void Object::setDescriptor(string descriptor){
  m_description = descriptor;
}
//------------------------------------------------------
// #setDescription
//------------------------------------------------------
void Object::setDescription(string description){
  m_description = description;
}
//------------------------------------------------------
// #setSubDescription
//------------------------------------------------------
void Object::setSubDescription(string subDescription){
  m_subDescription = subDescription;
}

//------------------------------------------------------
// #setPosition
//------------------------------------------------------
void Object::setPosition(int whichDirection){
  m_position = whichDirection;
}

//------------------------------------------------------
// #setReference
//------------------------------------------------------
void Object::setReference(Object* object){
  m_reference = object;
}

//------------------------------------------------------
// #isCurrentRoom
//------------------------------------------------------
bool Object::isCurrentRoom(Room* room) const{
  return false;
}
//------------------------------------------------------
// #isAdjecentRoom
//------------------------------------------------------
bool Object::isAdjacentRoom(Room* room) const{
  return false;
}

//------------------------------------------------------
// #getName
//------------------------------------------------------
string Object::getName() const{
  return m_name;
}
//------------------------------------------------------
// #getTitle
//------------------------------------------------------
string Object::getTitle() const{
  return m_title;
}
//------------------------------------------------------
// #getDescriptor
//------------------------------------------------------
string Object::getDescriptor() const{
  return m_descriptor;
}
//------------------------------------------------------
// #getDescription
//------------------------------------------------------
string Object::getDescription() const{
  return m_description;
}
//------------------------------------------------------
// #getSubDescription
//------------------------------------------------------
string Object::getSubDescription() const{
  return m_subDescription;
}

//------------------------------------------------------
// #getPosition
//------------------------------------------------------
int Object::getPosition() const{
  return m_position;
}

//------------------------------------------------------
// #getReference
//------------------------------------------------------
Object* Object::getReference() const{
  return m_reference;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Object::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case POSITION_SET:
      if(isGoodDirection(direction)){
        setPosition(direction);

        return true;
      }
      else{
        return false;
      }

    default:
      return false;
  }
}
