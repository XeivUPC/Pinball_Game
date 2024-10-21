#include "Globals.h"
#include "raylib.h"
#include "Timer.h"
#include "ModuleGame.h"

class CreditsScene : public ModuleGame {
private:

	Timer delay;

	float opacity;

	Texture2D* texture_credits;

	enum class language {
		JAPAN,
		NA,
		EU
	};
public:

	CreditsScene(Application* app, bool start_enabled = true);
	~CreditsScene();

	bool Start();
	update_status Update();
	bool CleanUp();

	language language;

};