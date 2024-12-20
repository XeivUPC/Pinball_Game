#include "ModuleGame.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "MapObject.h"
#include "ModuleAudio.h"
#include "MapEnergyBattery.h"
#include "MapCave.h"
#include "SaveAgainBall.h"
#include "GetArrowGroup.h"
#include "EvoArrowGroup.h"
#include <sstream>


ModuleGame::ModuleGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	pointsCounter.Set(100);

	saveAgainBall = new SaveAgainBall(this, { 64.f / SCREEN_SIZE ,238.f / SCREEN_SIZE });
	SetTimeSaveBall(24.f);

	return true;
}

update_status ModuleGame::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleGame::CleanUp()
{
	habitatIndex = -1;

	saveBall = false;
	extraBall = false;

	isEnergyCharged = false;
	isEnergyUsed = false;
	isBallInTopSection = false;

	canCapture = false;
	canEvolve = false;

	bonusSelectionAttempts = 1;
	return true;
}

PokeBall* ModuleGame::GetPokeball()
{
	return pokeBall;
}

GameUI* ModuleGame::GetUI()
{
	return UI;
}

TimerUI* ModuleGame::GetTimerUI()
{
	return timerUI;
}

void ModuleGame::NextHabitat()
{
	habitatIndex++;
	if (habitatIndex >= (int)mapHabitats.size())
		habitatIndex = 0;
}

void ModuleGame::PreviousHabitat()
{
	habitatIndex--;
	if (habitatIndex < 0)
		habitatIndex = mapHabitats.size()-1;
}

bool ModuleGame::ChangeToHabitat(int habitat)
{
	int index = 0;
	bool found=false;
	for (const auto& habitatType : mapHabitats) {
		if (habitat == habitatType) {
			found = true;
			break;
		}
		index++;
	}
	if (found)
		habitatIndex = index;

	return found;
}

int ModuleGame::GetHabitat()
{
	return mapHabitats[habitatIndex];
}

bool ModuleGame::IsEnergyCharged()
{
	return isEnergyCharged;
}

void ModuleGame::SetEnergyStatus(bool isCharged)
{
	isEnergyCharged = isCharged;
}

void ModuleGame::UseEnergy()
{
	energyBattery->Reset();
}

bool ModuleGame::CanEvolve()
{
	return canEvolve;
}

bool ModuleGame::CanCapture()
{
	return canCapture;
}

void ModuleGame::StartCapture()
{
	getArrowGroup->DesactivateAll();
	canCapture = false;
}

void ModuleGame::StartEvolve()
{
	evoArrowGroup->DesactivateAll();
	canEvolve = false;
}

int ModuleGame::GetCaptureRarityLevel()
{
	return getArrowGroup->GetActiveAmount();
}

void ModuleGame::OpenCave()
{
	cave->OpenCave();
}

void ModuleGame::CloseCave()
{
	cave->CloseCave();
}

void ModuleGame::FreeBallCave()
{
	cave->FreeBall();
}

bool ModuleGame::HasExtraPika()
{
	return extraPika;
}

void ModuleGame::SetExtraPika(bool status)
{
	extraPika = status;
}

void ModuleGame::PlayFieldMusic()
{
	App->audio->PlayMusic(musicPath.c_str(), 0.3f);
}

void ModuleGame::PlayCatchEvoMusic()
{
	App->audio->PlayMusic(catchEvoMusicPath.c_str(), 0.3f);
}

void ModuleGame::SetSaveBall(bool status)
{
	saveBall = status;
}

void ModuleGame::SetExtraBall(bool status)
{
	extraBall = status;
}

void ModuleGame::SetTimeSaveBall(float time)
{
	saveAgainBall->SetBallSaverTimer(time);
}

bool ModuleGame::HasExtraBall()
{
	return extraBall;
}

bool ModuleGame::HasSaveBall()
{
	return saveBall;
}

int ModuleGame::GetBonusSelectionAttempts()
{
	return bonusSelectionAttempts;
}

void ModuleGame::AddBonusSelectionAttempts()
{
	bonusSelectionAttempts++;
	if (bonusSelectionAttempts > 5)
		bonusSelectionAttempts = 1;
}

bool ModuleGame::IsBallInTopSection()
{
	return isBallInTopSection;
}

void ModuleGame::SetState(GameStates stateToChange)
{
	state = stateToChange;

}

ModuleGame::GameStates ModuleGame::GetState()
{
	return state;
}

void ModuleGame::AddObject(MapObject* object)
{
	mapObjects.emplace_back(object);
}

void ModuleGame::RemoveObject(MapObject* object)
{
	ObjectsToRemove.emplace_back(object);
}

void ModuleGame::FromStringToVertices(std::string stringData, std::vector<b2Vec2>& vector)
{
	std::stringstream ss(stringData);
	std::string vectorValue;

	vector.clear();

	while (std::getline(ss, vectorValue, ' ')) {
		std::stringstream ss_vectorValue(vectorValue);

		std::string x_str, y_str;

		std::getline(ss_vectorValue, x_str, ',');
		std::getline(ss_vectorValue, y_str);

		float x_poly = std::stof(x_str);
		float y_poly = std::stof(y_str);


		vector.push_back(b2Vec2(x_poly / SCREEN_SIZE, y_poly / SCREEN_SIZE));
	}
}

void ModuleGame::RepositionCamera(b2Vec2 positionToTrack)
{
	if (positionToTrack.x > 160 / SCREEN_SIZE) {
		App->renderer->camera.offset.x = -31 * SCREEN_SIZE;
	}
	else {
		App->renderer->camera.offset.x = 0;
	}

	if (positionToTrack.y > 134 / SCREEN_SIZE) {
		App->renderer->camera.offset.y = -134 * SCREEN_SIZE;
		isBallInTopSection = false;
	}
	else {
		App->renderer->camera.offset.y = 0;
		isBallInTopSection = true;
	}
}

void ModuleGame::RemoveAllPendentObjects()
{
	for (size_t i = 0; i < ObjectsToRemove.size(); i++)
	{
		MapObject* object = ObjectsToRemove.at(i);
		object->CleanUp();
		for (size_t j = 0; j < mapObjects.size(); j++)
		{
			if(mapObjects.at(j)==object)
				mapObjects.erase(mapObjects.begin() + j);
		}
		delete object;
	}
	ObjectsToRemove.clear();
}
