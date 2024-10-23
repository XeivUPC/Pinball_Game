#include "ModuleKeybinds.h"
#include "ModuleSettings.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

ModuleKeybinds::ModuleKeybinds(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

}

ModuleKeybinds::~ModuleKeybinds()
{
}

bool ModuleKeybinds::Start()
{
    selectedLanguage = App->userPreferences->GetLanguage();

    App->texture->CreateTexture("Assets/keybinds_menu_background.png", "keybinds_menu_background");
    background_texture = App->texture->GetTexture("keybinds_menu_background");


    StartFadeOut(WHITE, 0.3f);
    return true;
}

update_status ModuleKeybinds::Update()
{

    if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
        StartFadeIn(App->scene_settings, WHITE, 0.3f);
        //App->audio->PlayFx(audioSelectId);

    }


    Rectangle rectBackground = { 0,selectedLanguage * 144,160,144 };
    App->renderer->Draw(*background_texture, 0, 0, &rectBackground, WHITE);


    ModuleScene::FadeUpdate();

    return UPDATE_CONTINUE;
}

bool ModuleKeybinds::CleanUp()
{
    return true;
}
