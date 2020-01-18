#include "common.h"

#include "time.h"

extern void blit(SDL_Texture *texture, int x, int y);
extern SDL_Texture *loadTexture(char *filename);
extern void printMessage(char* string, int size, int x, int y);
extern App app;
extern Stage stage;