#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "Timer.h"


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


	Timer scrollMenuTimer;
	float scrollMenuTimeMS=0.2f;


public:

	ModuleMainMenu(Application* app, bool start_enabled = true);
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

};