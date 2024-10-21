#include "ModuleMainMenu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleLevelSelection.h"


ModuleMainMenu::ModuleMainMenu(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
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

	App->texture->CreateTexture("Assets/main_menu_background.png", "background");
	background_texture = App->texture->GetTexture("background");

	App->texture->CreateTexture("Assets/main_menu_pokeball.png", "pokeball");
	pokeball_texture = App->texture->GetTexture("pokeball");

	pokeball_animator = new Animator(App);
	background_animator = new Animator(App);

	AnimationData pokeballAnim = AnimationData("Boing");
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{1, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{2, 0}, {16,16} });
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

	return ret;
}

update_status ModuleMainMenu::Update()
{

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
		if (currentButton > 0) {
			currentButton--;
		}
	}
	else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
		if (currentButton < 2) {
			currentButton++;
		}
	}


	pokeball_animator->Update();
	background_animator->Update();



	if (blinkTimer.ReadSec() < 5) {
		background_animator->SelectAnimation("Idle", false);
	}
	else if (blinkTimer.ReadSec() >= 5 && blinkTimer.ReadSec() <= 5.3) {
		background_animator->SelectAnimation("Blink", false);
	}
	else if (blinkTimer.ReadSec() > 5.3 && blinkTimer.ReadSec() < 6) {
		background_animator->SelectAnimation("Idle", false);
	}
	else if (blinkTimer.ReadSec() >= 6 && blinkTimer.ReadSec() <= 6.6) {
		background_animator->SelectAnimation("Blink", true);

	}
	else if (blinkTimer.ReadSec() > 6.6) {
		blinkTimer.Start();
	}


	background_animator->Animate(0, 0, false);

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {

		switch (currentButton) {
		case 0:		
			//Go to game
			Disable();
			App->scene_levelSelection->Enable();
			break;
		case 1:
			//Go to pokedex

			break;
		case 2:
			//Go to options

			break;
		}
	}
	pokeball_animator->Animate(6, 99 + 12 * currentButton , false);
	
	return UPDATE_CONTINUE;
	
}

bool ModuleMainMenu::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
