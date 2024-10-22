#include "ModuleLanguageSelect.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleCredits.h"
#include "ModuleUserPreferences.h"

ModuleLanguageSelect::ModuleLanguageSelect(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{


}

ModuleLanguageSelect::~ModuleLanguageSelect()
{

}

bool ModuleLanguageSelect::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	currentButton = 0;

	App->texture->CreateTexture("Assets/language_select_background.png", "language_select_background");
	background_texture = App->texture->GetTexture("language_select_background");

	App->texture->CreateTexture("Assets/language_select_arrow.png", "language_select_arrow");
	arrow_texture = App->texture->GetTexture("language_select_arrow");

	StartFadeOut(WHITE, 0.3f);

	return ret;
}

update_status ModuleLanguageSelect::Update()
{

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::UP))) {
		if (currentButton > 0) {
			currentButton--;
		}
	}
	else if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
		if (currentButton < 5) {
			currentButton++;
		}
	}

	Rectangle rectBackground = { 0,0,160,144 };
	Rectangle rectArrow = { 0,0,8,8 };

	App->renderer->Draw(*background_texture, 0, 0, &rectBackground, WHITE);

	App->renderer->Draw(*arrow_texture, 57, 40 + 12 * currentButton, &rectArrow, WHITE);

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		App->userPreferences->ChangeLanguage((ModuleUserPreferences::AppLanguage)currentButton);
		StartFadeIn(App->scene_credits, WHITE, 0.3f);
	}

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}

bool ModuleLanguageSelect::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}
