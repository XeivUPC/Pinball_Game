#include "OverworldPokemon.h"
#include "Application.h"
#include "ModuleTexture.h"

void OverworldPokemon::AddHit()
{
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
}

void OverworldPokemon::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/capture_sprites.png", "Assets/capture_sprites.png");
	texture = gameAt->App->texture->GetTexture("Assets/capture_sprites.png");
}

void OverworldPokemon::Logic()
{
}

void OverworldPokemon::Render()
{
	rect = {192, 64, gameAt->screen->screenArea.width, gameAt->screen->screenArea.height};
	gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
}

void OverworldPokemon::EndProgram()
{
}
