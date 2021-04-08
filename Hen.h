#pragma once
#include "Chicken.h"
#include "Header.h"


class Hen : public Chicken {
public:


	

	Hen(olc::vi2d, int);

	ChickenStats update(ChickenStats stats, int);


};