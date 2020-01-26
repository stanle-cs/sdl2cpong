#include "input.h"

//handle keydown event, set the value of the correspond key in the key matrix
void handleKeyDown(SDL_KeyboardEvent* key) {
	if (key->repeat == 0 && key->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[key->keysym.scancode] = 1;
	}
}

//basically reset all that was done during keydown event
void handleKeyUp(SDL_KeyboardEvent* key) {
	if (key->repeat == 0 && key->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[key->keysym.scancode] = 0;
	}
}


//handle input in the input queue
void processInput() {
    //special type event
    SDL_Event event;
    //get event from the queue then handle them accordingly
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            handleKeyDown(&event.key);
            break;

        case SDL_KEYUP:
            handleKeyUp(&event.key);
            break;
            
        default:
            break;
        }
    }
}