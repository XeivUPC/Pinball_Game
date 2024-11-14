#include "CapturePokemon.h"
#include "Application.h"
#include "ModuleTexture.h"

void CapturePokemon::AddHit()
{
	count++;
	printf("Ouch\n");
}

void CapturePokemon::SelectPokemonByZone(int zone)
{
	ID = 3;
}

CapturePokemon::CapturePokemon() : ScreenProgram("CapturePokemon")
{
}

CapturePokemon::~CapturePokemon()
{
}

void CapturePokemon::CallAction(int id)
{
	switch (id)
	{
	case 0:
		AddHit();
	default:
		break;
	}
}

void CapturePokemon::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/pokemons_shadow_and_color.png", "spritesheet");
	texture = gameAt->App->texture->GetTexture("spritesheet");
	count = 0;
}

void CapturePokemon::Logic()
{
}

void CapturePokemon::Render()
{

}

void CapturePokemon::EndProgram()
{
}
