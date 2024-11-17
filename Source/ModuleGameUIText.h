#pragma once
#include "ModuleText.h"
#include "raylib.h"
#include <vector>

class ModuleGameUIText : public ModuleText
{
private:
	Texture2D* fontTexture = NULL;
	Vector2 size = {0,0};
	Vector2 count = {0,0};
	std::vector<int> charReferences;
	Rectangle GetCharRect(char c);
public:
	ModuleGameUIText(Application* app, bool start_enabled = true);

	virtual ~ModuleGameUIText();

	bool Init()override;

	bool Start();

	bool CleanUp()override;

	void Write(const char* text, int x, int y);
};