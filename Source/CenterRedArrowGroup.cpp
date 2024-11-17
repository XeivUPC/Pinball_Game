#include "CenterRedArrowGroup.h"
#include "CenterRedArrow.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

CenterRedArrowGroup::CenterRedArrowGroup(ModuleGame* gameAt) : MapArrowGroup(gameAt)
{
	this->gameAt = gameAt;
}

CenterRedArrowGroup::~CenterRedArrowGroup()
{

}

update_status CenterRedArrowGroup::Update()
{
	return UPDATE_CONTINUE;
}

bool CenterRedArrowGroup::CleanUp()
{
	mapArrows.clear();

	return true;
}

void CenterRedArrowGroup::Sort()
{
	std::sort(mapArrows.begin(), mapArrows.end(), [](MapArrow* a, MapArrow* b) {

		CenterRedArrow* arrowA = static_cast<CenterRedArrow*>(a);
		CenterRedArrow* arrowB = static_cast<CenterRedArrow*>(b);

		return arrowA->GetOrder() < arrowB->GetOrder();
		});

}

void CenterRedArrowGroup::ActivateRight()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.back());
	arrow->Activate();
}

void CenterRedArrowGroup::DeactivateRight()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.back());
	arrow->Desactivate();
}

void CenterRedArrowGroup::TwinkleRight()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.back());
	arrow->Twinkle();
}

void CenterRedArrowGroup::ActivateMid()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows[1]);
	arrow->Activate();
}

void CenterRedArrowGroup::DeactivateMid()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows[mapArrows.size() / 2]);
	arrow->Desactivate();
}

void CenterRedArrowGroup::TwinkleMid()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows[mapArrows.size() / 2]);
	arrow->Twinkle();
}

void CenterRedArrowGroup::ActivateLeft()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.front());
	arrow->Activate();
}

void CenterRedArrowGroup::DeactivateLeft()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.front());
	arrow->Desactivate();
}

void CenterRedArrowGroup::TwinkleLeft()
{
	CenterRedArrow* arrow = static_cast<CenterRedArrow*>(mapArrows.front());
	arrow->Twinkle();
}

void CenterRedArrowGroup::OnAllActive()
{
	//nothing
}
