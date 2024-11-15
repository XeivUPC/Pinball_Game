#include "CenterBlueArrowGroup.h"
#include "CenterBlueArrow.h"
#include "ModuleUserPreferences.h"
#include "Application.h"
#include <algorithm>

CenterBlueArrowGroup::CenterBlueArrowGroup(ModuleGame* gameAt) : MapArrowGroup(gameAt)
{
	this->gameAt = gameAt;
}

CenterBlueArrowGroup::~CenterBlueArrowGroup()
{

}

update_status CenterBlueArrowGroup::Update()
{
	return UPDATE_CONTINUE;
}

bool CenterBlueArrowGroup::CleanUp()
{

	return true;
}

void CenterBlueArrowGroup::Sort()
{
	std::sort(mapArrows.begin(), mapArrows.end(), [](MapArrow* a, MapArrow* b) {

		CenterBlueArrow* arrowA = static_cast<CenterBlueArrow*>(a);
		CenterBlueArrow* arrowB = static_cast<CenterBlueArrow*>(b);

		return arrowA->GetOrder() < arrowB->GetOrder();
		});

}

void CenterBlueArrowGroup::ActivateRight()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front());
	arrow->Activate();
}

void CenterBlueArrowGroup::ActivateRightTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front());
	arrow->ActivateTop();
	arrow->Twinkle();
}

void CenterBlueArrowGroup::DeactivateRightTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front());
	arrow->DesactivateTop();
}

void CenterBlueArrowGroup::ActivateRightBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front());
	arrow->ActivateBot();
}

void CenterBlueArrowGroup::DeactivateRightBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front());
	arrow->DesactivateBot();
}

void CenterBlueArrowGroup::ActivateMid()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front()+1);
	arrow->Activate();
}

void CenterBlueArrowGroup::ActivateMidTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front()+1);
	arrow->ActivateTop();
}

void CenterBlueArrowGroup::DeactivateMidTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front() + 1);
	arrow->DesactivateTop();
}

void CenterBlueArrowGroup::ActivateMidBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front()+1);
	arrow->ActivateBot();
}

void CenterBlueArrowGroup::DeactivateMidBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.front() + 1);
	arrow->DesactivateBot();
}

void CenterBlueArrowGroup::ActivateLeft()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.back());
	arrow->Activate();
}

void CenterBlueArrowGroup::ActivateLeftTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.back());
	arrow->ActivateTop();
	arrow->Twinkle();
}

void CenterBlueArrowGroup::DeactivateLeftTop()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.back());
	arrow->DesactivateTop();
}

void CenterBlueArrowGroup::ActivateLeftBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.back());
	arrow->ActivateBot();
}

void CenterBlueArrowGroup::DeactivateLeftBot()
{
	CenterBlueArrow* arrow = static_cast<CenterBlueArrow*>(mapArrows.back());
	arrow->DesactivateBot();
}

void CenterBlueArrowGroup::OnAllActive()
{
	//nothing
}

