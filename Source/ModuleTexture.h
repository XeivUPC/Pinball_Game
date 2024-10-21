#pragma once
#include <unordered_map>
#include "Module.h"

class ModuleTexture : public Module
{
public:
    ModuleTexture(Application* app, bool start_enabled = true);
    ~ModuleTexture();

    bool CleanUp();

    Texture2D* GetTexture(const char* textureID);
    void CreateTexture(const char* path, const char* textureID);
    void DeleteTexture(const char* textureID);
private:

    bool IsTextureLoaded(const char* textureID);
    std::unordered_map<const char*, Texture2D> textureData;

};

