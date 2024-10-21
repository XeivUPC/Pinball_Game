#include "ModuleCredits.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleMainMenu.h"
#include "ModuleUserPreferences.h"

ModuleCredits::ModuleCredits(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

}

ModuleCredits::~ModuleCredits()
{}

bool ModuleCredits::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->texture->CreateTexture("Assets/CreditsScene.png", "texture_credits");
	texture_credits = App->texture->GetTexture("texture_credits");

	delay.Start();

	backgroundOpacity = 255;
	colorFadeOpacity = 255;

	language = App->userPreferences->GetLanguage();

	if (language > 0) {
		language = 1;
	}

	return ret;
}

update_status ModuleCredits::Update()
{
	
	
	if (delay.ReadSec() < 5) {
		Color color = { 255,255,255,(int)backgroundOpacity };
		Rectangle rect = { 160 * (int)language,144,160,144 };
		App->renderer->Draw(*texture_credits, 0, 0, &rect, color);

		if (delay.ReadSec() > 4) {
			if (backgroundOpacity > 0) {
				backgroundOpacity -= 400.0f * GetFrameTime();
			}
			if (backgroundOpacity < 0){
				backgroundOpacity = 0;
			}
		}
	}
	else {
		//Game
		App->scene_mainMenu->Enable();
		Disable();
	}
	
	if (delay.ReadSec() < 1) {
		Color color = { 255,255,255,(int)colorFadeOpacity };
		DrawRectangle(0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, color);
		if (colorFadeOpacity > 0) {
			colorFadeOpacity -=400.0f * GetFrameTime();
		}
		if (colorFadeOpacity < 0) {
			colorFadeOpacity = 0;
		}
		
	}
	
	
	return UPDATE_CONTINUE;
}

bool ModuleCredits::CleanUp()
{
	LOG("Unloading Credits scene");

	return true;
}
