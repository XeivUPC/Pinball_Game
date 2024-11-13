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
	gameAt->App->texture->CreateTexture("Assets/pokedex-spritesheet.png", "spritesheet");
	pokedexSpritesheet = App->texture->GetTexture("spritesheet");
}
