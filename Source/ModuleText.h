#pragma once
#include "Module.h"
#include "raylib.h"
#include <vector>

class ModuleText : public Module
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size;
	Vector2 count;
	std::vector<int> charReferences;
	Rectangle* GetCharRect(char c);
public:
	ModuleText(Application* app, bool start_enabled = true);

	virtual ~ModuleText();

	bool Init()override;

	bool Start();

	update_status PreUpdate()override;
	update_status Update()override;
	update_status PostUpdate()override;

	bool CleanUp()override;
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB)override;
	void Write(const char* text, int x, int y, Color color = WHITE);
};