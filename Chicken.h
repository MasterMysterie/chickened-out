#pragma once
#include "ChickenStats.h"
#include "Header.h"

class Chicken {
public:

	int age_days;
	olc::vd2d position;
	olc::vd2d destination;
	bool male;
	bool fertile;
	int still_counter;
	double speed = 0;
	olc::vd2d velocity;
	int birth_time;
	bool adult;

	Chicken(olc::vi2d, int);

	virtual ChickenStats update(ChickenStats, int) = 0;
	void walk(float fElapsedTime);

};