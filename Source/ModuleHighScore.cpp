
#include "ModuleHighScore.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleLevelSelection.h"
#include "ModuleMainMenu.h"
#include "ModuleHSNum.h"
#include "ModuleHSName.h"



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

	//App->audio->PlayMusic("Assets/Music/Tiitle_Screen.wav", 0.3f);

	//audioSelectId = App->audio->LoadFx("Assets/SFX/Select.ogg");

	LoadHighScoreFile();
	LoadHighScore();

	StartFadeOut(WHITE, 0.3f);

	return ret;
}

update_status ModuleHighScore::Update()
{

	/*if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		scores[FIRST].score = 777777777;
		scores[FIRST].name = "???";
		SaveHighScore();
	}*/

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		//Return
		//App->audio->PlayFx(audioSelectId);
		StartFadeIn(App->scene_mainMenu, WHITE, 0.3f);
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

	App->text_highScoreNum->Write(scores[FIRST].score, 80, 16, versionColor, 1);
	App->text_highScoreNum->Write(scores[SECOND].score, 80, 16 + 24 * 1, versionColor, 2);
	App->text_highScoreNum->Write(scores[THIRD].score, 80, 16 + 24 * 2, versionColor, 3);
	App->text_highScoreNum->Write(scores[FOURTH].score, 80, 16 + 24 * 3, versionColor, 4);
	App->text_highScoreNum->Write(scores[FIFTH].score, 80, 16 + 24 * 4, versionColor, 5);

	App->text_highScoreName->Write(scores[FIRST].name, 24, 16, versionColor);
	App->text_highScoreName->Write(scores[SECOND].name, 24, 16 + 24 * 1, versionColor);
	App->text_highScoreName->Write(scores[THIRD].name, 24, 16 + 24 * 2, versionColor);
	App->text_highScoreName->Write(scores[FOURTH].name, 24, 16 + 24 * 3, versionColor);
	App->text_highScoreName->Write(scores[FIFTH].name, 24, 16 + 24 * 4, versionColor);

	arrow_animator->Animate(141 - (141*versionColor), 125, versionColor);


	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;

}

bool ModuleHighScore::CleanUp()
{
	if (arrow_animator != nullptr) {
		delete arrow_animator;
		arrow_animator = nullptr;
	}

	LOG("Unloading High Score scene");
	return true;
}

void ModuleHighScore::LoadHighScore()
{
	xml_node positionNode = highScoreFile.child("highscore").child("positions");

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
	xml_node positionNode = highScoreFile.child("highscore").child("positions");

	positionNode.child("first").attribute("score").set_value(scores[FIRST].score);
	positionNode.child("first").attribute("name").set_value(scores[FIRST].name);
	positionNode.child("second").attribute("score").set_value(scores[SECOND].score);
	positionNode.child("second").attribute("name").set_value(scores[SECOND].name);
	positionNode.child("third").attribute("score").set_value(scores[THIRD].score);
	positionNode.child("third").attribute("name").set_value(scores[THIRD].name);
	positionNode.child("fourth").attribute("score").set_value(scores[FOURTH].score);
	positionNode.child("fourth").attribute("name").set_value(scores[FOURTH].name);
	positionNode.child("fifth").attribute("score").set_value(scores[FIFTH].score);
	positionNode.child("fifth").attribute("name").set_value(scores[FIFTH].name);

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
