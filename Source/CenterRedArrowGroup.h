#pragma once
#include "CenterRedArrow.h"
#include "MapArrowGroup.h"

class CenterRedArrowGroup : public MapArrowGroup {
public:
	CenterRedArrowGroup(ModuleGame* gameAt);
	~CenterRedArrowGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

	void ActivateRight();
	void DeactivateRight();
	void TwinkleRight();

	void ActivateMid();
	void DeactivateMid();
	void TwinkleMid();

	void ActivateLeft();
	void DeactivateLeft();
	void TwinkleLeft();

protected:
	void OnAllActive() override;
};

