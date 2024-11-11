#pragma once

#include "AnimationSystem.h"
#include "ModuleGame.h"
#include "GameUI.h"
#include "PokeBall.h"
#include "Flipper.h"
#include "PokeballChangerGroup.h"
#include "CaveSensorGroup.h"



using namespace pugi;

class ModuleGameBlueMap : public ModuleGame {
private:

	PokeballChangerGroup* pokeballChangerGroup = nullptr;
	CaveSensorGroup* caveSensorGroup = nullptr;

	Flipper* leftFlipper = nullptr;
	Flipper* rightFlipper = nullptr;
	GameUI* UI = nullptr;
	
	//Create
	void LoadMap(std::string path) override;
	void SetState(GameStates stateToChange) override;

	std::string mapPath = "Assets/MapData/";

public:
	ModuleGameBlueMap(Application* app, bool start_enabled = true);
	~ModuleGameBlueMap();

	bool Start();
	update_status Update();
	bool CleanUp();
};

