#include "ModuleLevelSelection.h"
#include "Application.h"
#include "ModuleTexture.h"


ModuleLevelSelection::ModuleLevelSelection(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{}

ModuleLevelSelection::~ModuleLevelSelection()
{}

bool ModuleLevelSelection::Start()
{
	selectedLanguage = App->userPreferences->GetLanguage();
	anim = new Animator(App);

	App->texture->CreateTexture("Assets/LevelSelection.png", "levelSelectionBackground");
	levelSelectionTexture = App->texture->GetTexture("levelSelectionBackground");

	App->texture->CreateTexture("Assets/LevelSelection_Frame.png", "levelSelectedFrame");
	levelSelectionFrameTexture = App->texture->GetTexture("levelSelectedFrame");

	AnimationData animDefault = AnimationData("Active");
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{0, 0}, {64,88} });
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{1, 0}, {64,88} });
	animDefault.AddSprite(Sprite{ levelSelectionFrameTexture,{2, 0}, {64,88} });
	anim->AddAnimation(animDefault);

	anim->SetSpeed(0.1);
	anim->SelectAnimation("Active", true);

	markSelectionPosition = { 3, 5.5f };
	return true;
}

update_status ModuleLevelSelection::Update()
{
	anim->Update();
	if(IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT)))
	{
		markSelectionPosition.x = 3;
	}
	else if(IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT)))
	{
		markSelectionPosition.x = 21;
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		///Load Level
	}


	DrawTexturePro(*levelSelectionTexture, { 0,(float)selectedLanguage * 144,160,144 }, {0, 0, SCREEN_SIZE*SCREEN_WIDTH, SCREEN_SIZE*SCREEN_HEIGHT}, { 0, 0 },0, WHITE);
	anim->Animate(markSelectionPosition.x * SCREEN_SIZE, markSelectionPosition.y * SCREEN_SIZE, false);
	return UPDATE_CONTINUE;
}

bool ModuleLevelSelection::CleanUp()
{
	delete anim;
	return true;
}
