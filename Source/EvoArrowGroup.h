#pragma once
#include "MapArrowGroup.h"
#include "GetEvoArrow.h"

class EvoArrowGroup : public MapArrowGroup {
public:
	EvoArrowGroup(ModuleGame* gameAt);
	~EvoArrowGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();
	void ActivateNext();

protected:
	void OnAllActive() override;
};

