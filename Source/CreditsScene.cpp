#include "CreditsScene.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleTexture.h"

CreditsScene::CreditsScene(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

}

CreditsScene::~CreditsScene()
{}

bool CreditsScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->texture->CreateTexture("Assets/CreditsScene.png", "texture_credits");
	texture_credits = App->texture->GetTexture("texture_credits");

	delay.Start();
	int opacity = 255;

	return ret;
}

update_status CreditsScene::Update()
{
	
	if (delay.ReadSec() < 3)
	{
		Color color = {255,255,255,opacity };
		DrawRectangle(0, 0, SCREEN_HEIGHT, SCREEN_WIDTH,color);
		opacity--;
	}
	else if (delay.ReadSec() < 6) {
		Rectangle rect = { 0,144 * (int)language,160,144 };
		App->renderer->Draw(*texture_credits, 0, 0, &rect, 0);
	}
	else if(delay.ReadSec() < 9){
		Rectangle rect = { 0,144 * (int)language,160,144 };
		App->renderer->Draw(*texture_credits, 0, 0, &rect, 0);
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
