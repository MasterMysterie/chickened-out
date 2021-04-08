#pragma once
#include "Header.h"
#include "EggStats.h"

class Egg {
public:

	bool fertile;
	int age_days;
	olc::vi2d position;
	int birth_time;

	Egg(bool, olc::vi2d, int);
	EggStats update(EggStats, int);


};