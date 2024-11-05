#include "ModuleScene.h"
#include "ModuleMainMenu.h"
#include "AnimationSystem.h"
#include "Timer.h"


class ModuleSaveGame : public ModuleMainMenu {
private:

	int currentButton = 0;

	Texture* select_arrow = nullptr;
	Animator* select_arrow_animator = nullptr;

	Texture* background_texture = nullptr;
	Animator* background_animator = nullptr;

	Timer blinkTimer;

	int selectedLanguage;

	int audioSelectId;
	int audioMoveId;
	int audioStartGameId;


	Timer scrollSaveTimer;
	float scrollSaveTimeMS = 0.2f;


public:

	ModuleSaveGame(Application* app, bool start_enabled = true);
	~ModuleSaveGame();

	bool Start();
	update_status Update();
	bool CleanUp();

	void LoadGame();
	void SaveGame();

};