#include "ModuleSaveGame.h"
#include "Application.h"
#include "ModuleUserPreferences.h"

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

	return ret;
}

update_status ModuleSaveGame::Update()
{
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
