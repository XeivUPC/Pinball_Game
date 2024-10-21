#include "Globals.h"
#include "raylib.h"
#include "Timer.h"
#include "ModuleGame.h"

class CreditsScene : public ModuleGame {
private:

	Timer delay;

	float opacity;

	Texture2D* texture_credits_EU;
	Texture2D* texture_credits_NA;
	Texture2D* texture_credits_JAPAN;

	Texture2D* texture_credits;

	enum class language {
		NA,
		EU,
		JAPAN
	};
public:

	CreditsScene(Application* app, bool start_enabled = true);
	~CreditsScene();

	bool Start();
	update_status Update();
	bool CleanUp();

	language language;

};