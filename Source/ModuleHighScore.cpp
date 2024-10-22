
#include "ModuleHighScore.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleLevelSelection.h"



ModuleHighScore::ModuleHighScore(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}

ModuleHighScore::~ModuleHighScore()
{

}

bool ModuleHighScore::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	versionColor = /* Get the version's color of the game that scored a high score (example blue) */ 1;

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

	StartFadeOut(WHITE, 0.3f);

	return ret;
}

update_status ModuleHighScore::Update()
{


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

	arrow_animator->Animate(141 - (141*versionColor), 126, versionColor);

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;

}

bool ModuleHighScore::CleanUp()
{
	if (arrow_animator != nullptr) {
		delete arrow_animator;
		arrow_animator = nullptr;
	}

	LOG("Unloading Intro scene");
	return true;
}

void ModuleHighScore::LoadHighScore()
{
	xml_node positionNode = highScoreFile.child("highscore").child("positions");

	scores[FIRST] = positionNode.child("first").attribute("score").as_int();//, positionNode.child("first").attribute("name").as_string();
	scores[SECOND] = positionNode.child("second").attribute("score").as_int();//, positionNode.child("second").attribute("name").as_string();
	scores[THIRD] = positionNode.child("third").attribute("score").as_int();//, positionNode.child("third").attribute("name").as_string();
	scores[FOURTH] = positionNode.child("fourth").attribute("score").as_int();//, positionNode.child("fourth").attribute("name").as_string();
	scores[FIFTH] = positionNode.child("fifth").attribute("score").as_int();//, positionNode.child("fifth").attribute("name").as_string();
	
}

void ModuleHighScore::SaveHighScore()
{
	xml_node positionNode = highScoreFile.child("highscore").child("positions");

	positionNode.child("first").attribute("score").set_value(scores[FIRST]);
	positionNode.child("second").attribute("score").set_value(scores[SECOND]);
	positionNode.child("third").attribute("score").set_value(scores[THIRD]);
	positionNode.child("fourth").attribute("score").set_value(scores[FOURTH]);
	positionNode.child("fifth").attribute("score").set_value(scores[FIFTH]);

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