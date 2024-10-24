#pragma once
#include "ModuleText.h"
#include "raylib.h"
#include <vector>

class ModuleHSName : public ModuleText
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size;
	Vector2 count;
	std::vector<int> charReferences;
	Rectangle* GetCharRect(char c, int color);
public:
	ModuleHSName(Application* app, bool start_enabled = true);

	virtual ~ModuleHSName();

	bool Init()override;

	bool Start();

	update_status PreUpdate()override;
	update_status Update()override;
	update_status PostUpdate()override;

	bool CleanUp()override;
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB)override;
	/// <summary>
	/// for color: Red = 0, Blue 1
	/// </summary>
	/// <param name="text"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="color"></param>
	void Write(const char* text, int x, int y, int color);
};