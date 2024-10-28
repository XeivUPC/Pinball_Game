#include "ModuleGame.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "GameUI.h"

#include "ModuleHighScore.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

	
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	map_texture = App->texture->GetTexture("map_redMap");

	App->texture->CreateTexture("Assets/map_paddle.png", "map_paddle");
	paddle_texture = App->texture->GetTexture("map_paddle");

	paddleLeft_animator = new Animator(App);
	paddleRight_animator = new Animator(App);

	AnimationData paddleIdle = AnimationData("Paddle_Idle");
	paddleIdle.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });

	AnimationData paddleClick = AnimationData("Paddle_Click");
	paddleClick.AddSprite(Sprite{ paddle_texture,{0, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{1, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });

	paddleLeft_animator->AddAnimation(paddleIdle);
	paddleLeft_animator->AddAnimation(paddleClick);
	paddleLeft_animator->SetSpeed(0.07);
	paddleLeft_animator->SelectAnimation("Paddle_Idle", true);

	paddleRight_animator->AddAnimation(paddleIdle);
	paddleRight_animator->AddAnimation(paddleClick);
	paddleRight_animator->SetSpeed(0.07);
	paddleRight_animator->SelectAnimation("Paddle_Idle", true);


	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	return true;
}

update_status ModuleGame::Update()
{
	RepositionCamera();
	MovePaddles();

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		StartFadeIn(App->scene_highScore, WHITE, 0.3f);
	}

	paddleRight_animator->Update();
	paddleLeft_animator->Update();


	Rectangle rectBackground = { 0,0,191,278 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);

	paddleLeft_animator->Animate(51,245,false);
	paddleRight_animator->Animate(160-75, 245,true);

	UI->Render();

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}

void ModuleGame::RepositionCamera()
{
	

	//if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
	//	App->renderer->camera.offset.x = 0;
	//}

	//if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
	//	App->renderer->camera.offset.x = -31 * SCREEN_SIZE;
	//}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
		App->renderer->camera.offset.y = 0;
	}
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
		App->renderer->camera.offset.y = -135 * SCREEN_SIZE;
	}
}

void ModuleGame::MovePaddles()
{
	if (paddleLeft_animator->HasAnimationFinished()) {
		paddleLeft_animator->SelectAnimation("Paddle_Idle", true);
	}

	if (paddleRight_animator->HasAnimationFinished()) {
		paddleRight_animator->SelectAnimation("Paddle_Idle", true);
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		/// Trigger Left Paddle
		paddleLeft_animator->SelectAnimation("Paddle_Click", false);
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		/// Trigger Right Paddle
		paddleRight_animator->SelectAnimation("Paddle_Click", false);
	}
}


bool ModuleGame::CleanUp()
{
	App->renderer->camera.offset = { 0,0 };
	return true;
}
