#include "CircularBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include <random>

CircularBumper::CircularBumper(ModuleGame* gameAt, b2Vec2 position, float radius, float restitution, int variant) : Bumper (gameAt, position, restitution)
{
	gameAt->AddObject(this);

	this->variant = variant;
	
	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x + radius, position.y + radius }, radius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetDensity(1);
	body->GetFixtureList()[0].SetRestitution(restitution);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);

	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/circular_bumpers.png", "circular_bumpers");
	texture = gameAt->App->texture->GetTexture("circular_bumpers");

	animator = new Animator(gameAt->App);

	AnimationData circularIdle = AnimationData("Circular_Idle");
	circularIdle.AddSprite(Sprite{ texture,{0, (float)variant}, {18,18} });

	AnimationData circularHit = AnimationData("Circular_Hit");
	circularHit.AddSprite(Sprite{ texture,{1, (float)variant}, {18,18} });


	AnimationData circularShake = AnimationData("Circular_Shake");
	circularShake.AddSprite(Sprite{ texture,{2, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{3, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{4, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{5, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{6, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{3, (float)variant}, {18,18} });
	circularShake.AddSprite(Sprite{ texture,{2, (float)variant}, {18,18} });

	animator->AddAnimation(circularIdle);
	animator->AddAnimation(circularHit);
	animator->AddAnimation(circularShake);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Circular_Idle", true);

	SetShakeTime();
}

CircularBumper::~CircularBumper()
{
}

update_status CircularBumper::Update()
{
	if (animator->HasAnimationFinished()) {
		if (gettingHit) {
			gettingHit = false;
		}
		animator->SelectAnimation("Circular_Idle", true);
	}
	Bumper::Update();


	if (!gettingHit && shake_time <= shake_timer.ReadSec()) {
		animator->SelectAnimation("Circular_Shake", false);
		shake_timer.Start();
	}

	if (animator->GetCurrentAnimationName() == "Circular_Shake") {
		animator->SetSpeed(0.05f);
	}
	else {
		animator->SetSpeed(0.25f);
	}

	animator->Update();
	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 9), (int)(body->GetPosition().y * SCREEN_SIZE - 9), true);
	return UPDATE_CONTINUE;
}

bool CircularBumper::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void CircularBumper::OnHit()
{
	Bumper::OnHit();
	animator->SelectAnimation("Circular_Idle", true);
	animator->SelectAnimation("Circular_Hit", false);

	gettingHit = true;
}

void CircularBumper::SetShakeTime()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(shake_time_min, shake_time_max);

	shake_time = distribution(gen);
}
