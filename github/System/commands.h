
#ifndef COMMANDS_H
#define COMMANDS_H

#include "./../Characters.h"
#include <string>

const std::string invalidArguments = "Invalid arguments: ";

const std::string commandHELP = "HELP";
const std::string commandEXIT = "EXIT";
const std::string commandLOOK = "LOOK";
const std::string commandGO = "GO";

const std::string helpEXIT = "Exits the program";
const std::string helpHELP = "Displays help information";
const std::string helpLOOK = "Looks around at the current ROOM";
const std::string helpGO = "Attempts to GO to the ROOM in the given DIRECTION";

const std::string argsHELP = "[COMMAND]";
const std::string argsGO = "DIRECTION";

const int commandsMax = 4;

const int commands0argc = 3;
const int commands1argc = 2;

const std::string commandsAll[] = {
  commandEXIT
    , commandHELP
    , commandLOOK
    , commandGO
};

const std::string commands0arg[] = {
  commandEXIT
    , commandHELP
    , commandLOOK
};
const std::string commands1arg[] = {
    commandHELP
    , commandGO
};

bool executeCommand(const std::string* argv, const std::string* argvUpper, const int argc, const Character* character=NULL, const int offset=0);

bool executeEXIT(const std::string* argv, const std::string* argvUpper, const int argc, const int offset=0);

bool executeHELP(const std::string* argv, const std::string* argvUpper, const int argc, const int offset=0);

bool executeLOOK(const std::string* argv, const std::string* argvUpper, const int argc, const Character* character=NULL, const int offset=0);

bool executeGO(const std::string* argv, const std::string* argvUpper, const int argc, const Character* character=NULL, const int offset=0);

#endif
