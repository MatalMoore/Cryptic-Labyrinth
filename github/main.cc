
#include "Globals.h"
#include "Superclasses.h"
#include "Rooms.h"
#include "Items.h"
#include "Characters.h"
#include "System.h"
#include <iostream>
using namespace std;

int main(){
  bool exitFlag = false;

  string input;

  cout << endl;
  cout << "Initializing ..." << endl;
  cout << endl;

  cout << "Room* myRoom = new RoundRoom;" << endl;
  Room* myRoom = new RoundRoom;

  cout << "Room* room1 = new Room;" << endl;
  Room* room1 = new Room;

  cout << "Room* room2 = new RoundRoom;" << endl;
  Room* room2 = new RoundRoom;

  cout << "myRoom->linkRooms(N, room2);" << endl;
  myRoom->linkRooms(N, room2);

  cout << "room2->linkRooms(W, room1);" << endl;
  room2->linkRooms(W, room1);

  cout << "myRoom->linkRooms(W, new RoundRoom);" << endl;
  myRoom->linkRooms(W, new RoundRoom);

  cout << "myRoom->getRoom(W)->linkRooms(N, room1);" << endl;
  myRoom->getRoom(W)->linkRooms(N, room1);

  cout << "myRoom->linkRooms(S, new CorridorRoom(S));" << endl;
  myRoom->linkRooms(S, new CorridorRoom(S));

  cout << "myRoom->linkRooms(NE, new RotatingRoom(NE));" << endl;
  myRoom->linkRooms(NE, new RotatingRoom(NE));

  cout << "myRoom->getRoom(N)->setVisible(false);" << endl;
  myRoom->getRoom(N)->setVisible(false);

  cout << "myRoom->linkRooms(E, new RoundRoom);" << endl;
  myRoom->linkRooms(E, new RoundRoom);

  cout << "myRoom->setExitBlocked(NE, false);" << endl;
  myRoom->setExitBlocked(NE, false);

  cout << "myRoom->linkRooms(SE, new DiagonalRoom);" << endl;
  myRoom->linkRooms(SE, new DiagonalRoom);

  cout << "myRoom->linkRooms(NW, new DiagonalRoom);" << endl;
  myRoom->linkRooms(NW, new DiagonalRoom);

  cout << "myRoom->linkRooms(SW, new DiagonalRoom);" << endl;
  myRoom->linkRooms(SW, new DiagonalRoom);

  cout << "myRoom->setExitBlocked(SE, true);" << endl;
  myRoom->setExitBlocked(SE, true);

  cout << "myRoom->setExitBlocked(SW, true);" << endl;
  myRoom->setExitBlocked(SW, true);

  cout << "myRoom->getRoom(NE)->linkRooms(E, new Room);" << endl;
  myRoom->getRoom(NE)->linkRooms(E, new Room);

  myRoom->getRoom(S)->linkRooms(S, new RoundRoom);

  cout << "Item* myItem = new Switch(true);" << endl;
  Item* myItem = new Switch(false);

  myItem->activate(ON_ACTION_SET, 0, 0, myRoom->getExit(SW), BLOCK_TOGGLE);

  cout << "myRoom->addObject(myItem, CENTER, FLOOR);" << endl;
  myRoom->addObject(myItem, CENTER, FLOOR);

  cout << "Item* myItem2 = new Switch;" << endl;
  Item* myItem2 = new Switch;

  cout << "myItem2->activate(ON_ACTION_SET, 0, 0, myRoom->getExit(SE), BLOCK_TOGGLE);" << endl;
  myItem2->activate(ON_ACTION_SET, 0, 0, myRoom->getExit(SE), BLOCK_TOGGLE);

  cout << "myRoom->getRoom(SW)->addObject(myItem2, S, WALL);" << endl;
  myRoom->getRoom(SW)->addObject(myItem2, S, WALL);

  cout << "Item* myItem3 = new Switch(true);" << endl;
  Item* myItem3 = new Switch(true);

  cout << "myItem3->activate(ON_ACTION_SET, 0, E, myRoom->getRoom(NE), ROTATE_SET);" << endl;
  myItem3->activate(ON_ACTION_SET, 0, E, myRoom->getRoom(NE), ROTATE_SET);

  cout << "myItem3->activate(OFF_ACTION_SET, 0, NE, myRoom->getRoom(NE), ROTATE_SET);" << endl;
  myItem3->activate(OFF_ACTION_SET, 0, NE, myRoom->getRoom(NE), ROTATE_SET);

  cout << "myRoom->addObject(myItem3, NNW, WALL);" << endl;
  myRoom->addObject(myItem3, NNW, WALL);

  cout << endl;
  cout << "Initialized" << endl;
  cout << endl;

  Character::PLAYER->setCurrentRoom(myRoom);
  Character::PLAYER->displayCurrentRoom();

  while(!exitFlag){
    cout << endl
      << "Input command: ";
    getline(cin, input);
    cout << endl;
    //cout << "Parsing \"" << input << "\" ..." << endl;
    exitFlag = parse(input);
  }

  // Cleanup
#if 1
  int characterMax = Character::getNextCharacterID();
  Character* holdCharacter;

  for(int i=characterMax-1; i>=0; i--){
    holdCharacter = Character::getCharacterFromID(i);
    if(holdCharacter != NULL){
      delete holdCharacter;
    }
  }
#endif

#if 1
  int roomMax = Room::getNextRoomID();
  Room* holdRoom;

  for(int i=roomMax-1; i>=0; i--){
    holdRoom = Room::getRoomFromID(i);
    if(holdRoom != NULL){
      delete holdRoom;
    }
  }
#endif

#if 1
  if(SHOW_MESSAGES){
    cerr << "Ideally, no RoomExits should be deleted after this message."
      << endl;
  }

  int roomExitMax = RoomExit::getNextRoomExitID();
  RoomExit* holdRoomExit;

  for(int i=roomExitMax-1; i>=0; i--){
    holdRoomExit = RoomExit::getRoomExitFromID(i);
    if(holdRoomExit != NULL){
      delete holdRoomExit;
    }
  }
#endif

#if 1
  int itemMax = Item::getNextItemID();
  Item* holdItem;

  for(int i=itemMax-1; i>=0; i--){
    holdItem = Item::getItemFromID(i);
    if(holdItem != NULL){
      delete holdItem;
    }
  }
#endif

  cout << endl
    << "Have a nice day." << endl;

  return 0;
}
