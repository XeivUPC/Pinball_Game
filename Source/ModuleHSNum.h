#pragma once
#include "ModuleText.h"
#include "raylib.h"
#include <vector>

class ModuleHSNum : public ModuleText
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size;
	Vector2 count;
	std::vector<int> charReferences;
	Rectangle* GetCharRect(char c, int color, bool coma);
public:
	ModuleHSNum(Application* app, bool start_enabled = true);

	virtual ~ModuleHSNum();

	bool Init()override;

	bool Start();

	update_status PreUpdate()override;
	update_status Update()override;
	update_status PostUpdate()override;

	bool CleanUp()override;
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB)override;
	void Write(const char* text, int x, int y, int color, bool coma);
};