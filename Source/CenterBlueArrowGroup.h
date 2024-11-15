#pragma once
#include "CenterBlueArrow.h"
#include "MapArrowGroup.h"

class CenterBlueArrowGroup : public MapArrowGroup {
public:
	CenterBlueArrowGroup(ModuleGame* gameAt);
	~CenterBlueArrowGroup();

	update_status Update();
	bool CleanUp() override;

	void Sort();

	void ActivateRight();
	void ActivateRightTop();
	void DeactivateRightTop();
	void ActivateRightBot();
	void DeactivateRightBot();

	void ActivateMid();
	void ActivateMidTop();
	void DeactivateMidTop();
	void ActivateMidBot();
	void DeactivateMidBot();

	void ActivateLeft();
	void ActivateLeftTop();
	void DeactivateLeftTop();
	void ActivateLeftBot();
	void DeactivateLeftBot();

protected:
	void OnAllActive() override;
};

