#include "CapturePokemon.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "CentralScreen.h"
#include "ModulePokedex.h"
#include "OverworldPokemon.h"
#include "ModuleUserPreferences.h"
#include "TimerUI.h"
#include "GameUI.h"

void CapturePokemon::AddHit()
{
	if(animationStarted == 0)
		count++;
}

CapturePokemon::CapturePokemon() : ScreenProgram("CapturePokemon")
{

}

CapturePokemon::~CapturePokemon()
{
}

void CapturePokemon::SetRandomPokemonByZone(bool zoneID, int rarity)
{
	std::vector<int> possiblePokemon;
	int index = 0;
	for (int i = 0; i < gameAt->App->scene_pokedex->GetPokemonListCount()-1; i++)
	{
		if (!zoneID)
		{
			for (size_t j = 0; j < gameAt->App->scene_pokedex->GetBlueMapHabitats(i).size(); j++)
			{
				if (gameAt->App->scene_pokedex->GetBlueMapHabitats(i).at(j) == gameAt->GetHabitat() && gameAt->App->scene_pokedex->GetPokemonRarity(i) == rarity)
				{
					possiblePokemon.push_back(i);
					break;
				}
			}
		}
		else
		{
			for (size_t j = 0; j < gameAt->App->scene_pokedex->GetRedMapHabitats(i).size(); j++)
			{
				if (gameAt->App->scene_pokedex->GetRedMapHabitats(i).at(j) == gameAt->GetHabitat() && gameAt->App->scene_pokedex->GetPokemonRarity(i) == rarity)
				{
					possiblePokemon.push_back(i);
					break;
				}
			}
		}
	}
	index = GetRandomValue(0, possiblePokemon.size()-1);
	SetID(possiblePokemon.at(index));
	possiblePokemon.clear();
}

void CapturePokemon::SetID(int id)
{
	ID = id;
}

void CapturePokemon::CallAction(int id)
{
	if (gameAt->GetTimerUI()->IsTimerFinished())
	{
		return;
	}

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
	gameAt->App->texture->CreateTexture("Assets/pokemons_shadow_and_color.png", "Assets/pokemons_shadow_and_color.png");
	texture = gameAt->App->texture->GetTexture("Assets/pokemons_shadow_and_color.png");
	bool isRedMap = false;
	ModuleGameRedMap* redMap = (ModuleGameRedMap*)(gameAt);
	if (redMap != nullptr)
		isRedMap = true;

	int rarityLevel = gameAt->GetCaptureRarityLevel();
	if (rarityLevel < 2)
		rarityLevel = 2;
	SetRandomPokemonByZone(isRedMap, rarityLevel);
	count = 0;
	factor = 0;
	animationTimer.Start();
	animationTime = 0.5f;
	animationStarted = 0;
	animating = false;
	baseRect = { (float)((ID / 38)*2) * gameAt->screen->screenArea.width, (float)(ID % 38) * gameAt->screen->screenArea.height, gameAt->screen->screenArea.width, gameAt->screen->screenArea.height };
	gameAt->GetTimerUI()->AddTimer(60 * 2);

	gameAt->PlayCatchEvoMusic();
}

void CapturePokemon::Logic()
{
	if (ID == -1)
		return;

	if (gameAt->GetTimerUI()->IsTimerFinished() )
	{
		if (failedTimer.ReadSec() > failedTime) {
			int selectedLanguage = gameAt->App->userPreferences->GetLanguage();
			gameAt->GetUI()->AddText(failedUIText[selectedLanguage]);
			gameAt->GetTimerUI()->HideTimer();
			gameAt->PlayFieldMusic();
			gameAt->screen->RemoveProgram();
		}
		return;
	}
	else {
		failedTimer.Start();
	}

	if (animating)
		factor += GetFrameTime() / animationTime;
	if (animationStarted == 0 && count >= 6 && !animating && !gameAt->IsBallInTopSection())
	{
		factor = 0;
		animating = true;
		animationTimer.Start();
	}

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
		gameAt->screen->SwitchProgram(new OverworldPokemon(ID));
}

void CapturePokemon::Render()
{
	rect = baseRect;
	gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
	rect.x = baseRect.x + gameAt->screen->screenArea.width;
	rect.width = 16;
	rect.height = 16;
	if ((animationStarted == 0 && count >= 1) || (animationStarted != 0 && (count >= 1 && count <= 3)))
	{
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 2) || (animationStarted != 0 && (count >= 2 && count <= 4)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 16;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x+16), (int)(gameAt->screen->screenArea.y+16), &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 3) || (animationStarted != 0 && (count >= 3 && count <= 5)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 32;
		rect.y = baseRect.y;
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x + 32), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 4) || (animationStarted != 0 && (count >= 4 && count <= 6)))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x), (int)(gameAt->screen->screenArea.y+16), &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 5) || (animationStarted != 0 && ((count >= 5 && count <= 6) || (count == 1))))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 16;
		rect.y = baseRect.y;
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x+16), (int)(gameAt->screen->screenArea.y), &rect, WHITE);
	}
	if ((animationStarted == 0 && count >= 6) || (animationStarted != 0 && ((count >= 1 && count <= 2) || (count == 6))))
	{
		rect.x = baseRect.x + gameAt->screen->screenArea.width + 32;
		rect.y = baseRect.y + 16;
		gameAt->App->renderer->Draw(*texture, (int)(gameAt->screen->screenArea.x + 32), (int)(gameAt->screen->screenArea.y+16), &rect, WHITE);
	}
}

void CapturePokemon::EndProgram()
{
	gameAt->App->scene_pokedex->DiscoverPokemon(ID);

	failedUIText.clear();

}
