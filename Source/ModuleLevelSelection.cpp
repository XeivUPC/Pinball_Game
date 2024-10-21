#include "ModuleLevelSelection.h"
#include "Application.h"
#include "ModuleTexture.h"

ModuleLevelSelection::ModuleLevelSelection(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{}

ModuleLevelSelection::~ModuleLevelSelection()
{}

bool ModuleLevelSelection::Start()
{
	toLeftButton = KEY_A;
	toRightButton = KEY_D;
	selectedLanguage = Spanish;
	anim = new Animator(App);

	App->texture->CreateTexture("Assets/LevelSelection.png", "levelSelectionBackground");
	levelSelectionTexture = App->texture->GetTexture("levelSelectionBackground");

	App->texture->CreateTexture("Assets/LevelSelection_Frame.png", "levelSelectedFrame");
	levelSelectionFrameTexture = App->texture->GetTexture("levelSelectedFrame");

	Sprite s1{ levelSelectionFrameTexture, {0, 0}, {64,88}};
	Sprite s2{ levelSelectionFrameTexture, {1, 0}, {64,88}};
	Sprite s3{ levelSelectionFrameTexture, {2, 0}, {64,88}};
	AnimationData animDefault{ "Active",{s1,s2,s3} };
	anim->AddAnimation(animDefault);
	anim->SetSpeed(0.1);
	anim->SelectAnimation("Active", true);
	markSelectionPosition = { 3,5.5f };
	return true;
}

update_status ModuleLevelSelection::Update()
{
	anim->Update();
	if(IsKeyDown(toLeftButton))
	{
		markSelectionPosition.x = 3;
	}
	else if(IsKeyDown(toRightButton))
	{
		markSelectionPosition.x = 21;
	}
	DrawTexturePro(*levelSelectionTexture, { 0,(float)selectedLanguage * 144,160,144 }, {0, 0, SCREEN_SIZE*SCREEN_WIDTH, SCREEN_SIZE*SCREEN_HEIGHT}, { 0, 0 },0, WHITE);
	anim->Animate(markSelectionPosition.x * SCREEN_SIZE, markSelectionPosition.y * SCREEN_SIZE, true);
	return UPDATE_CONTINUE;
}

bool ModuleLevelSelection::CleanUp()
{
	delete anim;
	return true;
}
