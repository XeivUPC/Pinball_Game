#pragma once

#include "AnimationSystem.h"
#include "ModuleGame.h"
#include "GameUI.h"
#include "PokeBall.h"
#include "Flipper.h"



using namespace pugi;

class ModuleGameBlueMap : public ModuleGame {
private:

	PokeBall* pokeBall = nullptr;
	Flipper* leftFlipper = nullptr;
	Flipper* rightFlipper = nullptr;
	GameUI* UI = nullptr;


	b2Body* dittoCollider1 = nullptr;
	b2Body* dittoCollider2 = nullptr;

	
	//Create
	void LoadMap(std::string path) override;


	std::string mapPath = "Assets/MapData/";

public:
	ModuleGameBlueMap(Application* app, bool start_enabled = true);
	~ModuleGameBlueMap();

	bool Start();
	update_status Update();
	bool CleanUp();
};

