#include "LevelSelectionGameScene.h"

LevelSelectionGameScene::LevelSelectionGameScene()
{}

LevelSelectionGameScene::~LevelSelectionGameScene()
{}

bool LevelSelectionGameScene::Start()
{
	levelSelectionTexture = LoadTexture("");
	return true;
}

update_status LevelSelectionGameScene::Update()
{
	if(IsKeyDown(toLeftButton))
	{
		markSelectionPosition.x = 100;
	}
	else if(IsKeyDown(toRightButton))
	{
		markSelectionPosition.x = 400;
	}
	//Render
	return UPDATE_CONTINUE;
}

bool LevelSelectionGameScene::CleanUp()
{
	UnloadTexture(levelSelectionTexture);
	return true;
}
