#include "BonusMultiplierSensorGroup.h"
#include "BonusMultiplierSensor.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

BonusMultiplierSensorGroup::BonusMultiplierSensorGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
}

BonusMultiplierSensorGroup::~BonusMultiplierSensorGroup()
{

}

update_status BonusMultiplierSensorGroup::Update()
{
	BonusMultiplierSensor* frontSensor = static_cast<BonusMultiplierSensor*>(mapSensors.front());
	BonusMultiplierSensor* backSensor = static_cast<BonusMultiplierSensor*>(mapSensors.back());
	if (!frontSensor->IsActive()) {
		frontSensor->SetGlowing();
		backSensor->SetNotGlowing();
	}
	else if (frontSensor->IsActive() && !backSensor->IsActive()) {
		frontSensor->SetNotGlowing();
		backSensor->SetGlowing();
	}
	else if (frontSensor->IsActive() && backSensor->IsActive()) {
		totalNum++;
		if (totalNum >= 100) {
			totalNum = 99;
		}
		frontSensor->SetNumber((int)totalNum/10);
		backSensor->SetNumber((int)totalNum - ((int)totalNum / 10)*10);

		frontSensor->Desactivate();
		backSensor->Desactivate();
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
