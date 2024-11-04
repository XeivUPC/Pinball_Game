#include "ModuleCredits.h"
#include "ModuleRender.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleMainMenu.h"
#include "ModuleUserPreferences.h"

ModuleCredits::ModuleCredits(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
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

	language = App->userPreferences->GetLanguage();

	if (language > 0) {
		language = 1;
	}

	StartFadeOut(WHITE,0.3f);

	return ret;
}

update_status ModuleCredits::Update()
{
	Rectangle rect = { 160.0f * (int)language,144,160,144 };
	App->renderer->Draw(*texture_credits, 0, 0, &rect);
	
	if (delay.ReadSec() > 5) {	
		StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
	}


	ModuleScene::FadeUpdate();
	
	return UPDATE_CONTINUE;
}

bool ModuleCredits::CleanUp()
{
	
	LOG("Unloading Credits scene");

	return true;
}
