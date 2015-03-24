
#ifndef SWITCH_H
#define SWITCH_H

#include "./../Superclasses.h"
#include "Item.h"
#include <string>

const std::string ADJACENT_SOUND = "There is a sound from a nearby room ...";
const std::string DISTANT_SOUND = "There is a sound from a distant room ...";

class Switch: public Item{
  public:
    Switch(const bool canToggle=false, const bool isOn=false, const int action=0, const int state=0, const int direction=0, Object* target=NULL);
    ~Switch();

    void setOnAction(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    void setOffAction(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    bool isOn() const;
    bool canToggle() const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

  protected:
    bool m_isOn;
    bool m_canToggle;

    int m_onAction;
    int m_onState;
    int m_onDirection;
    Object* m_onTarget;

    int m_offAction;
    int m_offState;
    int m_offDirection;
    Object* m_offTarget;
};

#endif
