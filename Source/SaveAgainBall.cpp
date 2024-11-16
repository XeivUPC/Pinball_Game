#include "SaveAgainBall.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"
#include "Box2DFactory.h"
#include "Pokeball.h"
#include "CentralScreen.h"

SaveAgainBall::SaveAgainBall(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	selectedLanguage = gameAt->App->userPreferences->GetLanguage()-1;
	if (selectedLanguage < 0)
	{
		selectedLanguage = 0;
	}

	gameAt->App->texture->CreateTexture("Assets/map_saveAgainBall.png", "map_saveAgainBall");
	map_saveAgainBall = gameAt->App->texture->GetTexture("map_saveAgainBall");

	map_saveBall_animator = new Animator(gameAt->App);
	map_againBall_animator = new Animator(gameAt->App);
	
	//Animation Save
	AnimationData mapSaveBallActiveAnim = AnimationData("MapSaveBallActiveAnim");
	mapSaveBallActiveAnim.AddSprite(Sprite{ map_saveAgainBall,{1, 1.f * selectedLanguage }, {32,8} });

	AnimationData mapSaveBallBackAnim = AnimationData("MapSaveBallBackAnim");
	mapSaveBallBackAnim.AddSprite(Sprite{ map_saveAgainBall,{0, 1.f * selectedLanguage }, {32,8} });

	AnimationData mapSaveBallBlinkAnim = AnimationData("MapSaveBallBlinkAnim");
	mapSaveBallBlinkAnim.AddSprite(Sprite{ map_saveAgainBall,{0, 1.f * selectedLanguage }, {32,8} });
	mapSaveBallBlinkAnim.AddSprite(Sprite{ map_saveAgainBall,{1, 1.f * selectedLanguage }, {32,8} });
	

	//Animation Again
	AnimationData mapAgainBallActiveAnim = AnimationData("MapAgainBallActiveAnim");
	mapAgainBallActiveAnim.AddSprite(Sprite{ map_saveAgainBall,{1, 1.f * selectedLanguage + 5}, {32,8} });

	AnimationData mapAgainBallBackAnim = AnimationData("MapAgainBallBackAnim");
	mapAgainBallBackAnim.AddSprite(Sprite{ map_saveAgainBall,{0, 1.f * selectedLanguage + 5}, {32,8} });


	map_saveBall_animator->AddAnimation(mapSaveBallActiveAnim);
	map_saveBall_animator->AddAnimation(mapSaveBallBackAnim);
	map_saveBall_animator->AddAnimation(mapSaveBallBlinkAnim);

	map_againBall_animator->AddAnimation(mapAgainBallActiveAnim);
	map_againBall_animator->AddAnimation(mapAgainBallBackAnim);

	map_saveBall_animator->SetSpeed(0.5f);
	map_saveBall_animator->SelectAnimation("MapSaveBallBackAnim", true);

	map_againBall_animator->SetSpeed(0.5f);
	map_againBall_animator->SelectAnimation("MapAgainBallBackAnim", true);

	this->position = position;

	ballSaverTimer.Start();
}

SaveAgainBall::~SaveAgainBall()
{
}

void SaveAgainBall::SetBallSaverTimer(float time)
{
	ballSaverTime = time;
	numBallsSaved = 0;
	ballSaverTimer.Start();
	map_saveBall_animator->SetIfCanDraw(true);
}

update_status SaveAgainBall::Update()
{
	
	//Draw Front
	if (ballSaverTimer.ReadSec() < ballSaverTime + numBallsSaved) {
		gameAt->SetSaveBall(true);

		if (ballSaverTimer.ReadSec() >ballSaverTime + numBallsSaved - 5) {
			map_saveBall_animator->SelectAnimation("MapSaveBallBlinkAnim", true);
			map_saveBall_animator->SetSpeed(0.1f);
		}
		else if (ballSaverTimer.ReadSec() > ballSaverTime + numBallsSaved - 10) {
			map_saveBall_animator->SelectAnimation("MapSaveBallBlinkAnim", true);
			map_saveBall_animator->SetSpeed(0.3f);
		}
		else {
			map_saveBall_animator->SelectAnimation("MapSaveBallActiveAnim", true);
		}
	}
	else
	{
		map_saveBall_animator->SetIfCanDraw(true);
		gameAt->SetSaveBall(false);
		map_saveBall_animator->SelectAnimation("MapSaveBallBackAnim", true);
	}

	map_saveBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);





	if (gameAt->HasExtraBall())
	{
		map_againBall_animator->SelectAnimation("MapAgainBallActiveAnim", true);
	}
	else {
		map_againBall_animator->SelectAnimation("MapAgainBallBackAnim", true);
	}

	map_againBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)((position.y + 2) * SCREEN_SIZE), false);


	map_saveBall_animator->Update();
	map_againBall_animator->Update();

	return UPDATE_CONTINUE;
}

bool SaveAgainBall::CleanUp()
{
	if (map_saveBall_animator != nullptr) {
		delete map_saveBall_animator;
		map_saveBall_animator = nullptr;
	}

	if (map_againBall_animator != nullptr) {
		delete map_againBall_animator;
		map_againBall_animator = nullptr;
	}

	LOG("Unloading SaveAgainBall");
	return true;
}
