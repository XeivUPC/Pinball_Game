#pragma once
#include "Module.h"
#include "Globals.h"

#include <limits.h>

class ModuleRender : public Module
{
public:
	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

    void SetBackgroundColor(Color color);
	bool Draw(Texture2D texture, int x, int y, const Rectangle* section = NULL, Color tint = WHITE, bool flip=false,double angle = 0, float pivot_x = 0, float pivot_y = 0) const;
    bool DrawText(const char* text, int x, int y, Font font, int spacing, Color tint) const;

	bool DrawRect(int x, int y, int width, int height, Color color = WHITE);

public:

	Color background;
    Camera2D camera;
};