
#include "./../Globals.h"
#include "./../Characters.h"
#include "Switch.h"
#include <iostream>
using namespace std;


//------------------------------------------------------
// #Switch (Constructor)
//------------------------------------------------------
Switch::Switch(bool canToggle){
  m_itemType = SWITCH;

  m_isOn = false;
  m_canToggle = canToggle;

  m_actionMax = 10;
  m_onActionCount = 0;
  m_offActionCount = 0;

  m_onActions = new int[m_actionMax];
  m_onStates = new int[m_actionMax];
  m_onDirections = new int[m_actionMax];
  m_onTargets = new Object*[m_actionMax];

  m_offActions = new int[m_actionMax];
  m_offStates = new int[m_actionMax];
  m_offDirections = new int[m_actionMax];
  m_offTargets = new Object*[m_actionMax];

  m_title = "switch";
  m_descriptor = "a";
  m_description = "a switch";
}
//------------------------------------------------------
// #Switch (Destructor)
//------------------------------------------------------
Switch::~Switch(){
  delete [] m_onActions;
  delete [] m_onStates;
  delete [] m_onDirections;
  delete [] m_onTargets;

  delete [] m_offActions;
  delete [] m_offStates;
  delete [] m_offDirections;
  delete [] m_offTargets;
}

//------------------------------------------------------
// #addOnAction
//------------------------------------------------------
void Switch::addOnAction(int action, int state, int direction, Object* target){
  if(m_onActionCount >= m_actionMax){
    cerr << "Error: "
      << getName()
      << " cannot have more than "
      << m_actionMax
      << " on_actions"
      << endl;

    return;
  }

  m_onActions[m_onActionCount] = action;
  m_onStates[m_onActionCount] = state;
  m_onDirections[m_onActionCount] = direction;
  m_onTargets[m_onActionCount] = target;

  m_onActionCount++;
}

//------------------------------------------------------
// #addOffAction
//------------------------------------------------------
void Switch::addOffAction(int action, int state, int direction, Object* target){
  if(m_offActionCount >= m_actionMax){
    cerr << "Error: "
      << getName()
      << " cannot have more than "
      << m_actionMax
      << " off_actions"
      << endl;

    return;
  }

  m_offActions[m_offActionCount] = action;
  m_offStates[m_offActionCount] = state;
  m_offDirections[m_offActionCount] = direction;
  m_offTargets[m_offActionCount] = target;

  m_offActionCount++;
}

//------------------------------------------------------
// #deleteLastOnAction
//------------------------------------------------------
void Switch::deleteLastOnAction(){
    if(m_onActionCount == 0){
      return;
    }

    m_onActionCount--;
}
//------------------------------------------------------
// #deleteLastOffAction
//------------------------------------------------------
void Switch::deleteLastOffAction(){
    if(m_offActionCount == 0){
      return;
    }

    m_offActionCount--;
}

//------------------------------------------------------
// #isOn
//------------------------------------------------------
bool Switch::isOn() const{
  return m_isOn;
}
//------------------------------------------------------
// #canToggle
//------------------------------------------------------
bool Switch::canToggle() const{
  return m_canToggle;
}

//------------------------------------------------------
// #activateAll
//------------------------------------------------------
bool Switch::activateAll() const{
  int i;

  bool activateFlagHold;
  bool adjacentRoomFlagHold;
  bool distantRoomFlagHold;

  bool activateFlag = false;
  bool adjacentRoomFlag = false;
  bool distantRoomFlag = false;

  Object* objectHold;

  Room* currentRoom = Character::PLAYER->getCurrentRoom();

  if(isOn()){
    for(i=0; i<m_offActionCount; i++){
      objectHold = m_offTargets[i];

      if(objectHold == NULL){
        cerr << "Error: "
          << getName()
          << " attempted to activate a NULL m_offTargets["
          << i
          << "]"
          << endl;

        return false;
      }

      activateFlagHold = objectHold->activate(m_offActions[i], m_offStates[i], m_offDirections[i]);

      if(activateFlagHold){
        adjacentRoomFlagHold = objectHold->isAdjacentRoom(currentRoom);
        distantRoomFlagHold = (
            !objectHold->isCurrentRoom(currentRoom)
            && !adjacentRoomFlagHold
            );

        activateFlag = (activateFlag || activateFlagHold);
        adjacentRoomFlag = (adjacentRoomFlag || adjacentRoomFlagHold);
        distantRoomFlag = (distantRoomFlag || distantRoomFlagHold);
      }
    }
  }
  else{
    for(i=0; i<m_onActionCount; i++){
      objectHold = m_onTargets[i];

      if(objectHold == NULL){
        cerr << "Error: "
          << getName()
          << " attempted to activate a NULL m_onTargets["
          << i
          << "]"
          << endl;

        return false;
      }

      activateFlagHold = objectHold->activate(m_onActions[i], m_onStates[i], m_onDirections[i]);

      if(activateFlagHold){
        adjacentRoomFlagHold = objectHold->isAdjacentRoom(currentRoom);
        distantRoomFlagHold = (
            !objectHold->isCurrentRoom(currentRoom)
            && !adjacentRoomFlagHold
            );

        activateFlag = (activateFlag || activateFlagHold);
        adjacentRoomFlag = (adjacentRoomFlag || adjacentRoomFlagHold);
        distantRoomFlag = (distantRoomFlag || distantRoomFlagHold);
      }
    }
  }

  if(activateFlag){
    if(canToggle()){
      m_isOn = !m_isOn;
    }

    if(adjacentRoomFlag){
      cout << ADJACENT_SOUND << endl;
    }

    if(distantRoomFlag){
      cout << DISTANT_SOUND << endl;
    }
  }

  return activateFlag;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Switch::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case DEFAULT_ACTION:
      return activate(SWITCH_PRESS);

    case ON_ACTION_ADD:
      addOnAction(extra, state, direction, target);
      return (m_onActionCount >= m_actionMax);

    case OFF_ACTION_ADD:
      addOffAction(extra, state, direction, target);
      return (m_offActionCount >= m_actionMax);

    case SWITCH_PRESS:
      return activateAll();

    default:
      return Item::activate(action, state, direction, target, extra);
  }
}
