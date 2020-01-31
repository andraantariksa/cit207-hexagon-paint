#pragma once

#include <ctime>

#include <SFML/OpenGL.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

#include "../lib/tinyfiledialogs/tinyfiledialogs.c"

#include "../lib/lodepng/lodepng.h"

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, unsigned int* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

void defaultPNGFilename(char string[22])
{
    std::time_t now = std::time(nullptr);
    std::tm* time_s = std::localtime(&now);
    std::sprintf(string, "%d-%d-%d-%d-%d-%d.png",
        time_s->tm_year + 1900,
        time_s->tm_mon + 1, time_s->tm_mday, time_s->tm_hour + 1, time_s->tm_min + 1, time_s->tm_sec + 1);
}