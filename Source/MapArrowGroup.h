#pragma once
#include "MapObject.h"
#include "MapArrow.h"
#include <vector>

class MapArrowGroup : public MapObject {
private:
public:
	MapArrowGroup(ModuleGame* gameAt);
	~MapArrowGroup() = 0;

	update_status Update();
	bool CleanUp() override;

	void AddArrow(MapArrow* arrow);
	void RemoveArrow(MapArrow* arrow);

	void ActivateAll();
	void DesactivateAll();
	void SwitchAllActiveStatus();

	bool AllActive();
	int GetActiveAmount();

protected:
	virtual void OnAllActive() = 0;
	std::vector<MapArrow*> mapArrows;
};