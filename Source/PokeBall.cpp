#include "PokeBall.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"
#include <math.h>
 
PokeBall::PokeBall(ModuleGame* gameAt, b2Vec2 spawn, PokeballType type,float maxSpeed) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	this->maxSpeed = maxSpeed;
	this->spawn = spawn;
	

	gameAt->App->texture->CreateTexture("Assets/pokebal_defaultSize.png", "pokebal_defaultSize");
	pokeball_texture = gameAt->App->texture->GetTexture("pokebal_defaultSize");

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, spawn, 1.3f);
	body->GetFixtureList()[0].SetRestitution(0.5f);
	body->GetFixtureList()[0].SetFriction(0);
	body->GetFixtureList()[0].SetDensity(10);

	body->ResetMassData();

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

	AnimationData superballMove = AnimationData("Superball_Anim");
	superballMove.AddSprite(Sprite{ pokeball_texture,{0, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{1, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{2, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{3, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{4, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{5, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{6, 1}, {16,16} });
	superballMove.AddSprite(Sprite{ pokeball_texture,{7, 1}, {16,16} });

	AnimationData ultraballMove = AnimationData("Ultraball_Anim");
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{0, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{1, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{2, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{3, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{4, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{5, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{6, 2}, {16,16} });
	ultraballMove.AddSprite(Sprite{ pokeball_texture,{7, 2}, {16,16} });

	AnimationData masterballMove = AnimationData("Masterball_Anim");
	masterballMove.AddSprite(Sprite{ pokeball_texture,{0, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{1, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{2, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{3, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{4, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{5, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{6, 3}, {16,16} });
	masterballMove.AddSprite(Sprite{ pokeball_texture,{7, 3}, {16,16} });

	pokeball_animator->SetSpeed(0);
	pokeball_animator->AddAnimation(pokeballMove);
	pokeball_animator->AddAnimation(superballMove);
	pokeball_animator->AddAnimation(ultraballMove);
	pokeball_animator->AddAnimation(masterballMove);


	SetType(type);
}

PokeBall::~PokeBall()
{

}

update_status PokeBall::Update()
{
	if (IsKeyPressed(KEY_F2)) {
		godMode = !godMode;
	}

	if (type!= Pokeball && type!=MasterBall) {
		if (pokeballDowngradeTimer.ReadSec() > pokeballDowngradeTime) {
			SetType((PokeballType)((int)type - 1));
		}
	}
	else
		pokeballDowngradeTimer.Start();
	

	float xVel = body->GetLinearVelocity().x;
	float yVel = body->GetLinearVelocity().y;

	if (godMode) {
		body->SetGravityScale(0);

		float speed = 1000 * GetFrameTime();
		b2Vec2 direction = { 0,0 };
		
		if (IsKeyDown(KEY_UP)) {
			direction.y -= speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			direction.y += speed;
		}
		if (IsKeyDown(KEY_LEFT)) {
			direction.x -= speed;
		}
		if (IsKeyDown(KEY_RIGHT)) {
			direction.x += speed;
		}
		body->SetLinearVelocity(direction);
	}
	else {
		body->SetGravityScale(1);
		if (yVel < 0) {
			body->SetGravityScale(0.8f);
		}
	}
	

	float pokeballSpeed = sqrt(xVel * xVel + yVel * yVel);
	pokeballSpeed = (pokeballAnimMaxSpeed / pokeballSpeed) / 100;


	b2Vec2 velocity = body->GetLinearVelocity();
	if (velocity.Length() > maxSpeed) {
		velocity.Normalize();  
		body->SetLinearVelocity({ velocity.x * maxSpeed, velocity.y* maxSpeed });
	}

	if (xVel < 0)
		pokeball_animator->SetDirection(1);
	else
		pokeball_animator->SetDirection(-1);

	pokeball_animator->SetSpeed(pokeballSpeed);

	pokeball_animator->Update();
	pokeball_animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 8), (int)(body->GetPosition().y * SCREEN_SIZE - 8), true);
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

void PokeBall::SetVelocity(b2Vec2 velocity)
{
	body->SetLinearVelocity(velocity);
}

void PokeBall::SetType(PokeballType type)
{
	PokeballType lastType = this->type;

	float lastMultiplier = GetMultiplierByType(lastType);
	float newMultiplier = GetMultiplierByType(type);

	this->type = type;

	switch (type)
	{
	case PokeBall::Pokeball:
		gameAt->pointsCounter.AddMultiplier(newMultiplier);
		pokeball_animator->SelectAnimation("Pokeball_Anim", true);
		break;
	case PokeBall::SuperBall:
		gameAt->pointsCounter.EditMultiplier(lastMultiplier, newMultiplier);
		pokeball_animator->SelectAnimation("Superball_Anim", true);
		break;
	case PokeBall::Ultraball:
		gameAt->pointsCounter.EditMultiplier(lastMultiplier, newMultiplier);
		pokeball_animator->SelectAnimation("Ultraball_Anim", true);

		break;
	case PokeBall::MasterBall:
		gameAt->pointsCounter.EditMultiplier(lastMultiplier, newMultiplier);
		pokeball_animator->SelectAnimation("Masterball_Anim", true);
		break;
	default:
		gameAt->pointsCounter.AddMultiplier(newMultiplier);
		pokeball_animator->SelectAnimation("Pokeball_Anim", true);
		break;
	}
	pokeballDowngradeTimer.Start();
}

PokeBall::PokeballType PokeBall::GetType()
{
	return type;
}

b2Vec2 PokeBall::GetPosition()
{
	return body->GetPosition();
}

void PokeBall::Reset(bool saveBall)
{
	PokeballType lastType = this->type;
	

	SetPosition(spawn);
	SetVelocity({ 0,0 });

	if (saveBall)
		return;
	
	gameAt->pointsCounter.RemoveMultiplier(GetMultiplierByType(lastType));
	lives_pokeball--;
}

int PokeBall::GetLivesPokeball() const
{
	return lives_pokeball;
}

float PokeBall::GetMultiplierByType(PokeballType type)
{
	switch (type)
	{
	case PokeBall::Pokeball:
		return 1;
		break;
	case PokeBall::SuperBall:
		return 2;
		break;
	case PokeBall::Ultraball:
		return 3;
		break;
	case PokeBall::MasterBall:
		return 5;
		break;
	default:
		return 1;
		break;
	}
}

bool PokeBall::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}
