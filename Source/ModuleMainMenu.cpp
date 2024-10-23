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
	pokeball_animator->SetSpeed(0.1);
	pokeball_animator->SelectAnimation("Boing", true);


	AnimationData idleAnim = AnimationData("Idle");
	idleAnim.AddSprite(Sprite{ background_texture,{0, (float)selectedLanguage}, {160,144} });
	background_animator->AddAnimation(idleAnim);
	background_animator->SetSpeed(0.1);
	background_animator->SelectAnimation("Idle", false);

	AnimationData blinkAnim = AnimationData("Blink");
	blinkAnim.AddSprite(Sprite{ background_texture,{0, (float)selectedLanguage}, {160,144} });
	blinkAnim.AddSprite(Sprite{ background_texture,{1, (float)selectedLanguage}, {160,144} });
	blinkAnim.AddSprite(Sprite{ background_texture,{2, (float)selectedLanguage}, {160,144} });
	background_animator->AddAnimation(blinkAnim);
	background_animator->SetSpeed(0.1);

	blinkTimer.Start();

	App->audio->PlayMusic("Assets/Music/Tiitle_Screen.wav", 0.3f);

	audioSelectId = App->audio->LoadFx("Assets/SFX/Select.ogg");

	StartFadeOut(WHITE, 0.3f);

	return ret;
}

update_status ModuleMainMenu::Update()
{
	if (scrollMenuTimer.ReadSec() > scrollMenuTimeMS) {
		if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
			if (currentButton > 0) {
				currentButton--;
			}
			scrollMenuTimer.Start();
		}
		else if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
			if (currentButton < 2) {
				currentButton++;
			}
			scrollMenuTimer.Start();
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

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {

		switch (currentButton) {
		case 0:		
			//Go to game
			StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);
			App->audio->StopMusic();
			App->audio->PlayFx(audioSelectId);		
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
		}
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

	LOG("Unloading Intro scene");
	return true;
}
