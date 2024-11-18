#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = BLACK;
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
    camera = { 0 };
    camera.target = { 0.0f, 0.0f }; // Objetivo a seguir
    camera.offset = { 0.0f, 0.0f };// Centra la cámara
    camera.rotation = 0.0f; // Sin rotación
    camera.zoom = 1.0f; // Zoom por defecto (sin zoom)
    return true;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
    ClearBackground(background);
    BeginDrawing();
    BeginMode2D(camera);
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!

    EndMode2D();
    //DrawFPS(10, 10);
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

    int flipValue = flip ? -1 : 1;

	float scale = SCREEN_SIZE;

    Vector2 position = { (float)x, (float)y };

    position.x = (x-pivot_x) * scale;
    position.y = (y-pivot_y) * scale;

    DrawTexturePro(texture, *section, {x*scale, y*scale, section->width*scale * flipValue, section->height * scale }, {pivot_x,pivot_y},(float)angle, tint);

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

    position.x = (x) * scale;
    position.y = (y) * scale;

    Rectangle rect = { position.x, position.y, width * scale, height * scale };

    DrawRectangle((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, color);
    return ret;
}
