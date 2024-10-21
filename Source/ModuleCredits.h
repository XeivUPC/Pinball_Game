#include "Globals.h"
#include "raylib.h"
#include "Timer.h"
#include "ModuleGame.h"

class ModuleCredits : public ModuleGame {
private:

	Timer delay;

	float colorFadeOpacity=255;
	float backgroundOpacity =255;

	Texture2D* texture_credits;

public:

	ModuleCredits(Application* app, bool start_enabled = true);
	~ModuleCredits();

	bool Start();
	update_status Update();
	bool CleanUp();

	int language;

};