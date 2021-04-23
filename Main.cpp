#define OLC_PGE_APPLICATION

#include "Header.h"
#include "Chicken.h"
#include "Hen.h"
#include "Rooster.h"
#include "ChickenStats.h"
#include "Egg.h"
#include "Player.h"
#include "Button.h"

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

std::string to_igt(double, double);



class Window : public olc::PixelGameEngine
{
public:
	Window()
	{
		sAppName = "Window";
	}



public:

	double time = 0;
	double last_time = 0;

	int chicken_count = 1;
	int hen_count = 0;
	int rooster_count = 0;
	int egg_count = 0;
	
	double day_length = 3;
	double hour_length = day_length / 24;
	double minute_length = hour_length / 60;

	bool day_switch = false;
	int day = 0;
	int last_day = 0;
	bool paused = false;

	int selected_purchase = 0;
	int* purchase_prices = new int[4];
	

	std::vector<Chicken*> chickens;
	std::vector<Egg*> eggs;
	std::vector<Button*> buttons;

	Player player = Player(1000);

	// Might change to chimkin later

	std::unique_ptr<olc::Sprite> eggSpr;
	std::unique_ptr<olc::Sprite> pulletSpr;
	std::unique_ptr<olc::Sprite> cockerelSpr;
	std::unique_ptr<olc::Sprite> henSpr;
	std::unique_ptr<olc::Sprite> roosterSpr;
	std::unique_ptr<olc::Sprite> buttonSpr;
	std::unique_ptr<olc::Sprite> buttonPSpr;

	std::unique_ptr<olc::Decal> eggDec;
	std::unique_ptr<olc::Decal> pulletDec;
	std::unique_ptr<olc::Decal> cockerelDec;
	std::unique_ptr<olc::Decal> henDec;
	std::unique_ptr<olc::Decal> roosterDec;
	std::unique_ptr<olc::Decal> buttonDec;
	std::unique_ptr<olc::Decal> buttonPDec;

	int sizeMult = 10;

	olc::vi2d eggTrns = olc::vi2d(3.5 * sizeMult, 8 * sizeMult);
	olc::vi2d pulletTrns = olc::vi2d(4 * sizeMult, 8 * sizeMult);
	olc::vi2d cockerelTrns = olc::vi2d(4 * sizeMult, 9 * sizeMult);
	olc::vi2d henTrns = olc::vi2d(7.5 * sizeMult, 15 * sizeMult);
	olc::vi2d roosterTrns = olc::vi2d(8 * sizeMult, 16 * sizeMult);
	olc::vi2d buttonTrns = olc::vi2d(16 * sizeMult, 4 * sizeMult);

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		eggSpr = std::make_unique<olc::Sprite>("sprites/Egg.png");
		pulletSpr = std::make_unique<olc::Sprite>("sprites/Pullet.png");
		cockerelSpr = std::make_unique<olc::Sprite>("sprites/Cockerel.png");
		henSpr = std::make_unique<olc::Sprite>("sprites/Hen.png");
		roosterSpr = std::make_unique<olc::Sprite>("sprites/Rooster.png");
		buttonSpr = std::make_unique<olc::Sprite>("sprites/Button.png");
		buttonPSpr = std::make_unique<olc::Sprite>("sprites/ButtonPressed.png");
		
		eggDec = std::make_unique<olc::Decal>(eggSpr.get());
		pulletDec = std::make_unique<olc::Decal>(pulletSpr.get());
		cockerelDec = std::make_unique<olc::Decal>(cockerelSpr.get());
		henDec = std::make_unique<olc::Decal>(henSpr.get());
		roosterDec = std::make_unique<olc::Decal>(roosterSpr.get());
		buttonDec = std::make_unique<olc::Decal>(buttonSpr.get());
		buttonPDec = std::make_unique<olc::Decal>(buttonPSpr.get());

		//chickens.push_back(new Hen(olc::vi2d(rand() % 1000, rand() % 1000), 0));
		//chickens[0]->adult = true;

		purchase_prices[0] = 100;
		purchase_prices[1] = 150;
		purchase_prices[2] = 50;
		purchase_prices[3] = 5000;

		buttons.push_back(new Button(olc::vi2d(800, 60), olc::vi2d(32, 8), 2, "Buy 1 Egg\n\n", true));
		buttons.push_back(new Button(olc::vi2d(800, 160), olc::vi2d(32, 8), 0, "Buy 1 Hen\n\n", true));
		buttons.push_back(new Button(olc::vi2d(800, 260), olc::vi2d(32, 8), 1, "Buy 1 Rooster\n\n", true));

		buttons.push_back(new Button(olc::vi2d(800, 460), olc::vi2d(32, 8), 2, "Sell 1 Egg\n\n", false));
		buttons.push_back(new Button(olc::vi2d(800, 560), olc::vi2d(32, 8), 0, "Sell 1 Hen\n\n", false));
		buttons.push_back(new Button(olc::vi2d(800, 660), olc::vi2d(32, 8), 1, "Sell 1 Rooster\n\n", false));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::VERY_DARK_GREEN);

		if (!paused) {
			time += fElapsedTime;
		}

		//DrawDecal(olc::vi2d(0, 500), eggDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(250, 500), pulletDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(x, y), cockerelDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(500, 500), henDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(750, 500), roosterDec.get(), olc::vf2d(10,10));
		//DrawDecal(olc::vi2d(x,y), buttonDec.get(), olc::vf2d(10, 10));

		day = (int)(time / day_length);

		egg_count = 0;
		chicken_count = 0;
		hen_count = 0;
		rooster_count = 0;

		checkInput();

		if (last_day < day) {
			day_switch = true;
			

		}

		if (time - last_time >= hour_length) {
			updateChickens();
			updateEggs();
			day_switch = false;
			last_time = time;

			
		}

		drawEggs();
		drawChickens();
		drawButtons();
		
		if (! paused) {
			walkChickens(fElapsedTime);

		}
		

		DrawStringDecal({ 5, 5 }, "Time:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 25 }, "Chick:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 45 }, "Hens:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 65 }, "Roosters:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 85 }, "Eggs:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 105 }, "Day:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 125 }, "Balance:", olc::WHITE, { 2,2 });

		DrawStringDecal({ 155, 5 }, to_igt(time, day_length), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 25 }, std::to_string(chicken_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 45 }, std::to_string(hen_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 65 }, std::to_string(rooster_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 85 }, std::to_string(egg_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 105 }, std::to_string(day), olc::WHITE, { 2,2 });
		DrawStringDecal({ 155, 125 }, "$" + std::to_string(player.balance), olc::WHITE, { 2,2 });


		last_day = day;
				
		return true;
	}

	void checkInput() {

		int hour_time = fmod(time, day_length) / hour_length;
		olc::vi2d mPos = olc::vi2d(GetMouseX(), GetMouseY());
		int c_index = chickens.size();
		int e_index = eggs.size();
	

		if (GetKey(olc::Key::K1).bPressed) {
			selected_purchase = 0;

		}
		else if (GetKey(olc::Key::K2).bPressed) {

			selected_purchase = 1;

		}
		else if (GetKey(olc::Key::K3).bPressed) {

			selected_purchase = 2;

		}
		else if (GetKey(olc::Key::K4).bPressed) {

			selected_purchase = 3;

		}

		if (GetKey(olc::Key::SPACE).bPressed) {

			paused = ! paused;

		}

		//yes I know that the above is stupid but you come up with something better

		if (GetMouse(0).bPressed) {
			//pressing on shit

			for (Button* button : buttons) {
				if (GetMouseX() >= button->position.x - sizeMult * button->dimensions.x / 2 &&
					GetMouseX() <= button->position.x + sizeMult * button->dimensions.x / 2 &&
					GetMouseY() >= button->position.y - sizeMult * button->dimensions.y / 2 &&
					GetMouseY() <= button->position.y + sizeMult * button->dimensions.y / 2) {

					//dont you dare insult this code ^^

					
					if (button->buy) {
						if (player.balance - purchase_prices[button->purchase] < 0) {
							break;
						}

						player.balance -= purchase_prices[button->purchase];

						switch (button->purchase) {

						case 0:
							//hen
							chickens.push_back(new Hen(olc::vi2d(rand() % 1000, rand() % 1000), hour_time));
							chickens[c_index]->age_days = 10;
							chickens[c_index]->adult = true;

							break;

						case 1:
							//rooster
							chickens.push_back(new Rooster(olc::vi2d(rand() % 1000, rand() % 1000), hour_time));
							chickens[c_index]->age_days = 10;
							chickens[c_index]->adult = true;

							break;

						case 2:
							//egg
							eggs.push_back(new Egg(true, olc::vi2d(rand() % 1000, rand() % 1000), hour_time));
							eggs[e_index]->age_days = 2;

							break;

						case 3:
							//coop

							break;

						}

					}
					else {
						

						std::vector<int> hens;
						std::vector<int> roosters;

						for (int i = 0; i < chickens.size(); i++) {
							if (chickens[i]->adult && chickens[i]->male) {
								roosters.push_back(i);
							}
							else if (chickens[i]->adult && !chickens[i]->male) {
								hens.push_back(i);
							}
							

						}

						switch (button->purchase) {

						case 0:
							//hen
							if (hens.size() > 0) {
								player.balance += purchase_prices[button->purchase];
								chickens.erase(chickens.begin() + hens[rand() % hens.size()]);
							}
							break;

						case 1:
							//rooster
							if (roosters.size() > 0) {
								player.balance += purchase_prices[button->purchase];
								chickens.erase(chickens.begin() + roosters[rand() % roosters.size()]);
							}
							break;

						case 2:
							//egg
							if (eggs.size() > 0) {
								player.balance += purchase_prices[button->purchase];
								eggs.erase(eggs.begin() + rand() % eggs.size());
							}
							break;

						case 3:
							//coop

							break;

						}

					}
					

					

					break;

				}


			}

			



		}

		else if (GetMouse(1).bPressed) {

			//nothing to see here(yet) folks


		}




	}


	void drawButtons() {

		for (Button* button : buttons) {
			if (GetMouseX() >= button->position.x - sizeMult * button->dimensions.x / 2 &&
				GetMouseX() <= button->position.x + sizeMult * button->dimensions.x / 2 &&
				GetMouseY() >= button->position.y - sizeMult * button->dimensions.y / 2 &&
				GetMouseY() <= button->position.y + sizeMult * button->dimensions.y / 2 &&
				GetMouse(0).bHeld) {

				//this code is fine alright so stop complaining ^^

				DrawDecal(olc::vi2d(button->position) - buttonTrns, buttonPDec.get(), olc::vi2d(sizeMult, sizeMult));

			}
			else {
				
				DrawDecal(olc::vi2d(button->position) - buttonTrns, buttonDec.get(), olc::vi2d(sizeMult, sizeMult));

			}

			olc::Pixel colour = olc::WHITE;

			//yes the british spelling of colour, deal with it

			if (player.balance - purchase_prices[button->purchase] < 0 && button->buy) {
				colour = olc::RED;
			}

			if (!button->buy) {
				colour = olc::DARK_GREEN;

			}

			DrawStringDecal(button->position - GetTextSize(button->label), button->label, colour, { 2,2 });
			DrawStringDecal(button->position - GetTextSize("\n\n$" + std::to_string(purchase_prices[button->purchase])), "\n\n$" + std::to_string(purchase_prices[button->purchase]), colour, { 2,2 });

		}
	}

	void updateChickens() {

		int hour_time = fmod(time, day_length) / hour_length;

		for (Chicken* chicken : chickens) {

			if (day_switch) {

				chicken->age_days++;

			}

			ChickenStats stats = ChickenStats(egg_count);

			stats = chicken->update(stats, hour_time);
			
			for (int i = 0; i < stats.egg_count - egg_count; i++) {
				eggs.push_back(new Egg(chicken->fertile, chicken->position, hour_time));
				//chicken->position        ^^
			}
			



		}
	}

	void updateEggs() {

		int hour_time = fmod(time, day_length) / hour_length;

		for (int i = 0; i < eggs.size(); i++) {
			

			if (day_switch) {

				eggs[i]->age_days += 1;

			}

			if (eggs[i]->fertile) {

				EggStats stats = EggStats();

				stats = eggs[i]->update(stats, hour_time);

				if (stats.hatching) {
					if (rand() % 2 == 0) {
						chickens.push_back(new Hen(eggs[i]->position, hour_time));
						//eggs[i]->position              ^^
					}
					else {
						chickens.push_back(new Rooster(eggs[i]->position, hour_time));

					}
					
					delete eggs[i];
					eggs.erase(std::remove(eggs.begin(), eggs.end(), eggs[i]));


				}

			}
			

		}
	}

	void drawEggs() {
		for (int i = 0; i < eggs.size(); i++) {
			egg_count++;
			DrawDecal(olc::vi2d(eggs[i]->position.x - eggTrns.x, eggs[i]->position.y - eggTrns.y), eggDec.get(), olc::vf2d(10, 10));

		}
	}

	void drawChickens() {
		for (int i = 0; i < chickens.size(); i++) {
			double flip = 1;
			if (chickens[i]->velocity.x < 0) {
				flip = -1;


			}
			if (! chickens[i]->adult && ! chickens[i]->male) {
				//pullet
				chicken_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - pulletTrns.x * flip, chickens[i]->position.y - pulletTrns.y), pulletDec.get(), olc::vf2d(10 * flip, 10));

			}
			else if (! chickens[i]->adult && chickens[i]->male) {
				//cockerel
				chicken_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - cockerelTrns.x * flip, chickens[i]->position.y - cockerelTrns.y), cockerelDec.get(), olc::vf2d(10 * flip, 10));

			}
			else if (chickens[i]->male) {
				//rooster
				rooster_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - roosterTrns.x * flip, chickens[i]->position.y - roosterTrns.y), roosterDec.get(), olc::vf2d(10 * flip, 10));

			}
			else {
				//hen
				hen_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - henTrns.x * flip, chickens[i]->position.y - henTrns.y), henDec.get(), olc::vf2d(10 * flip, 10));

			}
			

		}
	}

	void walkChickens(float fElapsedTime) {

		for (int i = 0; i < chickens.size(); i++) {

			chickens[i]->walk(fElapsedTime);
			
		}

	}

	std::string to_igt(double time, double day_length) {

		double hour_length = day_length / 24;
		double minute_length = hour_length / 60;

		int hour_time = fmod(time, day_length) / hour_length;
		int minute_time = fmod(time, hour_length) / minute_length;

		std::string hour_time_s = std::to_string(hour_time);

		if (hour_time < 10) {

			hour_time_s = "0" + hour_time_s;

		}

		std::string minute_time_s = std::to_string(minute_time);

		if (minute_time < 10) {

			minute_time_s = "0" + minute_time_s;

		}

		return hour_time_s + ":" + minute_time_s;
	}

};



int main()
{

	std::srand(std::time(nullptr));

	std::cout << std::time(nullptr) << "\n";

	Window window;
	if (window.Construct(1000, 1000, 1, 1))
		window.Start();
	

	return 0;

}



