#pragma once
#include <unordered_map>
#include "raylib.h"

class TextureManager
{
public:
    static TextureManager& Instance()
    {
        static TextureManager instance; //Guaranteed to be initialized only once
        return instance;
    }
    Texture2D* GetTexture(const char* textureID);
    void CreateTexture(const char* path, const char* textureID);
    void DeleteTexture(const char* textureID);
private:

    //Private constructor to prevent instantiation
    TextureManager();
    //Destructor
    ~TextureManager();
    bool IsTextureLoaded(const char* textureID);
    std::unordered_map<const char*, Texture2D> textureData;

};

