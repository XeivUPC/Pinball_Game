#include "PokeBall.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include "AnimationSystem.h"
#include <math.h>

PokeBall::PokeBall(ModuleGame* gameAt)
{
	this->gameAt = gameAt;


	gameAt->App->texture->CreateTexture("Assets/pokebal_defaultSize.png", "pokebal_defaultSize");
	pokeball_texture = gameAt->App->texture->GetTexture("pokebal_defaultSize");

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { 43,68 }, 1.3f);
	body->GetFixtureList()[0].SetRestitution(0.5f);
	body->GetFixtureList()[0].SetFriction(0);
	body->GetFixtureList()[0].SetDensity(100);

	body->SetBullet(true);


	pokeball_animator = new Animator(gameAt->App);
	AnimationData pokeballMove = AnimationData("Pokeball_Anim");
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{1, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{2, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{3, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{4, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{5, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{6, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{7, 0}, {16,16} });

	pokeball_animator->SetSpeed(0);
	pokeball_animator->AddAnimation(pokeballMove);
	pokeball_animator->SelectAnimation("Pokeball_Anim", true);
}

PokeBall::~PokeBall()
{
	gameAt->App->physics->world->DestroyBody(body);
}

update_status PokeBall::Update()
{
	float xVel = body->GetLinearVelocity().x;
	float yVel = body->GetLinearVelocity().y;

	float pokeballSpeed = sqrt(xVel * xVel + yVel * yVel);
	pokeballSpeed = (pokeballAnimMaxSpeed / pokeballSpeed) / 100;

	if (xVel < 0)
		pokeball_animator->SetDirection(1);
	else
		pokeball_animator->SetDirection(-1);

	pokeball_animator->SetSpeed(pokeballSpeed);

	pokeball_animator->Update();
	pokeball_animator->Animate(body->GetPosition().x * SCREEN_SIZE - 8, body->GetPosition().y * SCREEN_SIZE - 8, true);
	return UPDATE_CONTINUE;
}

void PokeBall::ApplyForce(b2Vec2 force)
{
	body->ApplyLinearImpulseToCenter(force, true);
}

void PokeBall::SetPosition(b2Vec2 position)
{
	body->SetTransform(position,0);
}

b2Vec2 PokeBall::GetPosition()
{
	return body->GetPosition();
}