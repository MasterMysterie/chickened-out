#define OLC_PGE_APPLICATION

#include "Header.h"
#include "Chicken.h"
#include "Hen.h"
#include "Rooster.h"
#include "ChickenStats.h"
#include "Egg.h"
#include "Player.h"

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>


std::string to_igt(double, double);

void updateChickens();


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
	
	double day_length = 2;
	double hour_length = day_length / 24;
	double minute_length = hour_length / 60;

	bool day_switch = false;
	int day = 0;
	int last_day = 0;

	std::vector<Chicken*> chickens;
	std::vector<Egg*> eggs;

	// Might change to chimkin later

	std::unique_ptr<olc::Sprite> eggSpr;
	std::unique_ptr<olc::Sprite> chickenSpr;
	std::unique_ptr<olc::Sprite> henSpr;
	std::unique_ptr<olc::Sprite> roosterSpr;

	std::unique_ptr<olc::Decal> eggDec;
	std::unique_ptr<olc::Decal> chickenDec;
	std::unique_ptr<olc::Decal> henDec;
	std::unique_ptr<olc::Decal> roosterDec;

	int sizeMult = 10;

	olc::vi2d eggTrns = olc::vi2d(3.5 * sizeMult, 8 * sizeMult);
	olc::vi2d chickenTrns = olc::vi2d(4 * sizeMult, 8 * sizeMult);
	olc::vi2d henTrns = olc::vi2d(7.5 * sizeMult, 15 * sizeMult);
	olc::vi2d roosterTrns = olc::vi2d(8 * sizeMult, 16 * sizeMult);


	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		eggSpr = std::make_unique<olc::Sprite>("sprites/Egg.png");
		chickenSpr = std::make_unique<olc::Sprite>("sprites/Chicken.png");
		henSpr = std::make_unique<olc::Sprite>("sprites/Hen.png");
		roosterSpr = std::make_unique<olc::Sprite>("sprites/Rooster.png");
		
		eggDec = std::make_unique<olc::Decal>(eggSpr.get());
		chickenDec = std::make_unique<olc::Decal>(chickenSpr.get());
		henDec = std::make_unique<olc::Decal>(henSpr.get());
		roosterDec = std::make_unique<olc::Decal>(roosterSpr.get());

		chickens.push_back(new Hen(olc::vi2d(500, 500), 2));
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::VERY_DARK_GREEN);

		time += fElapsedTime;
		
		//DrawDecal(olc::vi2d(0, 500), eggDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(250, 500), chickenDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(500, 500), henDec.get(), olc::vf2d(10, 10));
		//DrawDecal(olc::vi2d(750, 500), roosterDec.get(), olc::vf2d(10,10));

		day = (int)(time / day_length);

		egg_count = 0;
		chicken_count = 0;
		hen_count = 0;
		rooster_count = 0;

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
		
		walkChickens(fElapsedTime);

		DrawStringDecal({ 5, 5 }, "Time:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 25 }, "Chick:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 45 }, "Hens:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 65 }, "Roosters:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 85 }, "Eggs:", olc::WHITE, { 2, 2 });
		DrawStringDecal({ 5, 105 }, "Day:", olc::WHITE, { 2, 2 });

		DrawStringDecal({ 155, 5 }, to_igt(time, day_length), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 25 }, std::to_string(chicken_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 45 }, std::to_string(hen_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 65 }, std::to_string(rooster_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 85 }, std::to_string(egg_count), olc::WHITE, { 2, 2 });
		DrawStringDecal({ 155, 105 }, std::to_string(day), olc::WHITE, { 2,2 });


		last_day = day;
				
		return true;
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

			EggStats stats = EggStats();

			stats = eggs[i]->update(stats, hour_time);

			if (stats.hatching) {
				chickens.push_back(new Hen(eggs[i]->position, hour_time));
				//eggs[i]->position              ^^
				delete eggs[i];
				eggs.erase(std::remove(eggs.begin(), eggs.end(), eggs[i]));
				

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
			if (! chickens[i]->adult) {
				chicken_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - chickenTrns.x * flip, chickens[i]->position.y - chickenTrns.y), chickenDec.get(), olc::vf2d(10 * flip, 10));

			}
			else if (chickens[i]->male) {
				rooster_count++;
				DrawDecal(olc::vi2d(chickens[i]->position.x - roosterTrns.x * flip, chickens[i]->position.y - roosterTrns.y), roosterDec.get(), olc::vf2d(10 * flip, 10));

			}
			else {
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

	Window window;
	if (window.Construct(1000, 1000, 1, 1))
		window.Start();
	

	return 0;

}



