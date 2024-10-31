
#include "ModuleHighScore.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleLevelSelection.h"
#include "ModuleMainMenu.h"
#include "ModuleHSNum.h"
#include "ModuleHSName.h"

#include "cmath"
#include <sstream>
#include <iostream>


ModuleHighScore::ModuleHighScore(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModuleHighScore::~ModuleHighScore()
{

}

bool ModuleHighScore::Start()
{
	LOG("Loading High Score assets");
	bool ret = true;

	//versionColor = /* Get the version's color of the game that scored a high score (example blue) */ 1;

	selectedLanguage = App->userPreferences->GetLanguage();

	if (selectedLanguage > 0) {
		selectedLanguage--;
	}

	App->texture->CreateTexture("Assets/high_score_background.png", "high_score_background");
	background_texture = App->texture->GetTexture("high_score_background");

	App->texture->CreateTexture("Assets/high_score_arrow.png", "high_score_arrow");
	arrow_texture = App->texture->GetTexture("high_score_arrow");

	arrow_animator = new Animator(App);

	AnimationData arrowIdle = AnimationData("Idle");
	arrowIdle.AddSprite(Sprite{ arrow_texture,{0, 0}, {20,10} });
	arrow_animator->AddAnimation(arrowIdle);
	arrow_animator->SetSpeed(0.1);
	arrow_animator->SelectAnimation("Idle", true);

	AnimationData arrowAnim = AnimationData("Forward");
	arrowAnim.AddSprite(Sprite{ arrow_texture,{1, 0}, {20,10} });
	arrowAnim.AddSprite(Sprite{ arrow_texture,{2, 0}, {20,10} });
	arrowAnim.AddSprite(Sprite{ arrow_texture,{3, 0}, {20,10} });
	arrow_animator->AddAnimation(arrowAnim);
	arrow_animator->SetSpeed(0.1);

	arrowTimer.Start();

	textTimer.Start();

	App->audio->PlayMusic("Assets/Music/HighScore_Screen.wav", 0.3f);

	audioSelectId = App->audio->LoadFx("Assets/SFX/Menu_Option_Select.ogg");

	score_was_inserted = true;

	LoadHighScoreFile();

	//provisional, when game returns a score, input it here
	TryToInsertHighScore(incoming_score);

	LoadHighScore();

	StartFadeOut(WHITE, 0.3f);

	std::string savedName(1, current_char);

	ChangeName(savedName);

	return ret;
}

update_status ModuleHighScore::Update()
{
	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT)) && !score_was_inserted) {
		//App->audio->PlayFx(audioSelectId);
		StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
	}

	if (score_was_inserted) {

		if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
			current_char++;
			if (current_char == 111) {
				current_char = 65;
			}
			savedName[current_char_pos] = current_char;
			ChangeName(savedName);
		}
		if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
			current_char--;
			if (current_char == 64) {
				current_char = 110;
			}
			savedName[current_char_pos] = current_char;
			ChangeName(savedName);
		}
		if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
			savedName += current_char;
			current_char_pos++;
			current_char = 65;
			savedName[current_char_pos] = current_char;
			if (current_char_pos == 3) {
				score_was_inserted = false;
			}
			else {
				ChangeName(savedName);
			}
		}
	}

	Rectangle rectBackground = { 0 + 160 * versionColor,0 + 144 * selectedLanguage,160 + 160 * versionColor,144 + 144 * selectedLanguage };

	App->renderer->Draw(*background_texture, 0, 0, &rectBackground, WHITE);

	arrow_animator->Update();

	if (arrowTimer.ReadSec() < 1) {
		arrow_animator->SelectAnimation("Idle", false);
	}
	else if (arrowTimer.ReadSec() >= 1 && arrowTimer.ReadSec() <= 1.3) {
		arrow_animator->SelectAnimation("Forward", false);
	}
	else if (arrowTimer.ReadSec() > 1.3) {
		arrowTimer.Start();
	}

	App->text_highScoreNum->Write(scores[FIRST].score.c_str(), 153 - scores[FIRST].score.length() * 8, 16, versionColor, 1);
	App->text_highScoreNum->Write(scores[SECOND].score.c_str(), 153 - scores[SECOND].score.length() * 8, 16 + 24 * 1, versionColor, 2);
	App->text_highScoreNum->Write(scores[THIRD].score.c_str(), 153 - scores[THIRD].score.length() * 8, 16 + 24 * 2, versionColor, 3);
	App->text_highScoreNum->Write(scores[FOURTH].score.c_str(), 153 - scores[FOURTH].score.length() * 8, 16 + 24 * 3, versionColor, 4);
	App->text_highScoreNum->Write(scores[FIFTH].score.c_str(), 153 - scores[FIFTH].score.length() * 8, 16 + 24 * 4, versionColor, 5);

	DrawText();

	if (!score_was_inserted) {
		arrow_animator->Animate(141 - (141*versionColor), 125, versionColor);
	}

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;

}

bool ModuleHighScore::CleanUp()
{
	if (arrow_animator != nullptr) {
		delete arrow_animator;
		arrow_animator = nullptr;
	}
	highScoreFile.reset();
	LOG("Unloading High Score scene");
	return true;
}

void ModuleHighScore::LoadHighScore()
{
	xml_node positionNode;
	if (versionColor == 0) {
		positionNode = highScoreFile.child("highscore").child("positions").child("red");
	}
	else {
		positionNode = highScoreFile.child("highscore").child("positions").child("blue");
	}

	scores[FIRST].score = positionNode.child("first").attribute("score").as_string();
	scores[FIRST].name = positionNode.child("first").attribute("name").as_string();
	scores[SECOND].score = positionNode.child("second").attribute("score").as_string();
	scores[SECOND].name = positionNode.child("second").attribute("name").as_string();
	scores[THIRD].score = positionNode.child("third").attribute("score").as_string();
	scores[THIRD].name = positionNode.child("third").attribute("name").as_string();
	scores[FOURTH].score = positionNode.child("fourth").attribute("score").as_string();
	scores[FOURTH].name = positionNode.child("fourth").attribute("name").as_string();
	scores[FIFTH].score = positionNode.child("fifth").attribute("score").as_string();
	scores[FIFTH].name = positionNode.child("fifth").attribute("name").as_string();
	
}

void ModuleHighScore::SaveHighScore()
{
	xml_node positionNode;
	if (versionColor == 0) {
		positionNode = highScoreFile.child("highscore").child("positions").child("red");
	}
	else {
		positionNode = highScoreFile.child("highscore").child("positions").child("blue");
	}

	positionNode.child("first").attribute("score").set_value(scores[FIRST].score.c_str());
	positionNode.child("first").attribute("name").set_value(scores[FIRST].name.c_str());
	positionNode.child("second").attribute("score").set_value(scores[SECOND].score.c_str());
	positionNode.child("second").attribute("name").set_value(scores[SECOND].name.c_str());
	positionNode.child("third").attribute("score").set_value(scores[THIRD].score.c_str());
	positionNode.child("third").attribute("name").set_value(scores[THIRD].name.c_str());
	positionNode.child("fourth").attribute("score").set_value(scores[FOURTH].score.c_str());
	positionNode.child("fourth").attribute("name").set_value(scores[FOURTH].name.c_str());
	positionNode.child("fifth").attribute("score").set_value(scores[FIFTH].score.c_str());
	positionNode.child("fifth").attribute("name").set_value(scores[FIFTH].name.c_str());

	SaveConfigFile();
}

void ModuleHighScore::LoadHighScoreFile()
{
	pugi::xml_parse_result result = highScoreFile.load_file("Assets/Preferences/HighScore.xml");
	if (result)
	{
		LOG("HighScore.xml parsed without errors");
	}
	else
	{
		LOG("Error loading HighScore.xml: %s", result.description());
	}
}

void ModuleHighScore::SaveConfigFile()
{
	highScoreFile.save_file("Assets/Preferences/HighScore.xml");
}

void ModuleHighScore::TryToInsertHighScore(double points)
{
	xml_node positionNode;
	if (versionColor == 0) {
		positionNode = highScoreFile.child("highscore").child("positions").child("red");
	}
	else {
		positionNode = highScoreFile.child("highscore").child("positions").child("blue");
	}

	std::stringstream ss;
	ss << static_cast<long long>(points);

	std::string points_str = ss.str();  // Convertimos el stream a string

	std::cout << points_str << std::endl;

	if (points > positionNode.child("first").attribute("score").as_int()) {
		scores[FIRST].score = points_str;

		scores[SECOND].score = positionNode.child("first").attribute("score").as_string();
		scores[SECOND].name = positionNode.child("first").attribute("name").as_string();
		scores[THIRD].score = positionNode.child("second").attribute("score").as_string();
		scores[THIRD].name = positionNode.child("second").attribute("name").as_string();
		scores[FOURTH].score = positionNode.child("third").attribute("score").as_string();
		scores[FOURTH].name = positionNode.child("third").attribute("name").as_string();
		scores[FIFTH].score = positionNode.child("fourth").attribute("score").as_string();
		scores[FIFTH].name = positionNode.child("fourth").attribute("name").as_string();
		score_position = 1;
	}
	else if (points > positionNode.child("second").attribute("score").as_int()) {
		scores[FIRST].score = positionNode.child("first").attribute("score").as_string();
		scores[FIRST].name = positionNode.child("first").attribute("name").as_string();
		scores[SECOND].score = points_str;

		scores[THIRD].score = positionNode.child("second").attribute("score").as_string();
		scores[THIRD].name = positionNode.child("second").attribute("name").as_string();
		scores[FOURTH].score = positionNode.child("third").attribute("score").as_string();
		scores[FOURTH].name = positionNode.child("third").attribute("name").as_string();
		scores[FIFTH].score = positionNode.child("fourth").attribute("score").as_string();
		scores[FIFTH].name = positionNode.child("fourth").attribute("name").as_string();
		score_position = 2;
	}
	else if (points > positionNode.child("third").attribute("score").as_int()) {
		scores[FIRST].score = positionNode.child("first").attribute("score").as_string();
		scores[FIRST].name = positionNode.child("first").attribute("name").as_string();
		scores[SECOND].score = positionNode.child("second").attribute("score").as_string();
		scores[SECOND].name = positionNode.child("second").attribute("name").as_string();
		scores[THIRD].score = points_str;

		scores[FOURTH].score = positionNode.child("third").attribute("score").as_string();
		scores[FOURTH].name = positionNode.child("third").attribute("name").as_string();
		scores[FIFTH].score = positionNode.child("fourth").attribute("score").as_string();
		scores[FIFTH].name = positionNode.child("fourth").attribute("name").as_string();
		score_position = 3;
	}
	else if (points > positionNode.child("fourth").attribute("score").as_int()) {
		scores[FIRST].score = positionNode.child("first").attribute("score").as_string();
		scores[FIRST].name = positionNode.child("first").attribute("name").as_string();
		scores[SECOND].score = positionNode.child("second").attribute("score").as_string();
		scores[SECOND].name = positionNode.child("second").attribute("name").as_string();
		scores[THIRD].score = positionNode.child("third").attribute("score").as_string();
		scores[THIRD].name = positionNode.child("third").attribute("name").as_string();
		scores[FOURTH].score = points_str;

		scores[FIFTH].score = positionNode.child("fourth").attribute("score").as_string();
		scores[FIFTH].name = positionNode.child("fourth").attribute("name").as_string();
		score_position = 4;
	}
	else if (points > positionNode.child("fifth").attribute("score").as_int()) {
		scores[FIRST].score = positionNode.child("first").attribute("score").as_string();
		scores[FIRST].name = positionNode.child("first").attribute("name").as_string();
		scores[SECOND].score = positionNode.child("second").attribute("score").as_string();
		scores[SECOND].name = positionNode.child("second").attribute("name").as_string();
		scores[THIRD].score = positionNode.child("third").attribute("score").as_string();
		scores[THIRD].name = positionNode.child("third").attribute("name").as_string();
		scores[FOURTH].score = positionNode.child("fourth").attribute("score").as_string();
		scores[FOURTH].name = positionNode.child("fourth").attribute("name").as_string();
		scores[FIFTH].score = points_str;

		score_position = 5;
	}
	else {
		LoadHighScore();
		score_was_inserted = false;
	}
	SaveHighScore();
}

void ModuleHighScore::ChangeName(std::string name)
{
	switch (score_position)
	{
	case 1:
		scores[FIRST].name = name.c_str();
		break;
	case 2:
		scores[SECOND].name = name.c_str();
		break;
	case 3:
		scores[THIRD].name = name.c_str();
		break;
	case 4:
		scores[FOURTH].name = name.c_str();
		break;
	case 5:
		scores[FIFTH].name = name.c_str();
		break;
	default:
		break;
	}

	SaveHighScore();
}

void ModuleHighScore::DrawText()
{
	if (score_was_inserted) {
		switch (score_position)
		{
		case 1:
			if (textTimer.ReadSec() < 0.6) {
				App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
			}
			else if (textTimer.ReadSec() >= 0.75) {
				textTimer.Start();
			}
			App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
			App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
			App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
			App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
			break;
		case 2:
			App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
			if (textTimer.ReadSec() < 0.5) {
				App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
			}
			else if (textTimer.ReadSec() >= 1) {
				textTimer.Start();
			}
			App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
			App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
			App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
			break;
		case 3:
			App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
			App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
			if (textTimer.ReadSec() < 0.5) {
			App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
			}
			else if (textTimer.ReadSec() >= 1) {
				textTimer.Start();
			}
			App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
			App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
			break;
		case 4:
			App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
			App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
			App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
			if (textTimer.ReadSec() < 0.5) {
				App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
			}
			else if (textTimer.ReadSec() >= 1) {
				textTimer.Start();
			}
			App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
			break;
		case 5:
			App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
			App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
			App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
			App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
			if (textTimer.ReadSec() < 0.5) {
				App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
			}
			else if (textTimer.ReadSec() >= 1) {
				textTimer.Start();
			}
			break;
		default:
			break;
		}		
	}
	else {
		App->text_highScoreName->Write(scores[FIRST].name.c_str(), 24, 16, versionColor);
		App->text_highScoreName->Write(scores[SECOND].name.c_str(), 24, 16 + 24 * 1, versionColor);
		App->text_highScoreName->Write(scores[THIRD].name.c_str(), 24, 16 + 24 * 2, versionColor);
		App->text_highScoreName->Write(scores[FOURTH].name.c_str(), 24, 16 + 24 * 3, versionColor);
		App->text_highScoreName->Write(scores[FIFTH].name.c_str(), 24, 16 + 24 * 4, versionColor);
	}

}
