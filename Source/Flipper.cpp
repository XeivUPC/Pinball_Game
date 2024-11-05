#include "Flipper.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "AnimationSystem.h"


Flipper::Flipper(ModuleGame* gameAt, float power, b2Vec2 position, b2Vec2 angleRange, ModuleUserPreferences::VirtualButton activationKey, bool flipped) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->power = power;
	this->flipped = flipped;
	this->activationKey = activationKey;

	////

	gameAt->App->texture->CreateTexture("Assets/map_paddle.png", "map_paddle");
	flipper_texture = gameAt->App->texture->GetTexture("map_paddle");

	flipper_animator = new Animator(gameAt->App);

	AnimationData paddleIdle = AnimationData("Paddle_Idle");
	paddleIdle.AddSprite(Sprite{ flipper_texture,{2, 0}, {24,24} });

	AnimationData paddleClick = AnimationData("Paddle_Click");
	paddleClick.AddSprite(Sprite{ flipper_texture,{2, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ flipper_texture,{1, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ flipper_texture,{0, 0}, {24,24} });

	flipper_animator->AddAnimation(paddleIdle);
	flipper_animator->AddAnimation(paddleClick);
	flipper_animator->SetSpeed(0.02f);
	flipper_animator->SelectAnimation("Paddle_Idle", true);

	////

	b2MassData paddleMassData;
	body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, position, 4.8f, 1);
	body->GetFixtureList()[0].SetDensity(10000);
	body->GetFixtureList()[0].SetRestitution(0);

	this->power *= body->GetFixtureList()[0].GetDensity();

	body->ResetMassData();
	body->SetType(b2_dynamicBody);

	anchorBody = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, position, 0.2f);
	anchorBody->SetType(b2_staticBody);

	b2RevoluteJointDef jointDef;
	b2Vec2 offset = body->GetWorldCenter();

	jointDef.bodyA = body;
	jointDef.bodyB = anchorBody;

	jointDef.localAnchorA.Set(flipped ? 2.4f : -2.4f, 0);
	jointDef.localAnchorB.Set(0.0f, 0.0f);

	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = angleRange.x;
	jointDef.upperAngle = angleRange.y;

	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = abs(this->power);
	jointDef.motorSpeed = 0.0f;

	flipperJoint = (b2RevoluteJoint*)gameAt->App->physics->world->CreateJoint(&jointDef);
	flipperJoint->EnableMotor(true);

	///

	drawingPosition = body->GetPosition();
	drawingPosition.x *= SCREEN_SIZE;
	drawingPosition.y *= SCREEN_SIZE;

	drawingPosition.x -= flipped ? 19 : 4;
	drawingPosition.y -= 12;
}

Flipper::~Flipper()
{
	
}

bool Flipper::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	gameAt->App->physics->world->DestroyBody(anchorBody);
	return true;
}

update_status Flipper::Update()
{

	if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(activationKey))) {
		flipper_animator->SelectAnimation("Paddle_Click", false);
		flipperJoint->SetMotorSpeed(-power);
	}
	else
	{
		flipperJoint->SetMotorSpeed(power);
		flipper_animator->SelectAnimation("Paddle_Idle", true);
	}

	flipper_animator->Update();
	flipper_animator->Animate((int)drawingPosition.x, (int)drawingPosition.y, flipped);
	return UPDATE_CONTINUE;
}
