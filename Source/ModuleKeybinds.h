#include "ModuleScene.h"

class ModuleKeybinds : public ModuleScene {
private:

	int selectedLanguage=-1;

	Texture* background_texture = nullptr;
	int audioSelectId=-1;

public:

	ModuleKeybinds(Application* app, bool start_enabled = true);
	~ModuleKeybinds();

	bool Start();
	update_status Update();
	bool CleanUp();

};