a.exe: main.cc Globals.o Superclasses.o Rooms.o Items.o Characters.o System.o
	g++ main.cc *.o

#Globals
Globals.o: Globals.h Globals.cc ./Globals/constants.h methods.o
	g++ -c Globals.cc

methods.o: ./Globals/methods.h ./Globals/methods.cc ./Globals/constants.h
	g++ -c ./Globals/methods.cc

#Superclasses
Superclasses.o: Superclasses.h Superclasses.cc Globals.o Object.o Container.o
	g++ -c Superclasses.cc

Object.o: ./Superclasses/Object.h ./Superclasses/Object.cc
	g++ -c ./Superclasses/Object.cc

Container.o: ./Superclasses/Container.h ./Superclasses/Container.cc Object.o
	g++ -c ./Superclasses/Container.cc

#Rooms
Rooms.o: Rooms.h Rooms.cc Superclasses.o  RoomExit.o Room.o DiagonalRoom.o CorridorRoom.o RoundRoom.o RotatingRoom.o
	g++ -c Rooms.cc

RoomExit.o: ./Rooms/RoomExit.h ./Rooms/RoomExit.cc ./Rooms/Room.h ./Rooms/Room.cc Superclasses.o
	g++ -c ./Rooms/RoomExit.cc

Room.o: ./Rooms/Room.h ./Rooms/Room.cc ./Rooms/RoomExit.h ./Rooms/RoomExit.cc Globals.o Superclasses.o
	g++ -c ./Rooms/Room.cc

DiagonalRoom.o: ./Rooms/DiagonalRoom.h ./Rooms/DiagonalRoom.cc Room.o
	g++ -c ./Rooms/DiagonalRoom.cc

CorridorRoom.o: ./Rooms/CorridorRoom.h ./Rooms/CorridorRoom.cc Room.o
	g++ -c ./Rooms/CorridorRoom.cc

RoundRoom.o: ./Rooms/RoundRoom.h ./Rooms/RoundRoom.cc Room.o
	g++ -c ./Rooms/RoundRoom.cc

RotatingRoom.o: ./Rooms/RotatingRoom.h ./Rooms/RotatingRoom.cc RoundRoom.o CorridorRoom.o Globals.o Characters.o
	g++ -c ./Rooms/RotatingRoom.cc

#Items
Items.o: Items.h Items.cc Superclasses.o Item.o Switch.o
	g++ -c Items.cc

Item.o: ./Items/Item.h ./Items/Item.cc Superclasses.o
	g++ -c ./Items/Item.cc

Switch.o: ./Items/Switch.h ./Items/Switch.cc Item.o Superclasses.o Characters.o
	g++ -c ./Items/Switch.cc

#Characters
Characters.o: Characters.h Characters.cc Superclasses.o Character.o
	g++ -c Characters.cc

Character.o: ./Characters/Character.h ./Characters/Character.cc Globals.o Superclasses.o
	g++ -c ./Characters/Character.cc

#System
System.o: System.h System.cc ./System/parse.h commands.o
	g++ -c System.cc

commands.o: ./System/commands.h ./System/commands.cc ./System/parse.h
	g++ -c ./System/commands.cc

#arguments
clean:
	rm -f ./a.exe
	rm -f ./*.o

run: a.exe
	./a.exe
