#pragma once
#include "raylib.h"

class Application;

class UI
{
private:
	Application* App;
	Texture* UITexture;
	bool enabled = true;
public:
	UI(Application* App);
	~UI();
	void ChangeVisibility();
	void Update()const;
};