
#include "./../Globals.h"
#include "./../Characters.h"
#include "Switch.h"
#include <iostream>
using namespace std;


//------------------------------------------------------
// #Switch (Constructor)
//------------------------------------------------------
Switch::Switch(bool canToggle, bool isOn, int action, int state, int direction, Object* target){
  m_itemType = SWITCH;

  m_isOn = isOn;
  m_canToggle = canToggle;

  m_onAction = action;
  m_onState = state;
  m_onDirection = direction;
  m_onTarget = target;

  m_offAction = m_onAction;
  m_offState = m_onState;
  m_offDirection =  m_onDirection;
  m_offTarget = m_onTarget;

  m_title = "switch";
  m_descriptor = "a";
  m_description = "a switch";
}
//------------------------------------------------------
// #Switch (Destructor)
//------------------------------------------------------
Switch::~Switch(){
}

//------------------------------------------------------
// #setOnAction
//------------------------------------------------------
void Switch::setOnAction(int action, int state, int direction, Object* target){
  m_onAction = action;
  m_onState = state;
  m_onDirection = direction;
  m_onTarget = target;
}

//------------------------------------------------------
// #setOffAction
//------------------------------------------------------
void Switch::setOffAction(int action, int state, int direction, Object* target){
  m_offAction = action;
  m_offState = state;
  m_offDirection = direction;
  m_offTarget = target;
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
// #activate
//------------------------------------------------------
bool Switch::activate(int action, int state, int direction, Object* target, int extra){
  bool activateFlag;
  Object* roomCheckTarget;

  switch(action){
    case(DEFAULT_ACTION):
      return activate(SWITCH_PRESS);

    case(ON_ACTION_SET):
      setOnAction(extra, state, direction, target);
      return true;

    case(OFF_ACTION_SET):
      setOffAction(extra, state, direction, target);
      return true;

    case SWITCH_PRESS:
      if(canToggle()){
        if(isOn()){
          if(m_offTarget == NULL){
            cerr << "Error: "
              << getName()
              << " attempted to actiavte a NULL m_offTarget"
              << endl;

            return false;
          }

          activateFlag = m_offTarget->activate(m_offAction, m_offState, m_offDirection);
          cerr << "Toggled off" << endl;
          roomCheckTarget = m_offTarget;
        }
        else{
          if(m_onTarget == NULL){
            cerr << "Error: "
              << getName()
              << " attempted to actiavte a NULL m_onTarget"
              << endl;

            return false;
          }

          activateFlag = m_onTarget->activate(m_onAction, m_onState, m_onDirection);
          roomCheckTarget = m_onTarget;
        }

        if(activateFlag){
          m_isOn = !isOn();
        }
      }
      else{
        if(m_onTarget == NULL){
          cerr << "Error: "
            << getName()
            << " attempted to actiavte a NULL m_onTarget"
            << endl;

          return false;
        }

        activateFlag =  m_onTarget->activate(m_onAction, m_onState, m_onDirection);
        roomCheckTarget = m_onTarget;
      }

      if(activateFlag){
        if(roomCheckTarget->isAdjacentRoom(Character::PLAYER->getCurrentRoom())){
          cout << ADJACENT_SOUND << endl;
        }
        else if(!roomCheckTarget->isCurrentRoom(Character::PLAYER->getCurrentRoom())){
          cout << DISTANT_SOUND << endl;
        }
      }

      return activateFlag;

    default:
      return Item::activate(action, state, direction, target, extra);
  }
}
