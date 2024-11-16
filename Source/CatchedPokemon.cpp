#include "CatchedPokemon.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"

CatchedPokemon::CatchedPokemon(ModuleGame* gameAt) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	counter.Set(0);
	gameAt->App->texture->CreateTexture("Assets/capture_sprites.png", "Assets/capture_sprites.png");
	texture = gameAt->App->texture->GetTexture("Assets/capture_sprites.png");
	rect = { 224,48,16,8 };
}

CatchedPokemon::~CatchedPokemon()
{
}

void CatchedPokemon::CatchPokemon()
{
	counter.Add(1);
}

update_status CatchedPokemon::Update()
{
	if (gameAt->screen->GetActualProgramIdentifier() == "OverworldPokemon") return UPDATE_CONTINUE;
	for (size_t i = 0; i < counter(); i++)
	{
		gameAt->App->renderer->Draw(*texture, (gameAt->screen->screenArea.x + 16 * i), (gameAt->screen->screenArea.y + gameAt->screen->screenArea.height), &rect);
	}
	return UPDATE_CONTINUE;
}

bool CatchedPokemon::CleanUp()
{
	return true;
}
