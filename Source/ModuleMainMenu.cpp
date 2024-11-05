#include "ModuleMainMenu.h"
#include "ModuleSettings.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleLevelSelection.h"
#include "ModuleUserPreferences.h"


ModuleMainMenu::ModuleMainMenu(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModuleMainMenu::~ModuleMainMenu()
{

}


bool ModuleMainMenu::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	currentButton = 0;

	selectedLanguage = App->userPreferences->GetLanguage();


	App->texture->CreateTexture("Assets/main_menu_background.png", "main_menu_background");
	background_texture = App->texture->GetTexture("main_menu_background");

	App->texture->CreateTexture("Assets/main_menu_pokeball.png", "main_menu_pokeball");
	pokeball_texture = App->texture->GetTexture("main_menu_pokeball");

	App->texture->CreateTexture("Assets/language_select_arrow.png", "language_select_arrow");
	select_arrow = App->texture->GetTexture("language_select_arrow");

	App->texture->CreateTexture("Assets/main_menu_save&continue.png", "main_menu_save&continue");
	main_menu_save = App->texture->GetTexture("main_menu_save&continue");

	pokeball_animator = new Animator(App);
	background_animator = new Animator(App);

	AnimationData pokeballAnim = AnimationData("Boing");
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{1, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{2, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{3, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{4, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{5, 0}, {16,16} });
	pokeball_animator->AddAnimation(pokeballAnim);
	pokeball_animator->SetSpeed(0.1f);
	pokeball_animator->SelectAnimation("Boing", true);


	AnimationData idleAnim = AnimationData("Idle");
	idleAnim.AddSprite(Sprite{ background_texture,{0, (float)selectedLanguage}, {160,144} });
	background_animator->AddAnimation(idleAnim);
	background_animator->SetSpeed(0.1f);
	background_animator->SelectAnimation("Idle", false);

	AnimationData blinkAnim = AnimationData("Blink");
	blinkAnim.AddSprite(Sprite{ background_texture,{0, (float)selectedLanguage}, {160,144} });
	blinkAnim.AddSprite(Sprite{ background_texture,{1, (float)selectedLanguage}, {160,144} });
	blinkAnim.AddSprite(Sprite{ background_texture,{2, (float)selectedLanguage}, {160,144} });
	background_animator->AddAnimation(blinkAnim);
	background_animator->SetSpeed(0.1f);

	blinkTimer.Start();

	App->audio->PlayMusic("Assets/Music/Title_Screen.wav", 0.3f);


	audioSelectId = App->audio->LoadFx("Assets/SFX/Menu_Option_Select.ogg");
	audioMoveId = App->audio->LoadFx("Assets/SFX/Menu_Option_Move.ogg");
	audioStartGameId = App->audio->LoadFx("Assets/SFX/Menu_Option_StartGame.ogg");

	StartFadeOut(WHITE, 0.3f);

	switch (selectedLanguage)
	{
	case 0:
		rect_main_menu_save = {0,(float)selectedLanguage * 24,47,24};
		break;
	case 1:
		rect_main_menu_save = { 0,(float)selectedLanguage * 24,47,24};
		break;												 
	case 2:													 
		rect_main_menu_save = { 0,(float)selectedLanguage * 24,56,24};
		break;												 
	case 3:													 
		rect_main_menu_save = { 0,(float)selectedLanguage * 24,56,24};
		break;												 
	case 4:													 
		rect_main_menu_save = { 0,(float)selectedLanguage * 24,56,24};
		break;
	case 5:
		rect_main_menu_save = { 0,(float)selectedLanguage * 24,47,24};
		break;
	default:
		break;
	}
	is_in_menu_save = false;

	return ret;
}

update_status ModuleMainMenu::Update()
{
	if (is_in_menu_save) {
		if (scrollMenuTimer.ReadSec() > scrollMenuTimeMS) {
			if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
				if (currentButton_save_menu > 0) {
					currentButton_save_menu--;
				}
				App->audio->PlayFx(audioMoveId);
				scrollMenuTimer.Start();
			}
			else if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
				if (currentButton_save_menu < 1) {
					currentButton_save_menu++;
				}
				App->audio->PlayFx(audioMoveId);
				scrollMenuTimer.Start();
			}
		}
	}
	else {
		if (scrollMenuTimer.ReadSec() > scrollMenuTimeMS) {
			if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
				if (currentButton > 0) {
					currentButton--;
				}
				App->audio->PlayFx(audioMoveId);
				scrollMenuTimer.Start();
			}
			else if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
				if (currentButton < 2) {
					currentButton++;
				}
				App->audio->PlayFx(audioMoveId);
				scrollMenuTimer.Start();
			}
		}
	}



	pokeball_animator->Update();
	background_animator->Update();



	if (blinkTimer.ReadSec() < 4) {
		background_animator->SelectAnimation("Idle", false);
	}
	else if (blinkTimer.ReadSec() >= 4 && blinkTimer.ReadSec() <= 4.3) {
		background_animator->SelectAnimation("Blink", false);
	}
	else if (blinkTimer.ReadSec() > 4.3 && blinkTimer.ReadSec() < 5) {
		background_animator->SelectAnimation("Idle", false);
	}
	else if (blinkTimer.ReadSec() >= 5 && blinkTimer.ReadSec() <= 5.6) {
		background_animator->SelectAnimation("Blink", true);

	}
	else if (blinkTimer.ReadSec() > 5.6) {
		blinkTimer.Start();
	}


	background_animator->Animate(0, 0, false);

	if (is_in_menu_save)
	{
		App->renderer->Draw(*main_menu_save, (SCREEN_WIDTH / 2) - (rect_main_menu_save.width / 2), (SCREEN_HEIGHT / 2) - (rect_main_menu_save.height / 2) - OffsetX_main_menu_save, &rect_main_menu_save);
	}


	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {

		if (is_in_menu_save)
		{
			switch (currentButton)
			{
			case 0:
				//Go to game
				StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);
				App->audio->StopMusic();
				App->audio->PlayFx(audioStartGameId);

				break;
			case 1:
				//Continue
				App->audio->StopMusic();
				App->audio->PlayFx(audioSelectId);
				break;
			default:
				break;
			}
			

		}
		else
		{
			switch (currentButton)
			{
			case 0:
				//Go to save menu
				SetIsInMenuSave(true);
				break;
			case 1:
				//Go to pokedex
				App->audio->PlayFx(audioSelectId);
				break;
			case 2:
				//Go to options
				StartFadeIn(App->scene_settings, WHITE, 0.3f);
				App->audio->StopMusic();
				App->audio->PlayFx(audioSelectId);
				break;
			default:
				break;
			}
		}
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
		///Go Back
		App->audio->PlayFx(audioSelectId);
		if (is_in_menu_save) {
			currentButton_save_menu = 0;
			is_in_menu_save = false;
		}
		else {

			//StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
			//App->audio->StopMusic();
			//App->audio->PlayFx(audioSelectId);
		}

	}
	
	if (is_in_menu_save) {
		Rectangle rect = { 0, 0, 8, 8 };
		App->renderer->Draw(*select_arrow, (SCREEN_WIDTH / 2) - (rect_main_menu_save.width / 2),(SCREEN_HEIGHT / 2) - (rect_main_menu_save.height / 2) + (currentButton_save_menu * 10), &rect);
	}
	
	pokeball_animator->Animate(6, 97 + 12 * currentButton, false);
	

	ModuleScene::FadeUpdate();
	
	return UPDATE_CONTINUE;
	
}

bool ModuleMainMenu::CleanUp()
{
	if (background_animator != nullptr) {
		delete background_animator;
		background_animator = nullptr;
	}
	if (pokeball_animator != nullptr) {
		delete pokeball_animator;
		pokeball_animator = nullptr;
	}
	if (select_arrow_animator != nullptr) {
		delete select_arrow_animator;
		select_arrow_animator = nullptr;
	}
	if (main_menu_save_animator != nullptr) {
		delete main_menu_save_animator;
		main_menu_save_animator = nullptr;
	}

	LOG("Unloading Intro scene");
	return true;
}

void ModuleMainMenu::SetIsInMenuSave(bool is_in_menu_save_)
{
	is_in_menu_save = is_in_menu_save_;
}