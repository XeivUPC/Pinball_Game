#include "Flipper.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "AnimationSystem.h"
#include "ModuleUserPreferences.h"

Flipper::Flipper(ModuleGame* gameAt, float power, float maxAngle, float minAngle, b2Vec2 position, b2Vec2 drawingPosition, bool flipped)
{
	this->gameAt = gameAt;

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
	flipper_animator->SetSpeed(0.02);
	flipper_animator->SelectAnimation("Paddle_Idle", true);

	this->flipped = flipped;
	this->drawingPosition = drawingPosition;
	b2MassData paddleMassData;
	 body = Box2DFactory::GetInstance().CreateBox(gameAt->App->physics->world, position, 5.2f, 1);
	 body->GetFixtureList()[0].SetDensity(100000000);
	 body->SetType(b2_dynamicBody);

	 anchorBody = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, position, 0.2);
	anchorBody->SetType(b2_staticBody);

	b2RevoluteJointDef jointDef;
	b2Vec2 offset = body->GetWorldCenter();

	jointDef.bodyA = body;
	jointDef.bodyB = anchorBody;

	jointDef.localAnchorA.Set(flipped ? 2.55f : -2.55f ,0);
	jointDef.localAnchorB.Set(0.0f, 0.0f);

	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = minAngle;  //-0.15f * b2_pi; // -90 degrees
	jointDef.upperAngle = maxAngle; //0.15 * b2_pi; // 45 degrees

	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = power;
	jointDef.motorSpeed = 0.0f;

	flipperJoint = (b2RevoluteJoint*)gameAt->App->physics->world->CreateJoint(&jointDef);
	flipperJoint->EnableMotor(true);
}

Flipper::~Flipper()
{

	gameAt->App->physics->world->DestroyBody(body);
	gameAt->App->physics->world->DestroyBody(anchorBody);
}

update_status Flipper::Update()
{

	if (flipped) {

		if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		/// Trigger Left Paddle
			flipper_animator->SelectAnimation("Paddle_Click", false);
			flipperJoint->SetMotorSpeed(-40000.0f);
		}else
		{
			flipper_animator->SelectAnimation("Paddle_Idle", true);
			flipperJoint->SetMotorSpeed(40000.0f);
		}
	}
	else {
		if (IsKeyDown(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
			/// Trigger Left Paddle
			flipper_animator->SelectAnimation("Paddle_Click", false);
			flipperJoint->SetMotorSpeed(40000.0f);
		}
		else
		{
			flipper_animator->SelectAnimation("Paddle_Idle", true);
			flipperJoint->SetMotorSpeed(-40000.0f);
		}

	}

	flipper_animator->Update();
	flipper_animator->Animate(drawingPosition.x, drawingPosition.y, flipped);
	return UPDATE_CONTINUE;
}
