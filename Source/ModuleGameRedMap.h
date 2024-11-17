#pragma once
#include "AnimationSystem.h"
#include "ModuleGame.h"
#include "GameUI.h"
#include "Flipper.h"
#include "DittoColliders.h"
#include "DiglettBumper.h"
#include "PokeballChangerGroup.h"
#include "CaveSensorGroup.h"
#include "LapSensorGroup.h"
#include "CenterRedArrowGroup.h"
#include "BonusMultiplierSensorGroup.h"

using namespace pugi;


class StaryuBumper;

class ModuleGameRedMap : public ModuleGame {
private:
	Flipper* leftFlipper = nullptr;
	Flipper* rightFlipper = nullptr;
	PokeballChangerGroup* pokeballChangerGroup = nullptr;
	CaveSensorGroup* caveSensorGroup = nullptr;
	LapSensorGroup* lapSensorGroup = nullptr;
	CenterRedArrowGroup* centerRedArrowGroup = nullptr;
	BonusMultiplierSensorGroup* bonusMultiplierSensorGroup = nullptr;
	StaryuBumper* staryuBumper = nullptr;

	DittoColliders* dittoColliders=nullptr;
	b2Body* staryuCollider = nullptr;

	//Create
	void LoadMap(std::string path) override;
	void SetState(GameStates stateToChange) override;


	std::string mapPath = "Assets/MapData/";

public:
	ModuleGameRedMap(Application* app, bool start_enabled = true);
	~ModuleGameRedMap();

	bool Start();
	update_status Update();
	bool CleanUp();

	bool IsTopSideCovered();
};

