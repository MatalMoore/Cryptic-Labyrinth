
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// When set to true, creation and deletion of objects will be shown
const bool SHOW_MESSAGES = false;

const int ARGC_MAX = 20;

// activate action constants
// -!- MUST BE EXCLUSIVE -!-

const int DEFAULT_ACTION = -1;

const int NO_ACTION = 0;

const int BLOCK_SET = 1;
const int HIDE_SET = 2;

const int BLOCK_TOGGLE = 3;
const int HIDE_TOGGLE = 4;

const int ROTATE = 5;
const int ROTATE_SET = 6;

const int POSITION_SET = 7;
const int FACE_SET = 8;

const int ROOM_SET = 9;

const int OBTAINABLE_SET = 10;
const int OBTAIN_SET = 11;

const int OBTAINABLE_TOGGLE = 12;
const int OBTAIN_TOGGLE = 13;

const int ON_ACTION_ADD = 14;
const int OFF_ACTION_ADD = 15;
const int SWITCH_PRESS = 16;

const int VISIBLE_SET = 17;

const int OBJECT_ADD = 18;

// compass directions
// -!- DIRECTIONS NEED TO BE CONTIGUOUS -!-
// -!- NO_DIRECTION MUST ALWAYS BE SMALLEST -!-

const int NO_DIRECTION = -3;

const int OPPOSITE = -2;
const int CENTER = -1;

const int N = 0;
const int NNE = 1;
const int NE = 2;
const int ENE = 3;
const int E = 4;
const int ESE = 5;
const int SE = 6;
const int SSE = 7;
const int S = 8;
const int SSW = 9;
const int SW = 10;
const int WSW = 11;
const int W = 12;
const int WNW = 13;
const int NW = 14;
const int NNW = 15;

const int DIRECTION_MAX = 16;

// general types
const std::string OBJECT = "OBJECT";
const std::string CONTAINER = "CONTAINER";
const std::string ROOM_EXIT = "ROOM_EXIT";

// room types
const std::string ROOM = "ROOM";
const std::string DIAGONAL_ROOM = "DIAGONAL_ROOM";
const std::string CORRIDOR_ROOM = "CORRIDOR_ROOM";
const std::string ROUND_ROOM = "ROUND_ROOM";
const std::string ROTATING_ROOM = "ROTATING_ROOM";

// item types
const std::string ITEM = "ITEM";
const std::string SWITCH = "SWITCH";

// character types
const std::string CHARACTER = "CHARACTER";

// other strings
const std::string FLOOR = "floor";
const std::string WALL = "wall";
const std::string CEILING = "ceiling";

const std::string DISPLAY_LINE = "------------------------------------------------------------";
const std::string DISPLAY_LINE_ALT = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

// arrays that are used for quick access to strings
// -!- NEED TO HAVE INDICES CORRESPONDING TO (DIRECTION - NO_DIRECTION) -!-
const std::string DIRECTION_ARRAY_LONG[] = {
  "NO_DIRECTION"
    , "OPPOSITE"
    , "Center"
    , "North"
    , "North-by-Northeast"
    , "Northeast"
    , "East-by-Northeast"
    , "East"
    , "East-by-Southeast"
    , "Southeast"
    , "South-by-Southeast"
    , "South"
    , "South-by-Southwest"
    , "Southwest"
    , "West-by-Southwest"
    , "West"
    , "West-by-Northwest"
    , "Northwest"
    , "North-by-Northwest"
};

const std::string DIRECTION_ARRAY_SHORT[] = {
  "N/D"
    , "OPP"
    , "C"
    , "N"
    , "NNE"
    , "NE"
    , "ENE"
    , "E"
    , "ESE"
    , "SE"
    , "SSE"
    , "S"
    , "SSW"
    , "SW"
    , "WSW"
    , "W"
    , "WNW"
    , "NW"
    , "NNW"
};

#endif
