#include "MapCave.h"
#include "Box2DFactory.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "CentralScreen.h"
#include "ModuleAudio.h"

MapCave::MapCave(ModuleGame* gameAt, b2Vec2 position, b2Vec2 entryPosition, float entryRadius) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->position = position;
	this->entryPosition = entryPosition;
	this->entryRadius = entryRadius;



	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { entryPosition.x + entryRadius, entryPosition.y + entryRadius }, entryRadius, fixtureData);
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
}

MapCave::~MapCave()
{
}

update_status MapCave::Update()
{
	animator->Update();

	if (isOpen) {
		if (sensor.OnTriggerEnter()) {
			OnHit();
		}
	}

	animator->Animate((int)(position.x * SCREEN_SIZE ), (int)(position.y * SCREEN_SIZE), true);
	return UPDATE_CONTINUE;
}

bool MapCave::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

void MapCave::OpenCave()
{
	isOpen = true;
	animator->SelectAnimation("Opened", true);
}

void MapCave::CloseCave()
{
	isOpen = false;
	animator->SelectAnimation("Closed", true);
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
	}
}
