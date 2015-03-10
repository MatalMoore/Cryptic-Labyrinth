
#ifndef CHARACTER_H
#define CHARACTER_H

#include "./../Superclasses.h"
#include "./../Rooms.h"
#include <string>

class Character: public Container{
  public:
    Character(Room* initialRoom=NULL, const int initialPosition=CENTER, const int initialFacing=N);
    ~Character();

    void setPosition(int whichDirection) const;
    void setFacing(int whichDirection) const;
    void setCurrentRoom(Room* room) const;

    unsigned int getPosition() const;
    unsigned int getFacing() const ;
    Room* getCurrentRoom() const;

    std::string positionToString() const;
    std::string facingToString() const;

    void displayCurrentRoom() const;

    std::string getCharacterType() const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Room* target=NULL);

    static unsigned int getNextCharacterID(){return s_nextCharacterID;}
    static unsigned int getCharacterCount(){return s_characterCount;}
    static unsigned int getCharacterMax(){return s_characterMax;}
    static Character* getCharacterFromID(unsigned int characterID){return s_characters[characterID];}

  protected:
    mutable unsigned int m_position;
    mutable unsigned int m_facing;
    mutable Room* m_currentRoom;

    unsigned int m_characterID;
    std::string m_characterType;

    static unsigned int s_nextCharacterID;
    static unsigned int s_characterCount;
    static unsigned int s_characterMax;
    static Character** s_characters;
};

#endif
