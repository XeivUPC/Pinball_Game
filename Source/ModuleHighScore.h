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

	struct Score {
		std::string score;
		std::string name;
	};

	ModuleHighScore(Application* app, bool start_enabled = true);
	~ModuleHighScore();

	bool Start();
	update_status Update();
	bool CleanUp();

	/// <summary>
	/// Sets the version's color to Red = 0 or Blue = 1
	/// </summary>
	/// <param name="id"></param>
	void SetVersionColor(int id) {
		if (id < 2 && id > -1) versionColor = id;
	}

private:

	Texture* arrow_texture;
	Animator* arrow_animator;

	Texture* background_texture;

	Timer arrowTimer;
	Timer textTimer;

	int selectedLanguage;
	int versionColor = 0;
	// Red = 0, Blue = 1

	int audioSelectId;

	void LoadHighScore();
	void SaveHighScore();

	void LoadHighScoreFile();
	void SaveConfigFile();
	xml_document highScoreFile;

	std::unordered_map<Position, Score> scores;

	int times_num_offset = 0;

	//provisional, when game returns a score, erase this
	double incoming_score = 300000000;

	void TryToInsertHighScore(double points);
	void ChangeName(std::string name);

	void DrawText();

	bool score_was_inserted = true;
	int score_position;
	int current_char_pos = 0;
	char current_char = 65;
	std::string savedName;
};