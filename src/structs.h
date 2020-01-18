//Represent an abstract structure that does delegation
typedef struct {
	void (*logic) (void) ;
	void (*draw) (void);
} Delegate;

//Represent the window and the canvas
typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
} App;

//Represent objects with coordinate
//forward declaration of it first so we can use its pointer in its own definition. Mindblown!
typedef struct Object Object;
struct Object {
	float x, y, dx, dy;
	int w, h, health;
	//reload is the time needed to load another bullet
	int reload;
	SDL_Texture *texture;
	Object *next;
};



//Represent the stages of the game: for different game we can have different
//stuff here
typedef struct {
	Object *paddle1, *paddle2;
	Object *ball;
} Stage;