#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "Timer.h"


class ModuleMainMenu : public ModuleScene {
private:

	int currentButton = 0;
	int currentButton_save_menu = 0;

	Texture* background_texture = nullptr;
	Animator* background_animator = nullptr;

	Texture* pokeball_texture = nullptr;
	Animator* pokeball_animator = nullptr;

	Texture* select_arrow = nullptr;
	Animator* select_arrow_animator = nullptr;

	Texture* main_menu_save = nullptr;
	Animator* main_menu_save_animator = nullptr;

	
	Timer blinkTimer;

	int selectedLanguage = -1;

	int audioSelectId = -1;
	int audioMoveId = -1;
	int audioStartGameId = -1;


	Timer scrollMenuTimer;
	float scrollMenuTimeMS=0.2f;

	Rectangle rect_main_menu_save = { 0,0,0,0 };
	int OffsetX_main_menu_save = 3;
	bool is_in_menu_save = false;

public:

	ModuleMainMenu(Application* app, bool start_enabled = true);
	~ModuleMainMenu();

	

	bool Start();
	update_status Update();
	bool CleanUp();

	void SetIsInMenuSave(bool is_in_menu_save_);
};