
#ifndef SWITCH_H
#define SWITCH_H

#include "./../Superclasses.h"
#include "Item.h"
#include <string>

const std::string ADJACENT_SOUND = "There is a sound from a nearby room ...";
const std::string DISTANT_SOUND = "There is a sound from a distant room ...";

class Switch: public Item{
  public:
    Switch(const bool canToggle=false);
    ~Switch();

    void addOnAction(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    void addOffAction(const int action=0, const int state=0, const int direction=0, Object* target=NULL);

    void deleteLastOnAction();
    void deleteLastOffAction();

    bool isOn() const;
    bool canToggle() const;

    bool activateAll() const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

  protected:
    mutable bool m_isOn;
    bool m_canToggle;

    unsigned int m_actionMax;
    unsigned int m_onActionCount;
    unsigned int m_offActionCount;

    int* m_onActions;
    int* m_onStates;
    int* m_onDirections;
    Object** m_onTargets;

    int* m_offActions;
    int* m_offStates;
    int* m_offDirections;
    Object** m_offTargets;
};

#endif
