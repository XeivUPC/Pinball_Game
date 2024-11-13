#pragma once
#include "MapArrowGroup.h"
#include "GetEvoArrow.h"

class GetArrowGroup : public MapArrowGroup {
public:
	GetArrowGroup(ModuleGame* gameAt);
	~GetArrowGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();
	void ActivateNext();

protected:
	void OnAllActive() override;
};

