#pragma once
#include "ModuleText.h"
#include "raylib.h"
#include <vector>

class ModuleHSNum : public ModuleText
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size = { 0,0 };
	Vector2 count = { 0,0 };
	std::vector<int> charReferences;
	Rectangle* GetCharRect(char c, int color, int position, bool coma);
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
	/// <summary>
	/// For color: Red = 0, Blue 1 \ For position: 1 to 5
	/// </summary>
	/// <param name="text"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="color"></param>
	/// <param name="position"></param>
	/// <param name="coma"></param>
	void Write(const char* text, int x, int y, int color, int position);
};