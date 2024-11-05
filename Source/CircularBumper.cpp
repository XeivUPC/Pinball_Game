#include "CircularBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

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
	circularIdle.AddSprite(Sprite{ texture,{0, (float)variant}, {16,16} });

	AnimationData circularHit = AnimationData("Circular_Hit");
	circularHit.AddSprite(Sprite{ texture,{1, (float)variant}, {16,16} });

	animator->AddAnimation(circularIdle);
	animator->AddAnimation(circularHit);
	animator->SetSpeed(0.5f);
	animator->SelectAnimation("Circular_Idle", true);

}

CircularBumper::~CircularBumper()
{
}

update_status CircularBumper::Update()
{
	Bumper::Update();
	if (animator->HasAnimationFinished()) {
		animator->SelectAnimation("Circular_Idle", true);
	}

	animator->Update();
	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 8), (int)(body->GetPosition().y * SCREEN_SIZE - 8), true);
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

}
