#include "TornadoThrower.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2DFactory.h"
#include "Tornado.h"


TornadoThrower::TornadoThrower(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	this->position = position;

	radius = 1;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, this->position, radius, fixtureData);
	body->SetType(b2_staticBody);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);
	body->GetFixtureList()[0].SetSensor(true);

	gameAt->App->texture->CreateTexture("Assets/tornado_pidgey.png", "tornado_pidgey");
	texture = gameAt->App->texture->GetTexture("tornado_pidgey");

	animator = new Animator(gameAt->App);

	AnimationData idle = AnimationData("Idle");
	idle.AddSprite(Sprite{ texture,{0, 0}, {32,32} });
	idle.AddSprite(Sprite{ texture,{1, 0}, {32,32} });

	animator->AddAnimation(idle);
	animator->SetSpeed(0.15f);
	animator->SelectAnimation("Idle", true);

	destroyTimer.Start();
}

TornadoThrower::~TornadoThrower()
{

}

update_status TornadoThrower::Update()
{
	if (throwSpeed < throwTimer.ReadSec()) {
		throwTimer.Start();
		
		Tornado* tornado = new Tornado(gameAt, body->GetPosition(), {1,-0.5},5);
		tornado = new Tornado(gameAt, body->GetPosition(), {-1,-0.5},5);
		//// Do Throw
	}

	if (position.y <= 216 / SCREEN_SIZE) {
		position.y = position.y + 0.5 * GetFrameTime();
		body->SetTransform(position, 0);
	}
	if (destroyTimer.ReadSec() >= destroyTime) {
		gameAt->RemoveObject(this);
	}
	else {
		animator->Update();
		animator->Animate((int)((position.x) * SCREEN_SIZE)-16, (int)((position.y) * SCREEN_SIZE)-16, true);
	}
	return UPDATE_CONTINUE;
}

bool TornadoThrower::CleanUp()
{	
	gameAt->App->physics->world->DestroyBody(body);
	
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	return true;
}

