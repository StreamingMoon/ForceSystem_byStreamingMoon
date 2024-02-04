#pragma once

#ifndef CONSTANTS
#define CONSTANTS
#endif

#include<math.h>
#include<vector>
#include"Force.h"
#include"Object.h"

using namespace std;

extern const double UNITTIME;

extern const double PI;

extern Object EMPTYOBJECT;
extern Force EMPTYFORCE;

extern vector<Force*> FORCES;
extern vector<Object*> OBJECTS;