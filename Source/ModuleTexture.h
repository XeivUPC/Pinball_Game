#pragma once
#include <unordered_map>
#include "Module.h"
#include <string>

class ModuleTexture : public Module
{
public:
    ModuleTexture(Application* app, bool start_enabled = true);
    ~ModuleTexture();

    bool CleanUp();

    Texture2D* GetTexture(std::string textureID);
    void CreateTexture(std::string path, std::string textureID);
    void DeleteTexture(std::string textureID);

private:
    bool IsTextureLoaded(std::string textureID);
    std::unordered_map<std::string, Texture2D> textureData;

};

