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
	void ActivateRightBot();

	void ActivateMid();
	void ActivateMidTop();
	void ActivateMidBot();

	void ActivateLeft();
	void ActivateLeftTop();
	void ActivateLeftBot();

protected:
	void OnAllActive() override;
};

