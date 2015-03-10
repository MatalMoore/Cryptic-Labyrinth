
#include "Object.h"
#include <string>
using namespace std;

Object::Object(string name, string description){
  m_name = name;
  m_description = description;
}

//------------------------------------------------------
// #setName
//------------------------------------------------------
void Object::setName(string name){
  m_name = name;
}
//------------------------------------------------------
// #setDescription
//------------------------------------------------------
void Object::setDescription(string description){
  m_description = description;
}

//------------------------------------------------------
// #getName
//------------------------------------------------------
string Object::getName() const{
  return m_name;
}
//------------------------------------------------------
// #getDescription
//------------------------------------------------------
string Object::getDescription() const{
  return m_description;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Object::activate(int arg0, int arg1, int arg2, Object* argObj){
}
