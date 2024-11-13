#include "CapturePokemon.h"
#include "Application.h"
#include "ModuleTexture.h"

void CapturePokemon::AddHit()
{
	count++;
}

void CapturePokemon::SelectPokemonByZone(int zone)
{
	ID = 3;
}

CapturePokemon::CapturePokemon(const std::string id) : ScreenProgram(id)
{
}

void CapturePokemon::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/pokemons_shadow_and_color.png", "spritesheet");
	texture = gameAt->App->texture->GetTexture("spritesheet");
}
