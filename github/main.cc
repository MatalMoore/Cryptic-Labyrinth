
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

  cout << "myRoom->linkRooms(NE, new RotatingRoom(NE, true));" << endl;
  myRoom->linkRooms(NE, new RotatingRoom(NE, true));

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

  cout << endl;
  cout << "Initialized" << endl;
  cout << endl;

  PLAYER->setCurrentRoom(myRoom);
  PLAYER->displayCurrentRoom();

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
