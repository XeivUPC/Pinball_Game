#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "Timer.h"
#include "ModuleUserPreferences.h"


class ModuleHighScore : public ModuleScene {
public:

	int current_game_score = 0;

	enum Position
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
	};

	ModuleHighScore(Application* app, bool start_enabled = true);
	~ModuleHighScore();

	bool Start();
	update_status Update();
	bool CleanUp();

private:

	Texture* arrow_texture;
	Animator* arrow_animator;

	Texture* background_texture;

	Timer arrowTimer;

	int selectedLanguage;
	int versionColor;
	// Red = 0, Blue = 1

	int audioSelectId;

	void LoadHighScore();
	void SaveHighScore();

	void LoadHighScoreFile();
	xml_document highScoreFile;

	std::unordered_map<Position, int> scores;
};