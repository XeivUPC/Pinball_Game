#pragma once
#include "ModuleScene.h"
#include "raylib.h"
#include "Globals.h"
#include "AnimationSystem.h"
#include "ModuleUserPreferences.h"

class ModuleLevelSelection : public ModuleScene
{
private:
	int selectedLanguage = -1;
	Texture2D* levelSelectionTexture=nullptr;
	Texture2D* levelSelectionFrameTexture=nullptr;

	Vector2 markSelectionPosition = {0,0};
	Animator* animator = nullptr;

	int audioSelectId=-1;
	int audioMoveId =-1;

public:
	ModuleLevelSelection(Application* app, bool start_enabled=true);
	~ModuleLevelSelection();
	bool Start();
	update_status Update();
	bool CleanUp();
};