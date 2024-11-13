#include "CapturePokemon.h"

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
