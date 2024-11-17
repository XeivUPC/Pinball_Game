#pragma once
#include "ModuleText.h"
#include "raylib.h"
#include <vector>

class ModuleTimerUIText : public ModuleText
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size = { 0,0 };
	Vector2 count = { 0,0 };
	std::vector<int> charReferences;
	Rectangle GetCharRect(char c);
public:
	ModuleTimerUIText(Application* app, bool start_enabled = true);

	virtual ~ModuleTimerUIText();

	bool Init()override;

	bool Start();

	bool CleanUp()override;

	void Write(const char* text, int x, int y);
};