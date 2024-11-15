#include "MapArrowGroup.h"

MapArrowGroup::MapArrowGroup(ModuleGame* gameAt) : MapObject(gameAt)
{
	gameAt->AddObject(this);
}

MapArrowGroup::~MapArrowGroup()
{

}

update_status MapArrowGroup::Update()
{
	return UPDATE_CONTINUE;
}

bool MapArrowGroup::CleanUp()
{
	mapArrows.clear();
	return true;
}

void MapArrowGroup::AddArrow(MapArrow* arrow)
{
	mapArrows.emplace_back(arrow);
}

void MapArrowGroup::RemoveArrow(MapArrow* arrow)
{
	bool found = false;
	int index = 0;
	for (const auto& arrowPointer : mapArrows)
	{
		if (arrowPointer == arrow) {
			found = true;
			break;
		}
		index++;
	}
	if (found)
		mapArrows.erase(mapArrows.begin() + index);
}

void MapArrowGroup::ActivateAll()
{
	for (const auto& arrowPointer : mapArrows)
	{
		arrowPointer->Activate();
	}
}

void MapArrowGroup::DesactivateAll()
{
	for (const auto& arrowPointer : mapArrows)
	{
		arrowPointer->Desactivate();
	}
}

void MapArrowGroup::SwitchAllActiveStatus()
{
	for (const auto& arrowPointer : mapArrows)
	{
		arrowPointer->SwitchActiveStatus();
	}
}

bool MapArrowGroup::AllActive()
{
	bool allActive = true;
	for (const auto& arrowPointer : mapArrows)
	{
		if (!arrowPointer->IsActive()) {
			allActive = false;
			break;
		}
	}
	return allActive;
}

int MapArrowGroup::GetActiveAmount()
{
	int count = 0;
	for (const auto& arrowPointer : mapArrows)
	{
		if (arrowPointer->IsActive()) {
			count++;
		}
	}
	return count;
}
