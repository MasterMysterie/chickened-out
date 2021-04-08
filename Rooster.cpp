#include "Rooster.h"
#include "ChickenStats.h"


Rooster::Rooster(olc::vi2d position, int birth_time) : Chicken(position, birth_time) {

	male = true;
	fertile = true;
	this->birth_time = birth_time;

}

ChickenStats Rooster::update(ChickenStats stats) {


	return stats;

}

