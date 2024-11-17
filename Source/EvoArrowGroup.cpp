#include "EvoArrowGroup.h"
#include "GetEvoArrow.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

EvoArrowGroup::EvoArrowGroup(ModuleGame* gameAt) : MapArrowGroup(gameAt)
{
	this->gameAt = gameAt;
}

EvoArrowGroup::~EvoArrowGroup()
{

}

update_status EvoArrowGroup::Update()
{
	for (const auto& arrowPointer : mapArrows)
	{
		if (!arrowPointer->IsActive()) {
			arrowPointer->Twinkle();
			break;
		}
	}
	if (AllActive())
		OnAllActive();

	return UPDATE_CONTINUE;
}

bool EvoArrowGroup::CleanUp()
{
	mapArrows.clear();
	return true;
}

void EvoArrowGroup::Sort()
{
	std::sort(mapArrows.begin(), mapArrows.end(), [](MapArrow* a, MapArrow* b) {

		GetEvoArrow* arrowA = static_cast<GetEvoArrow*>(a);
		GetEvoArrow* arrowB = static_cast<GetEvoArrow*>(b);

		return arrowA->GetOrder() < arrowB->GetOrder();
		});

}

void EvoArrowGroup::ActivateNext()
{
	for (const auto& arrowPointer : mapArrows)
	{
		if (!arrowPointer->IsActive()) {
			arrowPointer->Activate();
			break;
		}
	}
}

void EvoArrowGroup::OnAllActive()
{
	// gameAt->pointsCounter.Add(25000);
	// Dito collider now gets removed and evolution is possible
	mapArrows.front()->Twinkle();
}
