#ifndef _HELPERS_HPP
#define _HELPERS_HPP

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, unsigned int* out_texture, int* out_width, int* out_height);

void defaultPNGFilename(char string[22]);

#endif
