#pragma once
#include "Header.h"

class Button {
public:

	olc::vi2d position;
	olc::vi2d dimensions;
	int purchase;

	std::string label;

	Button(olc::vi2d, olc::vi2d, int, std::string);

	


};