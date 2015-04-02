
#include "Globals.h"
#include "Superclasses.h"
#include "Rooms.h"
#include "Items.h"
#include "Characters.h"
#include "System.h"
#include <iostream>
using namespace std;

int main(){
  const int roomCount = 9;
  const int roomExitCount = 11;
  const int switchCount = 2;

  int i;

  bool exitFlag = false;

  string input;

  Room* winRoom = NULL;

  Room* rooms[roomCount];

  RoomExit* roomExits[roomExitCount];

  Switch* switches[switchCount];

#if 0
  cout << endl;
  cout << "Initializing ..." << endl;
  cout << endl;
#endif

  rooms[0] = new RotatingRoom;
  for(i=0; i<6; i++){
    rooms[i+1] = new Room;
  }
  for(i=0; i<2; i++){
    rooms[7+i] = new RoundRoom;
  }

  for(i=0; i<roomExitCount; i++){
    roomExits[i] = new RoomExit;
  }

  for(i=0; i<switchCount; i++){
    switches[i] = new Switch;
  }

#if 0
  for(i=0; i<roomCount; i++){
    cout << rooms[i]->getName() << " -" << rooms[i]->getRoomType() << "-" << endl;
  }
#endif

  roomExits[4]->setBlocked(true);
  roomExits[4]->setHidden(true);

  rooms[0]->linkRooms(N, 1, 0);
  rooms[0]->linkRooms(E, 3, 3);
  rooms[0]->linkRooms(S, 4, 6);
  rooms[0]->linkRooms(W, 6, 9);

  rooms[2]->linkRooms(W, 1, 1);
  rooms[2]->linkRooms(S, 3, 2);

  rooms[5]->linkRooms(N, 6, 8);
  rooms[5]->linkRooms(E, 4, 7);

  rooms[7]->linkRooms(N, 3, 4);
  rooms[7]->linkRooms(NW, 0, 5);

  rooms[8]->linkRooms(SE, 0, 10);

  switches[0] = new Switch(true);
  switches[1] = new Switch;

  switches[0]->addOnAction(ROTATE_SET, 0, SE, rooms[0]);
  switches[0]->addOffAction(ROTATE_SET, 0, N, rooms[0]);

  switches[1]->addOnAction(BLOCK_SET, false, 0, roomExits[4]);

  rooms[3]->addObject(switches[0], E, WALL);
  rooms[6]->addObject(switches[1], W, WALL);

#if 0
  cout << endl;
  cout << "Initialized" << endl;
#endif

  cout << endl;
  cout << "You may type \"help\" to see the available commands." << endl;
  cout << endl;

  Character::PLAYER->setCurrentRoom(rooms[0]);
  Character::PLAYER->displayCurrentRoom();

  winRoom = rooms[8];
  winRoom->setDescription("You leave the dungeon.");

  while(!exitFlag){
    cout << endl;

    if(Character::PLAYER->getCurrentRoom() == winRoom){
      cout << "You win!" << endl;
      break;
    }

#if 0
    cout << Character::PLAYER->getCurrentRoom()->getName() << endl;
    cout << endl;
#endif

    cout << DISPLAY_LINE_ALT << endl;
    cout << "Input command: ";
    getline(cin, input);
    cout << endl;
    cout << DISPLAY_LINE_ALT << endl;
    cout << endl;
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
