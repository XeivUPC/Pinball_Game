#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"

class ModuleGame : public ModuleScene {
private:
	Texture* map_texture;

public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
};

