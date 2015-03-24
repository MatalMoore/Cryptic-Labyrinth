
#include "Container.h"
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------
// #Container (Constructor)
//------------------------------------------------------
Container::Container(string title, string description, string descriptor){
  m_objectMax = 10;
  m_objectNext = 0;
  m_objectCount = 0;
  m_objects = NULL;

  m_title = title;
  m_description = description;
  m_descriptor = descriptor;

  m_type = CONTAINER;
}
//------------------------------------------------------
// #~Container (Destructor)
//------------------------------------------------------
Container::~Container(){
  if(m_objects != NULL){
    delete[] m_objects;
  }
}

//------------------------------------------------------
// #addObject
//------------------------------------------------------
void Container::addObject(Object* object, int whichDirection, string subDescription){
  int i;
  string newSubDescription;
  Object* holdObject;

  if(object == NULL){
    cerr << "Error: Tried to add NULL to "
      << getName()
      << endl;

    return;
  }

  if(!isGoodDirection(whichDirection)){
    cerr << "Error adding "
      << object->getName()
      << " to "
      << getName()
      << endl;

    cerr << "Invalid direction: "
      << compassDirectionToString(whichDirection)
      << endl;

    return;
  }

  if(m_objectNext == 0){
    m_objects = new Object*[m_objectMax];
  }

  if(subDescription.empty()){
    newSubDescription = FLOOR;
  }
  else{
    if(whichDirection==CENTER && subDescription==WALL){
      newSubDescription = FLOOR;
    }
    else{
      newSubDescription = subDescription;
    }
  }

  for(i=0; i<m_objectNext; i++){
    holdObject = m_objects[i];

    if(holdObject == NULL){
      continue;
    }

    if(uppercase(object->getTitle())==uppercase(holdObject->getTitle())
        && whichDirection==holdObject->getPosition()
        &&(uppercase(newSubDescription)
          == uppercase(holdObject->getSubDescription())
          )
      ){
      cerr << "Error adding "
        << object->getName()
        << " to "
        << getName()
        << endl;

      cerr << getName()
        << " already has a "
        << uppercase(object->getTitle())
        << " in the "
        << compassDirectionToString(whichDirection)
        << " on the "
        << uppercase(newSubDescription)
        << endl;

      return;
    }
  }

  if(m_objectNext >= m_objectMax){
    Object** holdObjects = new Object*[m_objectMax*2];

    for(i=0; i<m_objectMax; i++){
      holdObjects[i] = m_objects[i];
    }

    delete[] m_objects;
    m_objects = holdObjects;
    m_objectMax *= 2;
  }

  m_objects[m_objectNext] = object;
  object->setSubDescription(newSubDescription);
  object->setReference(this);
  object->setPosition(whichDirection);

  m_objectNext++;
  m_objectCount++;
}

//------------------------------------------------------
// #getObjectCount
//------------------------------------------------------
int Container::getObjectCount() const{
  return m_objectCount;
}

//------------------------------------------------------
// #getObject
//------------------------------------------------------
Object* Container::getObject(string title, int whichDirection, string subDescription) const{
  bool objectExists = false;
  bool directionFlag;
  bool subDescriptionFlag;
  bool holdBool;

  int objectCount = 0;

  string holdTitle;

  Object* holdObject;
  Object** holdObjects = new Object*[m_objectMax];

  directionFlag = isGoodDirection(whichDirection);
  subDescriptionFlag = !subDescription.empty();

  for(int i=0; i<m_objectNext; i++){
    holdObject = m_objects[i];

    if(holdObject == NULL){
      continue;
    }

    holdTitle = holdObject->getTitle();

    if(uppercase(title) == uppercase(holdTitle)){
      holdBool = true;

      if(directionFlag){
        holdBool = (holdBool
            &&(whichDirection==holdObject->getPosition())
            );
      }

      if(subDescriptionFlag){
        holdBool = (holdBool
            &&(subDescription==holdObject->getSubDescription())
            );
      }

      if(holdBool){
        holdObjects[objectCount] = holdObject;
        objectCount++;
      }
    }
  }

  if(objectCount == 1){
    holdObject = holdObjects[0];

    delete[] holdObjects;

    return holdObject;
  }
  else{
    delete[] holdObjects;

    return NULL;
  }
}

bool Container::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case OBJECT_ADD:
      if(target == NULL){
        return false;
      }
      else{
        addObject(target, direction);

        return true;
      }

    default:
      return Object::activate(action, state, direction, target, extra);
  }
}
