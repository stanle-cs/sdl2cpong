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
void printMessage(char* string, int size, int x, int y) {
	
	TTF_Font * font = TTF_OpenFont("ARIAL.TTF", size);

	SDL_Color color = { 255, 255, 255 };

	SDL_Surface * textSurface = TTF_RenderText_Blended(font, string, color);

	if (textSurface == NULL) {
	} else {
		SDL_Texture * texture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
		
		SDL_Rect dest;
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

		//
		const int PADDING_PIXEL = 5;
		if (x + dest.w / 2 > SCREEN_WIDTH) {
			dest.x = SCREEN_WIDTH - dest.w - PADDING_PIXEL;
		} 
		else if (x - dest.w / 2 < 0) {
			dest.x = PADDING_PIXEL;
		}
		else dest.x = x - dest.w / 2;
		
		if (y + dest.h > SCREEN_HEIGHT) {
			dest.y = SCREEN_HEIGHT - dest.h - PADDING_PIXEL;
		} 
		else if (y - dest.h /2 < 0) {
			dest.y = PADDING_PIXEL;
		}
		else dest.y = y - dest.h / 2;

		SDL_RenderCopy(app.renderer, texture, NULL, &dest);

		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}
	SDL_FreeSurface(textSurface);
}