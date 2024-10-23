#include "ModuleSettings.h"
#include "ModuleMainMenu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"


ModuleSettings::ModuleSettings(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

}

ModuleSettings::~ModuleSettings()
{

}

bool ModuleSettings::Start()
{
	currentButton = 0;
	selected = false;

	selectedVibration = App->userPreferences->GetVibration();
	selectedLanguage = App->userPreferences->GetLanguage();

	App->texture->CreateTexture("Assets/settings_menu_background.png", "settings_menu_background");
	background_texture = App->texture->GetTexture("settings_menu_background");

	App->texture->CreateTexture("Assets/settings_menu_vibration_options.png", "settings_menu_vibration_options");
	vibrationType_texture = App->texture->GetTexture("settings_menu_vibration_options");

	App->texture->CreateTexture("Assets/settings_select_arrow.png", "settings_select_arrow");
	arrow_texture = App->texture->GetTexture("settings_select_arrow");

	App->texture->CreateTexture("Assets/main_menu_pokeball.png", "main_menu_pokeball");
	pokeball_texture = App->texture->GetTexture("main_menu_pokeball");

	App->texture->CreateTexture("Assets/settings_menu_psyduck.png", "settings_menu_psyduck");
	psyduck_texture = App->texture->GetTexture("settings_menu_psyduck");

	App->texture->CreateTexture("Assets/settings_menu_pikachu.png", "settings_menu_pikachu");
	pikachu_texture = App->texture->GetTexture("settings_menu_pikachu");



	pokeball_animator = new Animator(App);
	AnimationData pokeballAnim = AnimationData("Boing");
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{1, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{2, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{3, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{4, 0}, {16,16} });
	pokeballAnim.AddSprite(Sprite{ pokeball_texture,{5, 0}, {16,16} });

	AnimationData pokeballAnimStatic = AnimationData("Static");
	pokeballAnimStatic.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });

	pokeball_animator->AddAnimation(pokeballAnim);
	pokeball_animator->AddAnimation(pokeballAnimStatic);

	pokeball_animator->SetSpeed(0.1f);
	pokeball_animator->SelectAnimation("Boing", true);


	///

	pikachu_animator = new Animator(App);
	AnimationData pikachuIdle = AnimationData("Idle");
	pikachuIdle.AddSprite(Sprite{ pikachu_texture,{0, 0}, {29,48} });

	AnimationData pikachuMoveInternational = AnimationData("MoveJapan");
	pikachuMoveInternational.AddSprite(Sprite{ pikachu_texture,{0, 0}, {29,56} });
	pikachuMoveInternational.AddSprite(Sprite{ pikachu_texture,{1, 0}, {29,56} });
	pikachuMoveInternational.AddSprite(Sprite{ pikachu_texture,{2, 0}, {29,56} });
	pikachuMoveInternational.AddSprite(Sprite{ pikachu_texture,{3, 0}, {29,56} });
	pikachuMoveInternational.AddSprite(Sprite{ pikachu_texture,{4, 0}, {29,56} });

	AnimationData pikachuMoveJapan = AnimationData("MoveInternational");
	pikachuMoveJapan.AddSprite(Sprite{ pikachu_texture,{0, 1}, {29,56} });
	pikachuMoveJapan.AddSprite(Sprite{ pikachu_texture,{1, 1}, {29,56} });
	pikachuMoveJapan.AddSprite(Sprite{ pikachu_texture,{2, 1}, {29,56} });
	pikachuMoveJapan.AddSprite(Sprite{ pikachu_texture,{3, 1}, {29,56} });
	pikachuMoveJapan.AddSprite(Sprite{ pikachu_texture,{4, 1}, {29,56} });

	pikachu_animator->AddAnimation(pikachuIdle);
	pikachu_animator->AddAnimation(pikachuMoveInternational);
	pikachu_animator->AddAnimation(pikachuMoveJapan);

	pikachu_animator->SetSpeed(0.1f);
	pikachu_animator->SelectAnimation("Idle", true);

	psyduck_animator = new Animator(App);
	AnimationData psyduckIdle = AnimationData("Idle");
	psyduckIdle.AddSprite(Sprite{ psyduck_texture,{0, 0}, {40,56} });

	AnimationData psyduckMove = AnimationData("Move");
	psyduckMove.AddSprite(Sprite{ psyduck_texture,{3, 0}, {40,56} });
	psyduckMove.AddSprite(Sprite{ psyduck_texture,{4, 0}, {40,56} });

	psyduck_animator->AddAnimation(psyduckIdle);
	psyduck_animator->AddAnimation(psyduckMove);

	psyduck_animator->SetSpeed(0.05f);
	psyduck_animator->SelectAnimation("Idle", true);



	
	App->audio->PlayMusic("Assets/Music/Options_Screen.wav", 0.3f);
	audioSelectId = App->audio->LoadFx("Assets/SFX/Select.ogg");

	StartFadeOut(WHITE, 0.3f);

	return true;
}

update_status ModuleSettings::Update()
{
	pokeball_animator->Update();
	pikachu_animator->Update();
	psyduck_animator->Update();

	if (!selected) {
		pokeball_animator->SelectAnimation("Boing", true);

		pikachu_animator->SelectAnimation("Idle", true);
		psyduck_animator->SelectAnimation("Idle", true);

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
	}
	else {
		pokeball_animator->SelectAnimation("Static", true);

		if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
		{
			switch (currentButton) {
				case 0:
					subCurrentButton = (int)App->userPreferences->PreviousVibration();
					selectedVibration = subCurrentButton;

					SetPokemonAnimations();

					break;

				case 2:
					subCurrentButton = (int)App->userPreferences->PreviousLanguage();
					selectedLanguage = subCurrentButton;
					break;
			}

		}
		else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
		{
			switch (currentButton) {
				case 0:
					subCurrentButton = (int)App->userPreferences->NextVibration();
					selectedVibration = subCurrentButton;

					SetPokemonAnimations();
					break;

				case 2:
					subCurrentButton = (int)App->userPreferences->NextLanguage();
					selectedLanguage = subCurrentButton;
					break;
			}
		}
	}
	


	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {

		switch (currentButton) {
		case 0:
			//Go to game
			selected = true;
			subCurrentButton = App->userPreferences->GetVibration();
			App->audio->PlayFx(audioSelectId);

			SetPokemonAnimations();

			break;
		case 1:
			StartFadeIn(App->scene_keybinds, WHITE, 0.3f);
			App->audio->PlayFx(audioSelectId);
			break;
		case 2:

			selected = true;
			subCurrentButton = App->userPreferences->GetLanguage();
			App->audio->PlayFx(audioSelectId);
			break;
		}
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
		///Go Back
		if (selected) {
			
			selected = false;
		}
		else {
			
			StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
			App->audio->StopMusic();
			//App->audio->PlayFx(audioSelectId);
		}
		
	}


	Rectangle rectBackground = { 0,selectedLanguage*144,160,144 };
	App->renderer->Draw(*background_texture, 0, 0, &rectBackground, WHITE);

	Rectangle rectvibrationType = { 48*selectedVibration,8*selectedLanguage,48,8 };
	App->renderer->Draw(*vibrationType_texture, 96, 24, &rectvibrationType, WHITE);

	if (selected) {
		Rectangle rectArrow = { 0, 0,64,16 };
		App->renderer->Draw(*arrow_texture, 87, 20 + 16 * currentButton, &rectArrow, WHITE);
	}
	pokeball_animator->Animate(6, 18 + 16 * currentButton, false);

	pikachu_animator->Animate(120,80, false);
	psyduck_animator->Animate(80,80, false);

	ModuleScene::FadeUpdate();
	return UPDATE_CONTINUE;
}

bool ModuleSettings::CleanUp()
{

	if (pokeball_animator != nullptr) {
		delete pokeball_animator;
		pokeball_animator = nullptr;
	}
	if (psyduck_animator != nullptr) {
		delete psyduck_animator;
		psyduck_animator = nullptr;
	}
	if (pikachu_animator != nullptr) {
		delete pikachu_animator;
		pikachu_animator = nullptr;
	}
	return true;
}

void ModuleSettings::SetPokemonAnimations()
{
	pikachu_animator->SelectAnimation("Idle", true);

	if (selectedVibration == 2)
		psyduck_animator->SelectAnimation("Idle", true);
	else {
		if (selectedVibration == 0) {
			psyduck_animator->SelectAnimation("Move", true);
			psyduck_animator->SetSpeed(0.05f);
		}
		else {
			psyduck_animator->SelectAnimation("Move", true);
			psyduck_animator->SetSpeed(0.07f);
		}

		if (selectedLanguage == 0)
			pikachu_animator->SelectAnimation("MoveJapan", false);
		else
			pikachu_animator->SelectAnimation("MoveInternational", false);
	}

	

}