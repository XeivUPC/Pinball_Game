#include "PokemonRevealer.h"
#include "Application.h"
#include "ModuleTexture.h"

PokemonRevealer::PokemonRevealer() : MapObject(gameAt)
{
	gameAt->AddObject(this);

	gameAt->App->texture->CreateTexture("Assets/pokemons_shadow_and_color.png", "pokemon");
	tex = gameAt->App->texture->GetTexture("pokemon");
}

PokemonRevealer::~PokemonRevealer(){}

void PokemonRevealer::SelectPokemonIDByZone()
{
	id = 0;
}

update_status PokemonRevealer::Update()
{
	if (id == -1);
	Rectangle rect = { id % 38,id / 38,48,32 };
	if (count == 1)
	{
		rect = { rect.x,rect.y,16,16 };
	}
	if (count == 2)
	{
		rect = { rect.x+16,rect.y+16,16,16 };
	}
	if (count == 3)
	{
		rect = { rect.x+32,rect.y,16,16 };
	}
	if (count == 4)
	{
		rect = { rect.x,rect.y+16,16,16 };
	}
	if (count == 5)
	{
		rect = { rect.x+16,rect.y,16,16 };
	}
	if (count == 6)
	{
		//rect = { rect.x,rect.y,16,16 };
	}
	return UPDATE_CONTINUE;
}
