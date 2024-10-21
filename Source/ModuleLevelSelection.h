#pragma once
#include "ModuleGame.h"
#include "raylib.h"
#include "Globals.h"
#include "AnimationSystem.h"

enum Language
{
	Japanese,
	English,
	French,
	German,
	Spanish,
	Italian
};

class ModuleLevelSelection : public ModuleGame
{
private:
	Language selectedLanguage;
	Texture2D* levelSelectionTexture;
	Texture2D* levelSelectionFrameTexture;
	KeyboardKey toLeftButton;
	KeyboardKey toRightButton;
	Vector2 markSelectionPosition;
	Animator* anim;
public:
	ModuleLevelSelection(Application* app, bool start_enabled=true);
	~ModuleLevelSelection();
	bool Start();
	update_status Update();
	bool CleanUp();
};