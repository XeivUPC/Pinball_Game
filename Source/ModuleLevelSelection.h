#pragma once
#include "ModuleGame.h"
#include "raylib.h"
#include "Globals.h"
#include "AnimationSystem.h"
#include "ModuleUserPreferences.h"

class ModuleLevelSelection : public ModuleGame
{
private:
	int selectedLanguage;
	Texture2D* levelSelectionTexture;
	Texture2D* levelSelectionFrameTexture;

	Vector2 markSelectionPosition;
	Animator* anim;
public:
	ModuleLevelSelection(Application* app, bool start_enabled=true);
	~ModuleLevelSelection();
	bool Start();
	update_status Update();
	bool CleanUp();
};