#pragma once

#include "AnimationSystem.h"
#include "ModuleGame.h"
#include "GameUI.h"
#include "PokeBall.h"
#include "Flipper.h"
#include "DittoColliders.h"



using namespace pugi;

class ModuleGameRedMap : public ModuleGame {
private:

	PokeBall* pokeBall = nullptr;
	Flipper* leftFlipper = nullptr;
	Flipper* rightFlipper = nullptr;
	GameUI* UI = nullptr;


	DittoColliders* dittoColliders=nullptr;

	
	//Create
	void LoadMap(std::string path) override;


	std::string mapPath = "Assets/MapData/";

public:
	ModuleGameRedMap(Application* app, bool start_enabled = true);
	~ModuleGameRedMap();

	bool Start();
	update_status Update();
	bool CleanUp();
};

