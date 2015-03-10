
#ifndef METHODS_H
#define METHODS_H

#include <string>

std::string stringsToSequence(std::string* strings, int numberOfStrings);
std::string compassDirectionToString(int compassDirection, bool giveFullName=false);
std::string uppercase(std::string value);

int oppositeDirection(int compassDirection);
int rotateDirection(int compassDirection, int interval);
int stringToCompassDirection(std::string value);

bool isNaturalDirection(int whichDirection);

#endif