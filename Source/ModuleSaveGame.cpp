#include "ModuleSaveGame.h"
#include "Application.h"
#include "ModuleUserPreferences.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleLevelSelection.h"
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

	audioSelectId = App->audio->LoadFx("Assets/SFX/Menu_Option_Select.ogg");
	audioMoveId = App->audio->LoadFx("Assets/SFX/Menu_Option_Move.ogg");
	audioStartGameId = App->audio->LoadFx("Assets/SFX/Menu_Option_StartGame.ogg");

	return ret;
}

update_status ModuleSaveGame::Update()
{
	Rectangle rect = { 0,(144 / 6) * (int)selectedLanguage,56,(144 / 6) };
	App->renderer->Draw(*background_texture, 0, 0, &rect);

	Rectangle rect1 = { 0,0,8,8 };

	if (scrollSaveTimer.ReadSec() > scrollSaveTimeMS) {
		if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
			if (currentButton > 0) {
				currentButton--;
			}
			App->audio->PlayFx(audioMoveId);
			App->renderer->Draw(*select_arrow, 0, 0, &rect1);//Set to correct pos
			scrollSaveTimer.Start();
		}
		else if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
			if (currentButton < 1) {
				currentButton++;
			}
			App->audio->PlayFx(audioMoveId);
			App->renderer->Draw(*select_arrow, 0, 0, &rect1);//Set to correct pos 
			scrollSaveTimer.Start();
		}
	}
	
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {

		switch (currentButton) {
		case 0:
			//New Game
			StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);
			App->audio->StopMusic();
			App->audio->PlayFx(audioStartGameId);
			break;
		case 1:
			//Continue last game
			StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);//Change to LoadGame()
			App->audio->StopMusic();
			App->audio->PlayFx(audioStartGameId);
			break;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSaveGame::LoadGame()
{
}

void ModuleSaveGame::SaveGame()
{
}

bool ModuleSaveGame::CleanUp()
{
	if (background_animator != nullptr) {
		delete background_animator;
		background_animator = nullptr;
	}
	if (select_arrow_animator != nullptr) {
		delete select_arrow_animator;
		select_arrow_animator = nullptr;
	}

	LOG("Unloading SaveGame scene");

	return true;
}
