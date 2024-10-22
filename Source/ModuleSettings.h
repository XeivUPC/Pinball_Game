#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"

class ModuleSettings : public ModuleScene {
private:
	int currentButton = 0;
	int subCurrentButton = 0;

	bool selected = false;

	Texture* arrow_texture;

	Texture* vibrationType_texture;

	Texture* pokeball_texture;
	Animator* pokeball_animator;

	Texture* psyduck_texture;
	Animator* psyduck_animator;

	Texture* pikachu_texture;
	Animator* pikachu_animator;

	Texture* background_texture;

	int selectedLanguage;
	int selectedVibration;


	int audioSelectId;

	void SetPokemonAnimations();


public:
	ModuleSettings(Application* app, bool start_enabled = true);
	~ModuleSettings();

	bool Start();
	update_status Update();
	bool CleanUp();
};

