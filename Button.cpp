#include "Button.h"


Button::Button(olc::vi2d position, olc::vi2d dimensions, int purchase, std::string label, bool buy) {

	this->position = position;
	this->dimensions = dimensions;
	this->purchase = purchase;
	this->label = label;
	this->buy = buy;

}

