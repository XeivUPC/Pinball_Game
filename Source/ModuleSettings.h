#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"

class ModuleSettings : public ModuleScene {
private:
	int currentButton = 0;
	int subCurrentButton = 0;

	bool selected = false;

	Texture* arrow_texture=nullptr;

	Texture* vibrationType_texture = nullptr;

	Texture* pokeball_texture = nullptr;
	Animator* pokeball_animator = nullptr;

	Texture* psyduck_texture = nullptr;
	Animator* psyduck_animator = nullptr;

	Texture* pikachu_texture = nullptr;
	Animator* pikachu_animator = nullptr;

	Texture* background_texture = nullptr;

	int selectedLanguage=-1;
	int selectedVibration=-1;


	int audioSelectId=-1;
	int audioMoveId=-1;


	Timer scrollMenuTimer;
	float scrollMenuTimeMS = 0.2f;

	void SetPokemonAnimations();


public:
	ModuleSettings(Application* app, bool start_enabled = true);
	~ModuleSettings();

	bool Start();
	update_status Update();
	bool CleanUp();
};

