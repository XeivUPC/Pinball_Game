#include "BonusMultiplierSensorGroup.h"
#include "BonusMultiplierSensor.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include "GameUI.h"
#include <algorithm>

BonusMultiplierSensorGroup::BonusMultiplierSensorGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
	gameAt->bonusPointsCounter.AddMultiplier(1.f, "BonusBumperMultiplier");
}

BonusMultiplierSensorGroup::~BonusMultiplierSensorGroup()
{

}

update_status BonusMultiplierSensorGroup::Update()
{
	BonusMultiplierSensor* frontSensor = static_cast<BonusMultiplierSensor*>(mapSensors.front());
	BonusMultiplierSensor* backSensor = static_cast<BonusMultiplierSensor*>(mapSensors.back());
	if (!frontSensor->IsDualTwinkling() && !backSensor->IsDualTwinkling()) {
		if (!frontSensor->IsActive()) {
			frontSensor->SetGlowing();
			backSensor->SetNotGlowing();
		}
		else if (frontSensor->IsActive() && !backSensor->IsActive()) {
			if (frontSensor->JustGotHit()) {
				frontSensor->SetDualTwinkling();
				backSensor->SetDualTwinkling();
			}
			else {
				frontSensor->SetNotGlowing();
				backSensor->SetGlowing();
			}
		}
		else if (frontSensor->IsActive() && backSensor->IsActive()) {
			totalNum++;

			const char* text = "MULT. BONUS x";
			std::string textNum = std::to_string(totalNum);
			std::string result = std::string(text) + textNum;

			gameAt->bonusPointsCounter.EditMultiplier(gameAt->bonusPointsCounter.GetMultiplier("BonusBumperMultiplier"), (float)totalNum, "BonusBumperMultiplier");

			gameAt->GetUI()->AddText(result);

			if (totalNum >= 100) {
				totalNum = 99;
			}
			frontSensor->SetNumber(totalNum/10);
			backSensor->SetNumber(totalNum - (totalNum / 10)*10);

			frontSensor->Desactivate();
			backSensor->Desactivate();

			frontSensor->SetDualTwinkling();
			backSensor->SetDualTwinkling();
		}
	}

	return UPDATE_CONTINUE;
}

bool BonusMultiplierSensorGroup::CleanUp()
{

	return true;
}

void BonusMultiplierSensorGroup::Sort()
{
	std::sort(mapSensors.begin(), mapSensors.end(), [](MapSensor* a, MapSensor* b) {

		BonusMultiplierSensor* sensorA = static_cast<BonusMultiplierSensor*>(a);
		BonusMultiplierSensor* sensorB = static_cast<BonusMultiplierSensor*>(b);

		return sensorA->GetOrder() < sensorB->GetOrder();
		});
}

void BonusMultiplierSensorGroup::OnAllActive()
{
}
