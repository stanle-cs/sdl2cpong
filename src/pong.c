#include "pong.h"

static void capFrameRate(long *then, float *remainder);

int main(int argc, char* argv[]) {

    long then;
    float remainder;
    //allocate mem for app (that has window and renderer pointers)
    memset(&app, 0, sizeof(App));

    initSDL();

    atexit(cleanUp);

    initStage();
    
    then = SDL_GetTicks();

    remainder = 0;

    while (1) {

        prepScene();

        processInput();

        app.delegate.logic();

        app.delegate.draw();

        updateScene();

        capFrameRate(&then, &remainder);
    }

    return 0;
}

//delay according to how long it take to draw the scene
static void capFrameRate(long *then, float *remainder) {
    long wait, frameTime;

    wait = 16 + *remainder;

    *remainder -= (int)*remainder;

    frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);
    *remainder += 0.667;
    *then = SDL_GetTicks();
}