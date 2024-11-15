#pragma once
#include "MapArrow.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

class CenterRedArrow : public MapArrow {
public:
	CenterRedArrow(ModuleGame* gameAt, b2Vec2 position, int order);
	~CenterRedArrow();

	update_status Update();
	bool CleanUp() override;

	void Activate() override;
	void Desactivate() override;
	void Twinkle() override;

	int GetOrder() const;

private:
	int order = -1;
	int type = -1;

	bool active = false;
	bool twinkle = false;

	b2Vec2 position = { 0,0 };

	Texture* texture = nullptr;
	Animator* animator = nullptr;
};

