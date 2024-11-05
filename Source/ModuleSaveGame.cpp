#include "ModuleSaveGame.h"
#include "Application.h"
#include "ModuleUserPreferences.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

ModuleSaveGame::ModuleSaveGame(Application* app, bool start_enabled) : ModuleMainMenu(app, start_enabled)
{

}

ModuleSaveGame::~ModuleSaveGame()
{
}

bool ModuleSaveGame::Start()
{
	LOG("Loading SaveGame");
	bool ret = true;
	currentButton = 0;

	selectedLanguage = App->userPreferences->GetLanguage();


	App->texture->CreateTexture("Assets/save_menu.png", "save_menu");
	background_texture = App->texture->GetTexture("save_menu");

	App->texture->CreateTexture("Assets/language_select_arrow.png", "language_select_arrow");
	select_arrow = App->texture->GetTexture("language_select_arrow");

	

	return ret;
}

update_status ModuleSaveGame::Update()
{
	Rectangle rect = { 0,(144 / 6) * (int)selectedLanguage,56,(144 / 6) };
	App->renderer->Draw(*background_texture, 0, 0, &rect);


	return UPDATE_CONTINUE;
}

bool ModuleSaveGame::CleanUp()
{
	LOG("Unloading SaveGame scene");

	return true;
}

void ModuleSaveGame::LoadGame()
{
}

void ModuleSaveGame::SaveGame()
{
}
