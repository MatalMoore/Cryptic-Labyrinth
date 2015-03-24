
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Room;

class Object{
  public:
    Object(const std::string title="", const std::string description="", const std::string descriptor="");
    ~Object(){}

    void setName(const std::string description);
    void setTitle(const std::string description);
    void setDescriptor(const std::string description);
    void setDescription(const std::string description);
    void setSubDescription(const std::string description);

    void setPosition(const int whichDirection);

    void setReference(Object* object);

    virtual bool isCurrentRoom(Room* room) const;
    virtual bool isAdjacentRoom(Room* room) const;

    std::string getName() const;
    std::string getTitle() const;
    std::string getDescriptor() const;
    std::string getDescription() const;
    std::string getSubDescription() const;
    std::string getType() const;

    int getPosition() const;

    Object* getReference() const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

  protected:
    std::string m_name;
    std::string m_title;
    std::string m_descriptor;
    std::string m_description;
    std::string m_subDescription;
    std::string m_type;

    int m_position;

    Object* m_reference;
};

#endif
