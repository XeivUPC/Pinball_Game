#include "OverworldPokemonBumper.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "CentralScreen.h"
#include "ModuleAudio.h"

OverworldPokemonBumper::OverworldPokemonBumper(ModuleGame* gameAt, b2Vec2 position, float radius, float restitution) : Bumper(gameAt, position, restitution)
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
	texture = gameAt->App->texture->GetTexture("Assets/pokemons_capture_sprites.png");

	//bumperAudioId = gameAt->App->audio->LoadFx("");

	animator = new Animator(gameAt->App);

	AnimationData pokemonIdle = AnimationData("PokemonIdle");
	AnimationData pokemonHit = AnimationData("PokemonHit");
	AnimationData caughtSmoke = AnimationData("CaughtSmoke");
	AnimationData pokeballShake = AnimationData("PokeballShake");
}
