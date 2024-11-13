#include "GetArrowGroup.h"
#include "GetEvoArrow.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

GetArrowGroup::GetArrowGroup(ModuleGame* gameAt) : MapArrowGroup(gameAt)
{
	this->gameAt = gameAt;
}

GetArrowGroup::~GetArrowGroup()
{

}

update_status GetArrowGroup::Update()
{
	if (AllActive())
		OnAllActive();

	return UPDATE_CONTINUE;
}

bool GetArrowGroup::CleanUp()
{

	return true;
}

void GetArrowGroup::Sort()
{
	std::sort(mapArrows.begin(), mapArrows.end(), [](MapArrow* a, MapArrow* b) {

		GetEvoArrow* arrowA = static_cast<GetEvoArrow*>(a);
		GetEvoArrow* arrowB = static_cast<GetEvoArrow*>(b);

		return arrowA->GetOrder() < arrowB->GetOrder();
		});

}

void GetArrowGroup::ActivateNext()
{
	for (const auto& arrowPointer : mapArrows)
	{
		if (!arrowPointer->IsActive()) {
			arrowPointer->Activate();
			break;
		}
	}
}

void GetArrowGroup::OnAllActive()
{
	// gameAt->pointsCounter.Add(25000);
	// Entering Bellsprout will make a pokemon appear
}
