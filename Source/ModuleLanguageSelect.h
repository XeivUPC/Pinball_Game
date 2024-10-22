#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "ModuleUserPreferences.h"


class ModuleLanguageSelect : public ModuleScene {
private:

	int currentButton = 0;

	Texture* background_texture;
	Texture* arrow_texture;

public:

	ModuleLanguageSelect(Application* app, bool start_enabled = true);
	~ModuleLanguageSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

};