#include "PokeballChangerGroup.h"
#include "PokeBall.h"
#include "ModuleUserPreferences.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "GameUI.h"
#include <algorithm>

PokeballChangerGroup::PokeballChangerGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;

	audioPokeballSensorAllActiveId = gameAt->App->audio->LoadFx("Assets/SFX/Game_PokeballSensorAllActive.ogg");

}

PokeballChangerGroup::~PokeballChangerGroup()
{

}

update_status PokeballChangerGroup::Update()
{
	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		bool startValue = mapSensors.front()->IsActive();

		for (size_t i = 0; i < mapSensors.size() - 1; i++)
		{
			if (mapSensors[i + 1]->IsActive())
				mapSensors[i]->Activate();
			else
				mapSensors[i]->Desactivate();
		}
		if (startValue)
			mapSensors.back()->Activate();
		else
			mapSensors.back()->Desactivate();
	}

	if (IsKeyPressed(gameAt->App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		bool lastValue = mapSensors.back()->IsActive();

		for (size_t i = mapSensors.size() - 1; i > 0; i--)
		{
			if (mapSensors[i - 1]->IsActive())
				mapSensors[i]->Activate();
			else
				mapSensors[i]->Desactivate();
		}
		if (lastValue)
			mapSensors.front()->Activate();
		else
			mapSensors.front()->Desactivate();
	}

	bool areTwinkling = true;
	for (const auto& sensorPointer : mapSensors)
	{
		if (!sensorPointer->IsTwinkling()) {
			areTwinkling = false;
		}
	}
	if (AllActive() && !areTwinkling)
		OnAllActive();

	for (const auto& sensorPointer : mapSensors)
	{
		if (sensorPointer->HasFinishedTwinkling()) {
			DesactivateAll();
			sensorPointer->FinishTwinkle();
		}
	}
	return UPDATE_CONTINUE;
}

bool PokeballChangerGroup::CleanUp()
{
	mapSensors.clear();
	return true;
}

void PokeballChangerGroup::Sort()
{
	std::sort(mapSensors.begin(), mapSensors.end(), [](MapSensor* a, MapSensor* b) {

		PokeballChangerSensor* sensorA = static_cast<PokeballChangerSensor*>(a);
		PokeballChangerSensor* sensorB = static_cast<PokeballChangerSensor*>(b);

		return sensorA->GetOrder() < sensorB->GetOrder();
		});

}

void PokeballChangerGroup::OnAllActive()
{
	PokeBall* pokeBall = gameAt->GetPokeball();
	gameAt->App->audio->PlayFx(audioPokeballSensorAllActiveId);
	if (pokeBall->GetType() != PokeBall::PokeballType::MasterBall) {
		pokeBall->SetType(PokeBall::PokeballType(pokeBall->GetType() + 1));
		gameAt->pointsCounter.Add(4000);
		const char* text = "MULT. BOARD x";
		std::string textNum = std::to_string(pokeBall->GetType() + 1);
		if (pokeBall->GetType() == PokeBall::PokeballType::MasterBall) {
			textNum = std::to_string(5);
		}
		std::string result = std::string(text) + textNum;

		gameAt->GetUI()->AddText(result);
	}
	else {
		gameAt->pointsCounter.Take(1000);
		gameAt->pointsCounter.AddWithoutMultipliers(10000000);
	}
	for (const auto& sensorPointer : mapSensors)
	{
		sensorPointer->Twinkle();
	}
}
