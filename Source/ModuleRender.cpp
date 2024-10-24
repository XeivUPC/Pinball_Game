#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = RAYWHITE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;

	return ret;
}

bool ModuleRender::Start()
{
    return true;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    ClearBackground(background);
   
    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    BeginDrawing();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    DrawFPS(10, 10);

    EndDrawing();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
	background = color;
}

// Draw to screen
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, Color tint,bool flip, double angle, float pivot_x, float pivot_y) const
{
	bool ret = true;

    float flipValue = flip ? -1 : 1;

	float scale = SCREEN_SIZE;

    Vector2 position = { (float)x, (float)y };

    position.x = (x-pivot_x) * scale + camera.x;
    position.y = (y-pivot_y) * scale + camera.y;

    DrawTexturePro(texture, *section, {x*scale, y*scale, section->width*scale * flipValue, section->height * scale }, {pivot_x,pivot_y},angle, tint);

	return ret;
}

bool ModuleRender::DrawText(const char * text, int x, int y, Font font, int spacing, Color tint) const
{
    bool ret = true;

    Vector2 position = { (float)x, (float)y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);

    return ret;
}

bool ModuleRender::DrawRect(int x, int y, int width, int height, Color color)
{
    bool ret = true;

    float scale = SCREEN_SIZE;
    Vector2 position = { (float)x, (float)y };

    position.x = (x) * scale + camera.x;
    position.y = (y) * scale + camera.y;

    Rectangle rect = { position.x, position.y, width * scale, height * scale };

    DrawRectangle(rect.x,rect.y, rect.width, rect.height, color);
    return ret;
}
