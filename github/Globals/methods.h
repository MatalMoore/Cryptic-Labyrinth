
#ifndef METHODS_H
#define METHODS_H

#include <string>

std::string stringsToSequence(const std::string* strings, const int numberOfStrings);
std::string compassDirectionToString(const int compassDirection, const bool giveFullName=false);
std::string uppercase(const std::string value);

int oppositeDirection(const int compassDirection);
int rotateDirection(const int compassDirection, const int interval);
int stringToCompassDirection(const std::string value);

bool isNaturalDirection(int whichDirection);
bool isGoodDirection(int whichDirection);

#endif
