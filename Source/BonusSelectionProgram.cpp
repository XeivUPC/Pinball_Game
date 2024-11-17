#include "BonusSelectionProgram.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "CentralScreen.h"
#include "PokeBall.h"
#include "ModuleUserPreferences.h"
#include <algorithm> 
#include <random>


bool BonusSelectionProgram::GiveBonus(int type, int subType)
{
	switch (type)
	{
		case 0:
			gameAt->pointsCounter.Add(100 * subType);
			break;
		case 1:
			gameAt->pointsCounter.Add(1000000 * subType);
			break;
		case 2:
			gameAt->bonusPointsCounter.EditMultiplier(gameAt->bonusPointsCounter.GetMultiplier("BonusMultiplier"), (float)subType, "BonusMultiplier");
			break;
		case 3:
			gameAt->SetTimeSaveBall(30);
			break;
		case 4:
			gameAt->SetTimeSaveBall(60);
			break;
		case 5:
			gameAt->SetTimeSaveBall(90);
			break;
		case 6:
			gameAt->SetExtraPika(true);
			//// DoblePika
			break;
		case 7:
			if(gameAt->GetPokeball()->GetType() < PokeBall::SuperBall)
				gameAt->GetPokeball()->SetType(PokeBall::SuperBall);
			break;
		case 8:
			if (gameAt->GetPokeball()->GetType() < PokeBall::Ultraball)
				gameAt->GetPokeball()->SetType(PokeBall::Ultraball);
			break;
		case 9:
			if (gameAt->GetPokeball()->GetType() < PokeBall::MasterBall)
				gameAt->GetPokeball()->SetType(PokeBall::MasterBall);
			break;
		case 10:
			gameAt->SetExtraBall(true);
			break;
		case 11:
			gameAt->screen->SwitchProgram(new CapturePokemon);
			return true;
			break;
		case 12:
			//// CaptureMode
			break;

		default:
			break;
	}
	return false;
}

BonusSelectionProgram::BonusSelectionProgram(int attemptVariant) : ScreenProgram("BonusSelection")
{
	this->attemptVariant = attemptVariant;

	std::random_device rd;
	std::mt19937 g(rd());

	std::uniform_int_distribution<int> pokeballUpgradeType(0, 2);
	int randomPokeUpgrade = 0;

	switch (this->attemptVariant)
	{
		case 1:
			bonusToSelect.emplace_back(3);
			bonusToSelect.emplace_back(6);
			bonusToSelect.emplace_back(2);
			bonusToSelect.emplace_back(0);
			break;
		case 2:
			bonusToSelect.emplace_back(3);
			bonusToSelect.emplace_back(0);
			bonusToSelect.emplace_back(2);
			bonusToSelect.emplace_back(11);
			break;
		case 3:
			bonusToSelect.emplace_back(3);
			bonusToSelect.emplace_back(6);
			bonusToSelect.emplace_back(2);
			bonusToSelect.emplace_back(0);
			bonusToSelect.emplace_back(1);
			break;
		case 4:
			bonusToSelect.emplace_back(4);
			bonusToSelect.emplace_back(2);
			bonusToSelect.emplace_back(0);
			bonusToSelect.emplace_back(1);
			//bonusToSelect.emplace_back(12);
			break;
		case 5:
			bonusToSelect.emplace_back(5);
			bonusToSelect.emplace_back(1);
			///bonusToSelect.emplace_back(1);//// Area Bonus

			
			randomPokeUpgrade = pokeballUpgradeType(g);
			bonusToSelect.emplace_back(7+randomPokeUpgrade);
			bonusToSelect.emplace_back(10);
			break;

		default:
			break;
	}

	
	std::shuffle(bonusToSelect.begin(), bonusToSelect.end(), g);

	
}

BonusSelectionProgram::~BonusSelectionProgram()
{
}

void BonusSelectionProgram::CallAction(int id)
{
}

void BonusSelectionProgram::StartProgram()
{
	gameAt->App->texture->CreateTexture("Assets/map_bonusSprites.png", "map_bonusSprites");
	texture = gameAt->App->texture->GetTexture("map_bonusSprites");

	int selectedLanguage = gameAt->App->userPreferences->GetLanguage() -1 ;
	if (selectedLanguage < 0)
		selectedLanguage = 0;

	animator = new Animator(gameAt->App);

	AnimationData selectAnimationBW = AnimationData("Select_Animation_BW");
	for (size_t i = 0; i < bonusToSelect.size(); i++)
	{
		int xIndex = bonusToSelect[i];
		selectAnimationBW.AddSprite(Sprite{ texture,{(float)xIndex, 6.f * selectedLanguage}, {48,32} }, xIndex);

		AnimationData selectedBonusAnim = AnimationData("Select_Animation_"+std::to_string(xIndex));
		selectedBonusAnim.AddSprite(Sprite{ texture,{(float)xIndex, 6.f * selectedLanguage +1}, {48,32} }, xIndex);
		selectedBonusAnim.AddSprite(Sprite{ texture,{(float)xIndex, 6.f * selectedLanguage +2}, {48,32} }, xIndex);

		if (xIndex == 0 || xIndex == 1) {
			for (size_t i = 0; i < 9; i++)
			{
				AnimationData selectedBonusSubIndexAnim = AnimationData("Select_Animation_" + std::to_string(xIndex) + "_" + std::to_string(i+1));
				selectedBonusSubIndexAnim.AddSprite(Sprite{ texture,{(float)1*i +i, 6.f * selectedLanguage + 3+xIndex}, {48,32} }, xIndex);
				selectedBonusSubIndexAnim.AddSprite(Sprite{ texture,{(float)1*i +i + 1, 6.f * selectedLanguage + 3 + xIndex}, {48,32} }, xIndex);
				animator->AddAnimation(selectedBonusSubIndexAnim);
			}
		}
		if (xIndex == 2) {
			for (size_t i = 0; i < 5; i++)
			{
				AnimationData selectedBonusSubIndexAnim = AnimationData("Select_Animation_" + std::to_string(xIndex) + "_" + std::to_string(i + 1));
				selectedBonusSubIndexAnim.AddSprite(Sprite{ texture,{(float)1 * i + i, 6.f * selectedLanguage + 5}, {48,32} }, xIndex);
				selectedBonusSubIndexAnim.AddSprite(Sprite{ texture,{(float)1 * i + i + 1, 6.f * selectedLanguage + 5}, {48,32} }, xIndex);
				animator->AddAnimation(selectedBonusSubIndexAnim);
			}
		}

		animator->AddAnimation(selectedBonusAnim);

	}
	animator->AddAnimation(selectAnimationBW);

	animator->SetSpeed(0.1f);
	animator->SelectAnimation("Select_Animation_BW", true);
	stopTimer.Start();

	audioBonusSwapId = gameAt->App->audio->LoadFx("Assets/SFX/Game_BonusSwap.ogg");
}

void BonusSelectionProgram::Logic()
{
	animator->Update();

	int currentSprite = animator->GetCurrentAnimationSpriteIndex();
	if (previousSprite != currentSprite)
	{
		gameAt->App->audio->PlayFx(audioBonusSwapId);
	}
	previousSprite = currentSprite;

	if (selectedBonus == -1) {
		speedReduction += speedReduction * GetFrameTime() / 2.f;
		animator->SetSpeed(animator->GetSpeed() + speedReduction * GetFrameTime());
		if (stopTime < stopTimer.ReadSec()) {
			animator->SetSpeed(0.5f);
			selectedBonus = animator->GetCurrentAnimationSprite().extraData;
			animator->SelectAnimation("Select_Animation_" + std::to_string(selectedBonus), true);
			selectedShowTimer.Start();

			selectedBonusSubType = -1;
			if (selectedBonus == 0 || selectedBonus == 1)
			{
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distrib(1, 9);

				selectedBonusSubType = distrib(gen);
			}
			if (selectedBonus == 2) {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distrib(1, 5);

				selectedBonusSubType = distrib(gen);
			}		
		}
	}
	else {
		if (selectedBonusSubType != -1 && !showingSubType) {

			if (selectedShowTime/2 < selectedShowTimer.ReadSec()) {
				animator->SelectAnimation("Select_Animation_" + std::to_string(selectedBonus) + "_" + std::to_string(selectedBonusSubType), true);
				selectedShowTime += 1;
				showingSubType = true;
			}
		}
		if (selectedShowTime < selectedShowTimer.ReadSec()) {
			canBeOverwritten = true;
			gameAt->FreeBallCave();
			if(!GiveBonus(selectedBonus, selectedBonusSubType))
				gameAt->screen->RemoveProgram();
		}
	}

	
}

void BonusSelectionProgram::Render()
{
	animator->Animate((int)gameAt->screen->screenArea.x, (int)gameAt->screen->screenArea.y, false);
	gameAt->App->audio->PlayFx(audioBonusSwapId);
}

void BonusSelectionProgram::EndProgram()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	bonusToSelect.clear();
}
