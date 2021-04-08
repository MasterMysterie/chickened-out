#include "Hen.h"

#include <cstdlib>



Hen::Hen(olc::vi2d position, int birth_time) : Chicken(position, birth_time){

	fertile = true;
	this->birth_time = birth_time;
	male = false;

}

ChickenStats Hen::update(ChickenStats stats, int time) {

	if (age_days > 5 && birth_time == time) {
		adult = true;



	}

	if (adult) {
		//adult
		if (std::rand() % 12 + 1 == 1) {

			stats.egg_count++;

		}
	}
	

	return stats;

}


