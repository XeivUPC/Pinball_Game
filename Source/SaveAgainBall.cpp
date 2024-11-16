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

	selectedLanguage = gameAt->App->userPreferences->GetLanguage();
	if (selectedLanguage == 0)
	{
		selectedLanguage = 1;
	}

	gameAt->App->texture->CreateTexture("Assets/map_saveAgainBall.png", "map_saveAgainBall");
	map_saveAgainBall = gameAt->App->texture->GetTexture("map_saveAgainBall");

	map_saveAgainBall_animator = new Animator(gameAt->App);
	
	//Animation Save
	AnimationData mapSaveBallActiveAnim = AnimationData("MapSaveBallActiveAnim");
	mapSaveBallActiveAnim.AddSprite(Sprite{ map_saveAgainBall,{1, 1.f * selectedLanguage - 1}, {32,8} });

	AnimationData mapSaveBallOffAnim = AnimationData("MapSaveBallOffAnim");
	mapSaveBallOffAnim.AddSprite(Sprite{ map_saveAgainBall,{2, 1.f * selectedLanguage - 1}, {32,8} });

	AnimationData mapSaveBallBackAnim = AnimationData("MapSaveBallBackAnim");
	mapSaveBallBackAnim.AddSprite(Sprite{ map_saveAgainBall,{0, 1.f * selectedLanguage - 1}, {32,8} });
	
	//Animation Again
	AnimationData mapAgainBallActiveAnim = AnimationData("MapAgainBallActiveAnim");
	mapAgainBallActiveAnim.AddSprite(Sprite{ map_saveAgainBall,{1, 1.f * selectedLanguage + 5 - 1}, {32,8} });

	AnimationData mapAgainBallOffAnim = AnimationData("MapAgainBallOffAnim");
	mapAgainBallOffAnim.AddSprite(Sprite{ map_saveAgainBall,{2, 1.f * selectedLanguage + 5 - 1}, {32,8} });

	AnimationData mapAgainBallBackAnim = AnimationData("MapAgainBallBackAnim");
	mapAgainBallBackAnim.AddSprite(Sprite{ map_saveAgainBall,{0, 1.f * selectedLanguage + 5 - 1}, {32,8} });


	map_saveAgainBall_animator->AddAnimation(mapSaveBallActiveAnim);
	map_saveAgainBall_animator->AddAnimation(mapSaveBallOffAnim);
	map_saveAgainBall_animator->AddAnimation(mapSaveBallBackAnim);

	map_saveAgainBall_animator->AddAnimation(mapAgainBallActiveAnim);
	map_saveAgainBall_animator->AddAnimation(mapAgainBallOffAnim);
	map_saveAgainBall_animator->AddAnimation(mapAgainBallBackAnim);

	map_saveAgainBall_animator->SetSpeed(0.5f);
	map_saveAgainBall_animator->SelectAnimation("MapSaveBallActiveAnim", true);

	this->position = position;

	BallSaverTimer.Start();
}

SaveAgainBall::~SaveAgainBall()
{
}

void SaveAgainBall::SetBallSaverTimer(float time)
{
	BallSaverTime = time;
}

update_status SaveAgainBall::Update()
{
	//Draw Background
	map_saveAgainBall_animator->SelectAnimation("MapSaveBallBackAnim", true);
	map_saveAgainBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);

	map_saveAgainBall_animator->SelectAnimation("MapAgainBallBackAnim", true);
	map_saveAgainBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)((position.y + 2) * SCREEN_SIZE), false);

	//Draw Front
	if (BallSaverTimer.ReadSec() < BallSaverTime + numBallsSaved) {
		map_saveAgainBall_animator->SelectAnimation("MapSaveBallActiveAnim",true);
		if (BallSaverTimer.ReadSec() > BallSaverTime + numBallsSaved - 5) {
			map_saveAgainBall_animator->SelectAnimation("MapSaveBallActiveAnim", true);
			if (BallSaverBlinkTimer.ReadSec() > BallSaverBlinkTime)
			{
				BallSaverBlinkTime = 0.1;
				map_saveAgainBall_animator->SetIfCanDraw(!map_saveAgainBall_animator->CanDraw());
				BallSaverBlinkTimer.Start();
			}
		}
		else if (BallSaverTimer.ReadSec() > BallSaverTime + numBallsSaved - 10) {
			map_saveAgainBall_animator->SelectAnimation("MapSaveBallActiveAnim", true);
			if (BallSaverBlinkTimer.ReadSec() > BallSaverBlinkTime)
			{
				map_saveAgainBall_animator->SetIfCanDraw(!map_saveAgainBall_animator->CanDraw());
				BallSaverBlinkTimer.Start();
			}
		}
	}
	else
	{
		map_saveAgainBall_animator->SelectAnimation("MapSaveBallOffAnim", true);
	}

	map_saveAgainBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);

	if (again)
	{
		map_saveAgainBall_animator->SelectAnimation("MapAgainBallActiveAnim", true);
		map_saveAgainBall_animator->Animate((int)(position.x * SCREEN_SIZE), (int)((position.y + 2) * SCREEN_SIZE), false);
	}

	map_saveAgainBall_animator->Update();

	return UPDATE_CONTINUE;
}

bool SaveAgainBall::CleanUp()
{
	if (map_saveAgainBall_animator != nullptr) {
		delete map_saveAgainBall_animator;
		map_saveAgainBall_animator = nullptr;
	}

	LOG("Unloading SaveAgainBall");
	return true;
}
