#include "Chicken.h"
#include "ChickenStats.h"
#include "Header.h"

#include <cstdlib>




Chicken::Chicken(olc::vi2d position, int birth_time) {

	age_days = 0;
	this->position = position;
	this->birth_time = birth_time;
	adult = false;
	still_counter = 0;

	
	//at destination
	//still_counter = rand() % 21;

	destination = olc::vi2d(rand() % 1000, rand() % 1000);

	speed = rand() % 100 + 30;
	if (! adult) {
		speed *= 2;
	}
	velocity = (destination - position).norm() * speed;

}

void Chicken::walk(float fElapsedTime) {

	if (still_counter == 0) {
		//not standing still
		if ((position - destination).mag() < velocity.mag() * 1.1) {
			
			//at destination
			still_counter = rand() % 1000 + 100;

			destination = olc::vi2d(rand() % 1000, rand() % 1000);
			speed = rand() % 100 + 30;
			if (! adult) {
				speed *= 2;
			}
			
			velocity = (destination - position).norm() * speed;

		}
		else {
			//walking to destination
			
			position += velocity * fElapsedTime;


		}

	}
	else {
		//stalling
		still_counter--;


	}
	

}



