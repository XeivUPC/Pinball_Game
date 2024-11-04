#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "Timer.h"


class ModuleMainMenu : public ModuleScene {
private:

	int currentButton = 0;

	Texture* pokeball_texture = nullptr;
	Animator* pokeball_animator = nullptr;

	Texture* background_texture = nullptr;
	Animator* background_animator = nullptr;

	Timer blinkTimer;

	int selectedLanguage=-1;

	int audioSelectId=-1;
	int audioMoveId=-1;
	int audioStartGameId=-1;


	Timer scrollMenuTimer;
	float scrollMenuTimeMS=0.2f;


public:

	ModuleMainMenu(Application* app, bool start_enabled = true);
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

};