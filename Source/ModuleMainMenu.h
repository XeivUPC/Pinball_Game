#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "Timer.h"
#include "ModuleUserPreferences.h"


class ModuleMainMenu : public ModuleScene {
private:

	int currentButton = 0;

	Texture* pokeball_texture;
	Animator* pokeball_animator;

	Texture* background_texture;
	Animator* background_animator;

	Timer blinkTimer;

	int selectedLanguage;

	int audioSelectId;


public:

	ModuleMainMenu(Application* app, bool start_enabled = true);
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

};