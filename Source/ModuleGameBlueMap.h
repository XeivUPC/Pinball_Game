#pragma once

#include "AnimationSystem.h"
#include "ModuleGame.h"
#include "GameUI.h"
#include "TimerUI.h"
#include "Flipper.h"
#include "PokeballChangerGroup.h"
#include "CaveSensorGroup.h"
#include "LapSensorGroup.h"
#include "CenterBlueArrowGroup.h"
#include "BonusMultiplierSensorGroup.h"


using namespace pugi;

class ModuleGameBlueMap : public ModuleGame {
private:

	PokeballChangerGroup* pokeballChangerGroup = nullptr;
	CaveSensorGroup* caveSensorGroup = nullptr;
	LapSensorGroup* lapSensorGroup = nullptr;
	CenterBlueArrowGroup* centerBlueArrowGroup = nullptr;
	BonusMultiplierSensorGroup* bonusMultiplierSensorGroup = nullptr;

	Flipper* leftFlipper = nullptr;
	Flipper* rightFlipper = nullptr;

	b2Body* entryCollider = nullptr;
	
	//Create
	void LoadMap(std::string path) override;
	void SetState(GameStates stateToChange) override;

	std::string mapPath = "Assets/MapData/";

	int audioGameStartId = -1;
	int audioGameRestartId = -1;
	int audioGameOverId = -1;
public:
	ModuleGameBlueMap(Application* app, bool start_enabled = true);
	~ModuleGameBlueMap();

	bool Start();
	update_status Update();
	bool CleanUp();
};

