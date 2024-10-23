#pragma once
#include "ModuleScene.h"
#include "raylib.h"
#include "Globals.h"
#include "AnimationSystem.h"
#include "ModuleUserPreferences.h"

class ModuleLevelSelection : public ModuleScene
{
private:
	int selectedLanguage;
	Texture2D* levelSelectionTexture;
	Texture2D* levelSelectionFrameTexture;

	Vector2 markSelectionPosition;
	Animator* animator;

	int audioSelectId;
	int audioMoveId;

public:
	ModuleLevelSelection(Application* app, bool start_enabled=true);
	~ModuleLevelSelection();
	bool Start();
	update_status Update();
	bool CleanUp();
};