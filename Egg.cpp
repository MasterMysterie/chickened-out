#include "Egg.h"
#include "Header.h"

#include <cstdlib>

Egg::Egg(bool fertile, olc::vi2d position, int birth_time) {

	age_days = 0;
	this->fertile = fertile;
	this->position = position;
	this->birth_time = birth_time;

}

EggStats Egg::update(EggStats stats, int time) {
	stats.hatching = false;
	if (age_days == 5 && fertile && time == birth_time) {
		stats.hatching = true;
		

	}

	return stats;

}


