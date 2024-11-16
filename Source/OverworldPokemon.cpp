#include "OverworldPokemon.h"
#include "OverworldPokemonBumper.h"
#include "ModuleUserPreferences.h"
#include "ModulePhysics.h"
#include "ModulePokedex.h"
#include "Pokeball.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"

void OverworldPokemon::AddHit()
{
	if(count < 4)
		count++;
}

OverworldPokemon::OverworldPokemon(int id) : ScreenProgram("OverworldPokemon")
{
	ID = id;
}

OverworldPokemon::~OverworldPokemon()
{
}

void OverworldPokemon::CallAction(int id)
{
	switch (id)
	{
	case 0:
		AddHit();
	default:
		break;
	}
}

void OverworldPokemon::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/capture_sprites.png", "Assets/capture_sprites.png");
	texture = gameAt->App->texture->GetTexture("Assets/capture_sprites.png");
	pokemon_bumper = new OverworldPokemonBumper(gameAt, { gameAt->screen->screenArea.x + gameAt->screen->screenArea.width/2,gameAt->screen->screenArea.y + gameAt->screen->screenArea.height/2 }, 8, 1.f, gameAt->App->scene_pokedex->GetOverworldTexture(ID));
	animator = new Animator(gameAt->App);
	AnimationData captureSmoke = AnimationData("Smoke");
	captureSmoke.AddSprite(Sprite{ texture, {0, 0}, {48,48} });
	captureSmoke.AddSprite(Sprite{ texture, {1, 0}, {48,48} });
	captureSmoke.AddSprite(Sprite{ texture, {2, 0}, {48,48} });
	captureSmoke.AddSprite(Sprite{ texture, {3, 0}, {48,48} });
	AnimationData pokeballShake = AnimationData("PokeballShake");
	pokeballShake.AddSprite(Sprite{ texture, {12, (float)gameAt->GetPokeball()->GetType()}, {16,16}});
	pokeballShake.AddSprite(Sprite{ texture, {13, (float)gameAt->GetPokeball()->GetType()}, {16,16}});
	AnimationData pokeballStatic = AnimationData("PokeballStatic");
	pokeballStatic.AddSprite(Sprite{ texture, {12, (float)gameAt->GetPokeball()->GetType()}, {16,16}});
	pokeballStatic.AddSprite(Sprite{ texture, {12, (float)gameAt->GetPokeball()->GetType()}, {16,16}});

	animator->SetSpeed(0.05f);
	animator->AddAnimation(captureSmoke);
	animator->AddAnimation(pokeballShake);
	animator->AddAnimation(pokeballStatic);
	animator->SetIfCanDraw(false);
	animator->SelectAnimation("PokeballStatic", true);
}

void OverworldPokemon::Logic()
{
	if (pokemon_bumper != nullptr && count == 4)
	{
		gameAt->RemoveObject(pokemon_bumper);
		pokemon_bumper = nullptr;
		animator->SetIfCanDraw(true);
		animator->SelectAnimation("Smoke", false);
	}

	if (animating && factor < fallingTime)
	{
		factor += GetFrameTime()/fallingTime;
		offset = factor - fallingTime / 2;
	}
	else if (animating && factor >= fallingTime)
	{
		offset = 0;
		animator->SelectAnimation("PokeballShake", false);
	}
	if (animator->GetCurrentAnimationName() == "Smoke" && animator->HasAnimationFinished())
	{
		animating = true;
		animator->SetSpeed(0.15f);
		animator->SelectAnimation("PokeballStatic", false);
		count = 0;

		gameAt->GetPokeball()->SetIfBlockMovement(true);
		gameAt->GetPokeball()->SetIfBlockRender(true);
		gameAt->GetPokeball()->SetPosition({ (gameAt->screen->screenArea.x + gameAt->screen->screenArea.width / 2 ) / SCREEN_SIZE, (gameAt->screen->screenArea.y + gameAt->screen->screenArea.height / 2) / SCREEN_SIZE });

		//Quitar bola pinball
	}
	if (animator->GetCurrentAnimationName() == "PokeballStatic" && animator->HasAnimationFinished())
	{
		animator->SelectAnimation("PokeballShake", false);
	}
	if (animator->GetCurrentAnimationName() == "PokeballShake" && animator->HasAnimationFinished())
	{
		if (count == 2) {
			gameAt->App->scene_pokedex->CapturePokemon(ID);
			//Poner bola pinball

			gameAt->GetPokeball()->SetIfBlockMovement(false);
			gameAt->GetPokeball()->SetIfBlockRender(false);
			gameAt->GetPokeball()->SetVelocity({ 5,-1 });
			gameAt->screen->RemoveProgram();
			return;
		}
		animator->SelectAnimation("PokeballStatic", false);
		count++;
	}
	
}

void OverworldPokemon::Render()
{
	rect = {192, 64, gameAt->screen->screenArea.width, gameAt->screen->screenArea.height};
	gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
	if (count >= 1 || animating)
	{
		rect = { 224, (float)gameAt->App->userPreferences->GetLanguage()*8, 16, 8};
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y + gameAt->screen->screenArea.height), &rect, WHITE);
	}
	if (count >= 2 || animating)
	{
		rect = { 224+16, (float)gameAt->App->userPreferences->GetLanguage()*8, 16, 8 };
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x+16), (int)(gameAt->screen->screenArea.y + gameAt->screen->screenArea.height), &rect, WHITE);
	}
	if (count >= 3 || animating)
	{
		rect = { 224+32, (float)gameAt->App->userPreferences->GetLanguage()*8, 16, 8 };
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x+32), (int)(gameAt->screen->screenArea.y + gameAt->screen->screenArea.height), &rect, WHITE);
	}
	animator->Update();
	animator->Animate((int)(gameAt->screen->screenArea.x + gameAt->screen->screenArea.width / 2 - animator->GetCurrentAnimationSprite().size.x/2), (int)(gameAt->screen->screenArea.y + gameAt->screen->screenArea.height / 2 - animator->GetCurrentAnimationSprite().size.y / 2 + offset*2), false);
}

void OverworldPokemon::EndProgram()
{
}
