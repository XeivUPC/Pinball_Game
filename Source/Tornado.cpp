#include "Tornado.h"
#include "ModuleTexture.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "BlackHoleEffector.h"

Tornado::Tornado(ModuleGame* gameAt, b2Vec2 position, b2Vec2 direction, float speed) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	this->position = position;
	this->direction = direction;
	this->speed = speed;

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, this->position, 0, fixtureData);
	body->SetType(b2_kinematicBody);
	body->GetFixtureList()[0].SetSensor(true);

	body->SetLinearVelocity({ direction.x * speed, direction.y * speed });

	gameAt->App->texture->CreateTexture("Assets/tornado.png", "tornado");
	texture = gameAt->App->texture->GetTexture("tornado");

	animator = new Animator(gameAt->App);

	AnimationData idle = AnimationData("Idle");
	idle.AddSprite(Sprite{ texture,{0, 0}, {24,32} });
	idle.AddSprite(Sprite{ texture,{2, 0}, {24,32} });
	idle.AddSprite(Sprite{ texture,{3, 0}, {24,32} });
	idle.AddSprite(Sprite{ texture,{0, 0}, {24,32} });

	animator->AddAnimation(idle);
	animator->SetSpeed(0.15f);
	animator->SelectAnimation("Idle", true);


	blackHoleEffector = new BlackHoleEffector(gameAt, position, 4.f,50.f);
	blackHoleEffector->SetIfEnable(true);
	lifeTimer.Start();

}

Tornado::~Tornado()
{
}

update_status Tornado::Update()
{
	

	if (lifeTime < lifeTimer.ReadSec()) {
		gameAt->RemoveObject(blackHoleEffector);
		gameAt->RemoveObject(this);
		
	}
	else {
		blackHoleEffector->Update();
		blackHoleEffector->SetPosition(body->GetPosition());
		animator->Update();
		animator->Animate((int)((body->GetPosition().x) * SCREEN_SIZE) - 12, (int)((body->GetPosition().y) * SCREEN_SIZE) - 16, true);
	}
	return UPDATE_CONTINUE;
}

bool Tornado::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	return true;
}
