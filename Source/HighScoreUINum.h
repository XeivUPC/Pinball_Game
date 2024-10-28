#pragma once
#include "UI.h"

class Application;

class HighScoreUINum : public UI
{
private:
	Application* App;
	Texture* UITexture;
	bool enabled = true;
public:
	HighScoreUINum(Application* App);
	~HighScoreUINum();
	void Update()const;
};