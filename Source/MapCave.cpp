#include "MapCave.h"
#include "Box2DFactory.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"
#include "CentralScreen.h"
#include "ModuleAudio.h"
#include "PokeBall.h"
#include "BonusFinalBall.h"
#include "BlackHoleEffector.h"

MapCave::MapCave(ModuleGame* gameAt, b2Vec2 position, b2Vec2 entryPosition, float entryRadius) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->position = position;
	this->entryPosition = entryPosition;
	this->entryRadius = entryRadius;
	
	this->entryPosition = { entryPosition.x + entryRadius, entryPosition.y + entryRadius };


	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, this->entryPosition , entryRadius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetSensor(true);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);


	gameAt->App->texture->CreateTexture("Assets/map_cave.png", "map_cave");
	texture = gameAt->App->texture->GetTexture("map_cave");

	animator = new Animator(gameAt->App);

	AnimationData closedAnim = AnimationData("Closed");
	closedAnim.AddSprite(Sprite{ texture,{0, 0}, {33,33} });

	AnimationData openedAnim = AnimationData("Opened");
	openedAnim.AddSprite(Sprite{ texture,{1, 0}, {33,33} });
	openedAnim.AddSprite(Sprite{ texture,{2, 0}, {33,33} });
	openedAnim.AddSprite(Sprite{ texture,{3, 0}, {33,33} });
	openedAnim.AddSprite(Sprite{ texture,{4, 0}, {33,33} });

	AnimationData openedNoEffectAnim = AnimationData("Opened_NoEffect");
	openedNoEffectAnim.AddSprite(Sprite{ texture,{4, 0}, {33,33} });

	animator->AddAnimation(closedAnim);
	animator->AddAnimation(openedAnim);
	animator->AddAnimation(openedNoEffectAnim);
	animator->SetSpeed(0.1f);
	animator->SelectAnimation("Closed", true);

	audioVoidAbsorbId = gameAt->App->audio->LoadFx("Assets/SFX/Game_VoidAbsorb.ogg");
	audioVoidEnterId = gameAt->App->audio->LoadFx("Assets/SFX/Game_VoidEnter.ogg");
	blackHoleEffector = new BlackHoleEffector(gameAt, this->entryPosition, 4.f);
}

MapCave::~MapCave()
{
}

update_status MapCave::Update()
{
	animator->Update();


	bool hasBeenTriggered = sensor.OnTriggerEnter();
	if (isOpen) {

		if (isBallIn && freeBallTime < freeBallTimer.ReadSec()) {
			isBallIn = false;
			CloseCave();
		}
		if (hasBeenTriggered) {
			gameAt->App->audio->PlayFx(audioVoidEnterId);
			OnHit();		
		}	
	}

	blackHoleEffector->Update();

	animator->Animate((int)(position.x * SCREEN_SIZE ), (int)(position.y * SCREEN_SIZE), true);
	return UPDATE_CONTINUE;
}

bool MapCave::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
	return true;
}

void MapCave::OpenCave()
{
	isOpen = true;
	animator->SelectAnimation("Opened", true);
	blackHoleEffector->SetIfEnable(true);
}

void MapCave::CloseCave()
{
	isBallIn = false;
	isOpen = false;
	animator->SelectAnimation("Closed", true);
	blackHoleEffector->SetIfEnable(false);
}

void MapCave::FreeBall()
{
	gameAt->GetPokeball()->SetIfBlockMovement(false);
	gameAt->GetPokeball()->SetIfBlockRender(false);
	gameAt->GetPokeball()->SetVelocity({ 5,-1 });
	freeBallTimer.Start();
	animator->SelectAnimation("Opened_NoEffect", true);
	isOpen = true;
}

bool MapCave::IsCaveOpen()
{
	return isOpen;
}

void MapCave::OnHit()
{
	///// DoActions
	if (gameAt->screen->GetActualProgramIdentifier() == "BonusStart") {
		gameAt->screen->CallScreenEvent(0);
		CloseCave();
		gameAt->GetPokeball()->SetIfBlockMovement(true);
		gameAt->GetPokeball()->SetIfBlockRender(true);
		gameAt->GetPokeball()->SetPosition(entryPosition);
		isBallIn = true;
		gameAt->finalBallUI->AddInBonus(8);
	}
}
