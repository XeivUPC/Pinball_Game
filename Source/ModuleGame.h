#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"

class GameUI;

class ModuleGame : public ModuleScene {
private:
	Texture* map_texture;
	GameUI* UI;

public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
};

