#pragma once
#include "Chicken.h"
#include "ChickenStats.h"

class Rooster : public Chicken {
public:


	Rooster(olc::vi2d, int);

	ChickenStats update(ChickenStats, int);


};