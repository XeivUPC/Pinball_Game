#include "raylib.h"
#include "Timer.h"

class CreditsScene{
public:

	void PreUpdate();
	void Update();
	void PostUpdate();
	void Render();

	bool CleanUp();

private:

	Timer delay;

	float opacity;

	Texture2D* texture_credits;

	enum class language {
		NA,
		EU,
		JAPAN
	};
};