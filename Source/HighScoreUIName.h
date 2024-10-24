#pragma once
#include "UI.h"

class Application;

class HighScoreUIName : public UI
{
private:
	Application* App;
	Texture* UITexture;
	bool enabled = true;
public:
	HighScoreUIName(Application* App);
	~HighScoreUIName();
	void Update()const;
};