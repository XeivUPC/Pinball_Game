#pragma once
#include "ModuleGame.h"
#include "raylib.h"

enum Languages
{
	Japanese,
	English,
	French,
	German,
	Spanish,
	Italian
};

class LevelSelectionGameScene : public ModuleGame
{
private:
	Texture2D levelSelectionTexture;
	KeyboardKey toLeftButton;
	KeyboardKey toRightButton;
	Vector2 markSelectionPosition;
public:
	LevelSelectionGameScene();
	~LevelSelectionGameScene();
	bool Start();
	update_status Update();
	bool CleanUp();
};