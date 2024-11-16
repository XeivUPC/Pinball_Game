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

	body = Box2DFactory::GetInstance().CreateCircle(gameAt->App->physics->world, { (position.x + radius-8)/SCREEN_SIZE, (position.y + radius-8)/SCREEN_SIZE }, radius/SCREEN_SIZE, fixtureData);
	body->SetType(b2_staticBody);
	body->GetFixtureList()[0].SetDensity(1);
	body->GetFixtureList()[0].SetRestitution(restitution);

	sensor.SetBodyToTrack(&body->GetFixtureList()[0]);
	sensor.AcceptOnlyTriggers(false);

	gameAt->App->texture->CreateTexture("Assets/pokemons_capture_sprites.png", "Assets/pokemons_capture_sprites.png");
	pokemonTexture = gameAt->App->texture->GetTexture("Assets/pokemons_capture_sprites.png");

	//bumperAudioId = gameAt->App->audio->LoadFx("");

	animator = new Animator(gameAt->App);

	AnimationData pokemonIdle = AnimationData("PokemonIdle");
	pokemonIdle.AddSprite(Sprite{ pokemonTexture,{(float)(((pokemonId-1)/20)*3),(float)((pokemonId - 1) % 20)}, {32,32}});
	pokemonIdle.AddSprite(Sprite{ pokemonTexture,{(float)(((pokemonId-1)/20)*3+1),(float)((pokemonId - 1) % 20)}, {32,32}});
	AnimationData pokemonHit = AnimationData("PokemonHit");
	pokemonHit.AddSprite(Sprite{ pokemonTexture,{(float)(((pokemonId - 1) / 20) * 3 + 2),(float)((pokemonId - 1) % 20)}, {32,32} });
	pokemonHit.AddSprite(Sprite{ pokemonTexture,{(float)(((pokemonId - 1) / 20) * 3 + 2),(float)((pokemonId - 1) % 20)}, {32,32} });
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
	if (animator->HasAnimationFinished()) {
		if (gettingHit) {
			gettingHit = false;
		}
		animator->SelectAnimation("PokemonIdle", true);
	}
	animator->Update();
	animator->Animate((int)(gameAt->screen->screenArea.x + gameAt->screen->screenArea.width/2-16),(int)(gameAt->screen->screenArea.y + gameAt->screen->screenArea.height / 2-16), false);
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
	gameAt->screen->CallScreenEvent(0);
	animator->SelectAnimation("PokemonHit", false);
	gettingHit = true;
}
