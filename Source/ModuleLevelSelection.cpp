#include "ModuleLevelSelection.h"
#include "ModuleMainMenu.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include "ModuleHighScore.h"
#include "ModuleGameRedMap.h"
#include "ModuleGameBlueMap.h"


ModuleLevelSelection::ModuleLevelSelection(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{}

ModuleLevelSelection::~ModuleLevelSelection()
{}

bool ModuleLevelSelection::Start()
{
	selectedLanguage = App->userPreferences->GetLanguage();
	animator = new Animator(App);

	App->texture->CreateTexture("Assets/LevelSelection.png", "levelSelectionBackground");
	levelSelectionTexture = App->texture->GetTexture("levelSelectionBackground");

	App->texture->CreateTexture("Assets/LevelSelection_Frame.png", "levelSelectedFrame");
	levelSelectionFrameTexture = App->texture->GetTexture("levelSelectedFrame");

	AnimationData animDefault = AnimationData("Active");
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{0, 0}, {64,88} });
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{1, 0}, {64,88} });
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{2, 0}, {64,88} });
	animator->AddAnimation(animDefault);

	animator->SetSpeed(0.1);
	animator->SelectAnimation("Active", true);

	markSelectionPosition = { 3, 5.5f };

	App->audio->PlayMusic("Assets/Music/Field_Select.wav",0.3f);


	audioSelectId = App->audio->LoadFx("Assets/SFX/Menu_Option_Select.ogg");
	audioMoveId = App->audio->LoadFx("Assets/SFX/Level_Selection_Move.ogg");

	StartFadeOut(WHITE, 0.3f);
	return true;
}

update_status ModuleLevelSelection::Update()
{
	animator->Update();
	if(IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
	{
		if(markSelectionPosition.x!=3)
			App->audio->PlayFx(audioMoveId);
		markSelectionPosition.x = 3;
	}
	else if(IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
	{
		if (markSelectionPosition.x != 21)
			App->audio->PlayFx(audioMoveId);
		markSelectionPosition.x = 21;
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		///Load Level
		App->audio->PlayFx(audioSelectId);

		if (markSelectionPosition.x < 10) {
			App->scene_highScore->SetVersionColor(0);
			StartFadeIn(App->scene_game_redMap, WHITE, 0.3f);
		}
		else {
			App->scene_highScore->SetVersionColor(1);
			StartFadeIn(App->scene_game_blueMap, WHITE, 0.3f);
		}
	}
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
		///Go Back
		StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);

		App->audio->StopMusic();
		App->audio->PlayFx(audioSelectId);
	}


	DrawTexturePro(*levelSelectionTexture, { 0,(float)selectedLanguage * 144,160,144 }, {0, 0, SCREEN_SIZE*SCREEN_WIDTH, SCREEN_SIZE*SCREEN_HEIGHT}, { 0, 0 },0, WHITE);
	animator->Animate(markSelectionPosition.x * SCREEN_SIZE, markSelectionPosition.y * SCREEN_SIZE, false);

	ModuleScene::FadeUpdate();
	return UPDATE_CONTINUE;
}

bool ModuleLevelSelection::CleanUp()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	return true;
}
