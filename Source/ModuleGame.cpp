#include "ModuleGame.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "GameUI.h"

#include "ModuleHighScore.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

	
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	map_texture = App->texture->GetTexture("map_redMap");

	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	return true;
}

update_status ModuleGame::Update()
{
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		StartFadeIn(App->scene_highScore, WHITE, 0.3f);
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {

	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {

	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {

	}
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {

	}

	Rectangle rectBackground = { 0,0,160,144 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);

	UI->Render();

	ModuleScene::FadeUpdate();
	return UPDATE_CONTINUE;
}

bool ModuleGame::CleanUp()
{
	return true;
}
