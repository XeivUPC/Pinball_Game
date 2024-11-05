#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

// Update: draw background
update_status ModuleScene::Update()
{
	

	return UPDATE_CONTINUE;
}


// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");


	return true;
}

void ModuleScene::StartFadeIn(ModuleScene* target, Color color, float time)
{
	if (doingFadeIn)
		return;

	fadeTarget = target;
	fadeColor = color;
	fadeTime = time;
	doingFadeIn = true;
	doingFadeOut = false;
	fadeTimer.Start();
	FadeIn();
}

void ModuleScene::StartFadeOut(Color color, float time)
{
	if (doingFadeOut)
		return;
	fadeTarget = nullptr;
	fadeColor = color;
	fadeTime = time;
	doingFadeOut = true;
	doingFadeIn = false;
	fadeTimer.Start();
	FadeOut();
}

void ModuleScene::FadeUpdate()
{
	EndMode2D();
	if (doingFadeIn)
		FadeIn();
	if (doingFadeOut)
		FadeOut();
	BeginMode2D(App->renderer->camera);
	
}

void ModuleScene::FadeIn()
{
	if (fadeTimer.ReadSec()>= fadeTime) {
		doingFadeIn = false;
		if(fadeTarget!=nullptr)
			fadeTarget->Enable();
		Disable();
	}
	else {
		int opacity = (int)(255 * (fadeTimer.ReadSec() / fadeTime));
		if (opacity > 255)
			opacity = 255;
		Color color = { fadeColor.r,fadeColor.g,fadeColor.b,(unsigned char)opacity };
		DrawRectangle(0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, color);
	}
}

void ModuleScene::FadeOut()
{
	if (fadeTimer.ReadSec() < fadeTime) {
		
		int opacity = 255 - (int)(255 * (fadeTimer.ReadSec() / fadeTime));
		if (opacity< 0)
			opacity = 0;
		Color color = { fadeColor.r,fadeColor.g,fadeColor.b,(unsigned char)opacity };
		DrawRectangle(0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, color);
	}
	else {
		doingFadeOut = false;
	}
}