#include "ModuleScene.h"

class ModuleKeybinds : public ModuleScene {
private:

	int selectedLanguage;

	Texture* background_texture;
	

public:

	ModuleKeybinds(Application* app, bool start_enabled = true);
	~ModuleKeybinds();

	bool Start();
	update_status Update();
	bool CleanUp();

};