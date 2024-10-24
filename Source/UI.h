#pragma once
#include "raylib.h"

class Application;

class UI
{
protected:
	Application* App;

private:
	Texture* UITexture;
	bool enabled = true;
public:
	UI(Application* App);
	~UI();
	void ChangeVisibility();
	void Render()const;
};