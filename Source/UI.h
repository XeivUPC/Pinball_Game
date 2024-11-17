#pragma once
#include "raylib.h"

class Application;

class UI
{
protected:
	Application* App;
	bool enabled = true;

private:
	Texture* UITexture;
public:
	UI(Application* App);
	~UI();
	void ChangeVisibility();
	void Render()const;
};