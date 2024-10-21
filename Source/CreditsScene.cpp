#include "CreditsScene.h"

CreditsScene::CreditsScene(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

}

CreditsScene::~CreditsScene()
{}

bool CreditsScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	switch (language)
	{
	case CreditsScene::language::NA:
		texture_credits = texture_credits_NA;
		break;
	case CreditsScene::language::EU:
		texture_credits = texture_credits_EU;
		break;
	case CreditsScene::language::JAPAN:
		texture_credits = texture_credits_JAPAN;
		break;
	default:
		break;
	}

	delay.Start();
	float opacity = 255;

	return ret;
}

update_status CreditsScene::Update()
{
	if (delay.ReadSec() < 3)
	{
		DrawRectangle(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, WHITE);
	}
	else if (delay.ReadSec() < 6) {

		DrawTexture(texture_credits, 0, 0, WHITE);
	}
	else if(delay.ReadSec() < 9){
		
		DrawTexture(texture_credits, 0, 0, {255,255,255,opacity});
		opacity--;
	}
	else {
		//Game
	}
	
	return UPDATE_CONTINUE;
}

bool CreditsScene::CleanUp()
{
	LOG("Unloading Credits scene");

	return true;
}
