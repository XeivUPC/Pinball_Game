#include "OverworldPokemonBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "CentralScreen.h"
#include "ModuleAudio.h"

OverworldPokemonBumper::OverworldPokemonBumper(ModuleGame* gameAt, b2Vec2 position, float radius, float restitution, int pokemonId) : Bumper(gameAt, position, restitution)
{
	gameAt->AddObject(this);

	b2FixtureUserData fixtureData;
	fixtureData.pointer = (uintptr_t)(&sensor);

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { position.x + radius, position.y + radius }, radius, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetDensity(1);
	body->GetFixtureList()[0].SetRestitution(restitution);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);
	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/pokemons_capture_sprites.png", "Assets/pokemons_capture_sprites.png");
	pokemonTexture = gameAt->App->texture->GetTexture("Assets/pokemons_capture_sprites.png");

	gameAt->App->texture->CreateTexture("Assets/capture_sprites.png", "Assets/capture_sprites.png");
	captureTexture = gameAt->App->texture->GetTexture("Assets/capture_sprites.png");

	//bumperAudioId = gameAt->App->audio->LoadFx("");

	animator = new Animator(gameAt->App);

	AnimationData pokemonIdle = AnimationData("PokemonIdle");
	AnimationData pokemonHit = AnimationData("PokemonHit");
	AnimationData caughtSmoke = AnimationData("CaughtSmoke");
	AnimationData pokeballShake = AnimationData("PokeballShake");

	animator->AddAnimation(pokemonIdle);
	animator->AddAnimation(pokemonHit);
	animator->AddAnimation(caughtSmoke);
	animator->AddAnimation(pokeballShake);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("PokemonIdle", true);
}

OverworldPokemonBumper::~OverworldPokemonBumper()
{
}

update_status OverworldPokemonBumper::Update()
{
	Bumper::Update();
	return UPDATE_CONTINUE;
}

bool OverworldPokemonBumper::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);
	return true;
}

void OverworldPokemonBumper::OnHit()
{
	Bumper::OnHit();
}
