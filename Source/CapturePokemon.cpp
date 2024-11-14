#include "CapturePokemon.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"

void CapturePokemon::AddHit()
{
	if(animationStarted == 0)
		count++;
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

void CapturePokemon::SetID(int id)
{
	ID = id;
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
	factor = 0;
	animationTimer.Start();
	animationTime = 0.5f;
	animationStarted = 0;
	ID = 3;
	animating = false;
	baseRect = { (float)(ID / 38) * gameAt->screen->screenArea.width, (float)(ID % 38) * gameAt->screen->screenArea.height, gameAt->screen->screenArea.width, gameAt->screen->screenArea.height };
}

void CapturePokemon::Logic()
{
	if (ID == -1)
		return;
	if (animating)
		factor += GetFrameTime() / animationTime;
	if (animationStarted == 0 && count >= 6 && !animating && !gameAt->IsBallInTopSection())
	{
		factor = 0;
		animating = true;
		animationTimer.Start();
	}

	////// Solo avanzar cuando el ball esta abajo/////////

	if ((factor >= 1 && animationStarted != 0) || (factor >= 1.5f && animationStarted == 0 && animating))
	{
		factor = 0;
		animationStarted++;
		animationTimer.Start();
	}
	if (animationStarted != 0 && animating)
	{
		count = (int)trunc(factor * 6 + 1);
	}
	if (animationStarted == 3)
		EndProgram();
}

void CapturePokemon::Render()
{
	rect = baseRect;
	gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x, gameAt->screen->screenArea.y, &rect, WHITE);
	rect.x = baseRect.x + gameAt->screen->screenArea.width;
	rect.width = 16;
	rect.height = 16;
	if ((animationStarted == 0 && count >= 1) || (animationStarted != 0 && (count >= 1 && count <= 3)))
	{
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x, gameAt->screen->screenArea.y, &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 2) || (animationStarted != 0 && (count >= 2 && count <= 4)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 16;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x+16, gameAt->screen->screenArea.y+16, &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 3) || (animationStarted != 0 && (count >= 3 && count <= 5)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 32;
		rect.y = baseRect.y;
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x + 32, gameAt->screen->screenArea.y, &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 4) || (animationStarted != 0 && (count >= 4 && count <= 6)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x, gameAt->screen->screenArea.y+16, &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 5) || (animationStarted != 0 && ((count >= 5 && count <= 6) || (count == 1))))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 16;
		rect.y = baseRect.y;
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x+16, gameAt->screen->screenArea.y, &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 6) || (animationStarted != 0 && ((count >= 1 && count <= 2) || (count == 6))))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 32;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, gameAt->screen->screenArea.x + 32, gameAt->screen->screenArea.y+16, &rect, WHITE);
	}
}

void CapturePokemon::EndProgram()
{
	gameAt->screen->QuitProgram();
}
