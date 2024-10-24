#include "ModuleScene.h"
#include "ModuleMainMenu.h"
#include "AnimationSystem.h"
#include "Timer.h"


class ModuleSaveGame : public ModuleMainMenu {
private:

	int currentButton = 0;

	Texture* pokeball_texture;
	Animator* pokeball_animator;

	Texture* background_texture;
	Animator* background_animator;

	Timer blinkTimer;

	int selectedLanguage;

	int audioSelectId;
	int audioMoveId;
	int audioStartGameId;


	Timer scrollMenuTimer;
	float scrollMenuTimeMS = 0.2f;


public:

	ModuleSaveGame(Application* app, bool start_enabled = true);
	~ModuleSaveGame();

	bool Start();
	update_status Update();
	bool CleanUp();

	void LoadGame();
	void SaveGame();

};