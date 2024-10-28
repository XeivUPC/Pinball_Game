#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"

class GameUI;

class ModuleGame : public ModuleScene {
private:
	Texture* map_texture;

	Texture* paddle_texture;
	Animator* paddleLeft_animator;
	Animator* paddleRight_animator;

	GameUI* UI;

	//Controls

	void RepositionCamera();

	void MovePaddles();



public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
};

