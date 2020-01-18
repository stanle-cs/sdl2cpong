#include "draw.h"

//Prepare the scene: set background and clear it
void prepScene() {
	SDL_RenderClear(app.renderer);
}

//update the scene, or in other word, present it
void updateScene() {
    SDL_RenderPresent(app.renderer);
}

//load the image using a filename
SDL_Texture* loadTexture(char *filename)
{
	SDL_Texture* texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

//blit the texture at (x,y) of the current texture onto the renderer
void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;

	//query the width and height of the texture and store then into dest.w and dest.h
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

//print a message onto the surface
void printMessage(char* string) {
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Printing message: opening font");
	TTF_Font * font = TTF_OpenFont("ARIAL.TTF", 25);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Printing message: setting color");
	SDL_Color color = { 255, 255, 255 };

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Printing message: creating renderText_Solid");
	SDL_Surface * textSurface = TTF_RenderText_Solid(font, "Hello world", color);

	if (textSurface == NULL) {
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Printing message: cannot create Text");
	} else {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Printing message: create texture from surface");
		SDL_Texture * texture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
	
	

		blit(texture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}
	SDL_FreeSurface(textSurface);
}