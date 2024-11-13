#include "MapEnergyRotator.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"
#include "ModuleTexture.h"

MapEnergyRotator::MapEnergyRotator(ModuleGame* gameAt, b2Vec2 position, MapEnergyBattery* battery, float width, float height, int variant) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->battery = battery;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, position, width, height, fixtureData);
	body->GetFixtureList()[0].SetSensor(true);
	body->SetType(b2_staticBody);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);
	
	gameAt->App->texture->CreateTexture("Assets/map_gyroEnergy.png", "map_gyroEnergy");
	texture = gameAt->App->texture->GetTexture("map_gyroEnergy");

	animator = new Animator(gameAt->App);
	AnimationData rotate = AnimationData("Rotator_Rotate");
	rotate.AddSprite(Sprite{ texture,{0, (float)variant}, {16,16} });
	rotate.AddSprite(Sprite{ texture,{1, (float)variant}, {16,16} });
	rotate.AddSprite(Sprite{ texture,{2, (float)variant}, {16,16} });
	rotate.AddSprite(Sprite{ texture,{3, (float)variant}, {16,16} });
	rotate.AddSprite(Sprite{ texture,{4, (float)variant}, {16,16} });
	rotate.AddSprite(Sprite{ texture,{5, (float)variant}, {16,16} });

	animator->SetSpeed(0);
	animator->AddAnimation(rotate);
	animator->SelectAnimation("Rotator_Rotate", true);

}

MapEnergyRotator::~MapEnergyRotator()
{
}

update_status MapEnergyRotator::Update()
{
	b2Body* ball = sensor.OnTriggerEnterGet();
	if (ball!=nullptr) {
		float pokeballSpeed = 0;
		float xVel = ball->GetLinearVelocity().x;
		float yVel = ball->GetLinearVelocity().y;

		pokeballSpeed = sqrt(xVel * xVel + yVel * yVel);
		velocity = pokeballSpeed;
	}


	

	float speed = b2_maxFloat;

	if (velocity != 0) {

		velocity -= speedReduction * GetFrameTime();
		if (abs(velocity) < 0.5f)
			velocity = 0;

		speed = (maxRotationSpeed / velocity) / 100;

		if (velocity < 0)
			animator->SetDirection(1);
		else
			animator->SetDirection(-1);

		if (pointsTime <= pointsTimer.ReadSec()) {
			pointsTimer.Start();
			gameAt->pointsCounter.Add(100);
		}
		battery->AddEnergy(velocity*GetFrameTime()/2);
	}
	
	animator->SetSpeed(speed);

	animator->Update();

	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 8), (int)(body->GetPosition().y * SCREEN_SIZE - 8), true);
	
	return UPDATE_CONTINUE;
}

bool MapEnergyRotator::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}
