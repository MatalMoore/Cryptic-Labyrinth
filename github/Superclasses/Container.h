
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Object.h"
#include <string>

class Container: public Object{
  public:
    Container(std::string name="", std::string description="");
    ~Container();

  protected:
    Object** m_objects;
};

#endif
