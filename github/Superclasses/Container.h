
#ifndef CONTAINER_H
#define CONTAINER_H

#include "./../Globals.h"
#include "Object.h"
#include <string>

class Container: public Object{
  public:
    Container(const std::string title="", const std::string description="", const std::string descriptor="");
    ~Container();

    void addObject(Object* object, const int whichDirection=CENTER, const std::string subDescription="");

    int getObjectCount() const;

    Object* getObject(const std::string title, const int whichDirection=NO_DIRECTION, const std::string subDescription="") const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

  protected:
    unsigned int m_objectMax;
    unsigned int m_objectNext;
    unsigned int m_objectCount;
    Object** m_objects;
};

#endif
