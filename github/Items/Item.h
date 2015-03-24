
#ifndef ITEM_H
#define ITEM_H

#include "./../Superclasses.h"
#include <string>

class Item: public Container{
  public:
    Item(const bool isObtainable=false, const bool isObtained=false, const std::string description="");
    ~Item();

    void setObtainable(const bool boolean);
    void setObtained(const bool boolean);

    bool isObtainable() const;
    bool isObtained() const;

    std::string getItemType() const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

    static unsigned int getNextItemID(){return s_nextItemID;}
    static unsigned int getItemCount(){return s_itemCount;}
    static unsigned int getItemMax(){return s_itemMax;}
    static Item* getItemFromID(const unsigned int itemID){return s_items[itemID];}

  protected:
    bool m_isObtainable;
    bool m_isObtained;

    unsigned int m_itemID;
    std::string m_itemType;

    static unsigned int s_nextItemID;
    static unsigned int s_itemCount;
    static unsigned int s_itemMax;
    static Item** s_items;
};

#endif
