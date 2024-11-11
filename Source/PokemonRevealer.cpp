#include "PokemonRevealer.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

PokemonRevealer::PokemonRevealer(ModuleGame* gameAt) : MapObject(gameAt)
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
	factor += time.ReadSec() / animTime;
	printf("%d\n", count);
	if (id == -1)
		return UPDATE_CONTINUE;
	if (IsKeyPressed(KEY_B))
		count++;
	Rectangle rect = { id % 38,id / 38,48,32 };
	gameAt->App->renderer->Draw(*tex, 56, 166, &rect, WHITE);
	rect.x += 48;
	if ((count >= 1 && count < 6) || ((count == 6 && (factor/2 - (int)factor/2 > 0) && (factor / 2 - (int)factor / 2 < 1/6))))
	{
		rect = { rect.x,rect.y,16,16 };
		gameAt->App->renderer->Draw(*tex, 56, 166, &rect, WHITE);
	}
	if ((count >= 2 && count < 6) || ((count == 6 && (factor / 2 - (int)factor / 2 > 1/6) && (factor / 2 - (int)factor / 2 < 2 / 6))))
	{
		rect = { rect.x+16,rect.y+16,16,16 };
		gameAt->App->renderer->Draw(*tex, 72, 182, &rect, WHITE);
	}
	if ((count >= 3 && count < 6) || ((count == 6 && (factor / 2 - (int)factor / 2 > 2 / 6) && (factor / 2 - (int)factor / 2 < 3 / 6))))
	{
		rect = { rect.x+16,rect.y-16,16,16 };
		gameAt->App->renderer->Draw(*tex, 88, 166, &rect, WHITE);
	}
	if ((count >= 4 && count < 6) || ((count == 6 && (factor / 2 - (int)factor / 2 > 3 / 6) && (factor / 2 - (int)factor / 2 < 4 / 6))))
	{
		rect = { rect.x-32,rect.y+16,16,16 };
		gameAt->App->renderer->Draw(*tex, 56, 182, &rect, WHITE);
	}
	if ((count >= 5 && count < 6) || ((count == 6 && (factor / 2 - (int)factor / 2 > 4 / 6) && (factor / 2 - (int)factor / 2 < 5 / 6))))
	{
		rect = { rect.x+16,rect.y-16,16,16 };
		gameAt->App->renderer->Draw(*tex, 72, 166, &rect, WHITE);
	}
	if ((count == 6 && factor == 0) || ((count == 6 && (factor / 2 - (int)factor / 2 > 5 / 6) && (factor / 2 - (int)factor / 2 < 1))))
	{
		rect = { rect.x + 16,rect.y + 16,16,16 };
		gameAt->App->renderer->Draw(*tex, 88, 182, &rect, WHITE);
	}
	if (count == 6 && factor >= 1)
	{
		if (pokemonCompleted)
		{

		}
		else
		{
			time.Start();
		}
	}
	return UPDATE_CONTINUE;
}

bool PokemonRevealer::CleanUp()
{
	return true;
}