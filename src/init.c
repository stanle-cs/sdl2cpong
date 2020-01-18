#include "init.h"


//initiate SDL, create a window and a renderer
void initSDL() {
    int rendererFlags, windowFlags, imgFlags;
    
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;
    imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    //initiate SDL stuff. If return < 0 error occured
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initate SDL: %s", SDL_GetError());
        exit(1);
    }

    //create a window
    app.window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (!app.window) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to create window: %s", SDL_GetError());
        exit(1);
    }

    //set hint for SDL
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    //create a renderer
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    if (!app.renderer) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to create renderer: %s", SDL_GetError());
        exit(1);
    }

    //init IMG
    if (IMG_Init(imgFlags) == 0) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to initialize SDL_Image: %s", SDL_GetError());
        exit(1);
    }

    //init TTF
    if (TTF_Init() == -1) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to initialize SDL_ttf: %s", SDL_GetError());
        exit(1);
    } 
    else SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "TTF_Init successfull");
}

//clean up: destroy the renderer and window then quit SDL
void cleanUp() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    IMG_Quit();
    TTF_Quit();
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Exit normally");
    SDL_Quit();
}