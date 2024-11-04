#include "Globals.h"
#include "raylib.h"
#include "Timer.h"
#include "ModuleScene.h"

class ModuleCredits : public ModuleScene {
private:

	Timer delay;
	Texture2D* texture_credits=nullptr;

public:

	ModuleCredits(Application* app, bool start_enabled = true);
	~ModuleCredits();

	bool Start();
	update_status Update();
	bool CleanUp();

	int language=-1;

};