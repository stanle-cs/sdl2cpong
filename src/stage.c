/*
	stage.c create the players and the ball for the pong game. It also
	reset the game whenever the ball reaches the sides.
	it also define the logic of the game, including the behaviors of
	the ball and the player.
	this file can potentially be broken down into smaller pieces.
*/


#include "stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void initBall(void);
static void updatePlayer(void);
static void updateBall(void);
static void drawPaddles(void);
static void drawBall(void);
static SDL_bool checkCollision(Object *collider, Object *collided);
static Object *paddle1, *paddle2, *ball;

//check if two objects collided
SDL_bool checkCollision(Object *objBall, Object *objPaddle) {
	int ax1 = objBall->x;
	int ax2 = objBall->x + objBall->w;
 	int ay1 = objBall->y;
	int ay2 = objBall->y + objBall->h;

	int bx1 = objPaddle->x;
	int bx2 = objPaddle->x + objPaddle->w;
	int by1 = objPaddle->y;
	int by2 = objPaddle->y + objPaddle->h;

	//first corner NW (ax1, ay1)
	if ((ax1 >= bx1 && ax1 <= bx2)&&( ay1 >= by1 && ay1 <= by2)) {
		return SDL_TRUE;
	}
	//NE (ax2, ay1)
	else if ((ax2 >= bx1 && ax2 <= bx2)&&( ay1 >= by1 && ay1 <= by2)) {
		return SDL_TRUE;
	}
	//SW (ax1, ay2)
	else if ((ax1 >= bx1 && ax1 <= bx2)&&( ay2 >= by1 && ay2 <= by2)) {
		return SDL_TRUE;
	}
	//SE (ax2, ay2)
	else if ((ax2 >= bx1 && ax2 <= bx2)&&( ay2 >= by1 && ay2 <= by2)) {
		return SDL_TRUE;
	} 
	else return SDL_FALSE;
}
//Set the stage
void initStage(void)
{
	//I wonder why the delegations happen here?
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	
	//memset a chunk of memory equal to the size of struct Stage to 0
	memset(&stage, 0, sizeof(Stage));
	
	initPlayer();
	initBall();
	
}

//Create player, set texture, add player to player list
static void initPlayer()
{
	//this is basically a calloc call lol
	paddle1 = malloc(sizeof(Object));
	memset(paddle1, 0, sizeof(Object));

	paddle2 = malloc(sizeof(Object));
	memset(paddle2, 0, sizeof(Object));

    stage.paddle1 = paddle1;
	stage.paddle2 = paddle2;

	paddle1->x = 0;
	paddle1->y = 100;
	paddle1->texture = loadTexture("gfx/player.png");

	paddle2->x = SCREEN_WIDTH - 10;
	paddle2->y = 100;
	paddle2->texture = loadTexture("gfx/player.png");

    //here we use -> because player is a pointer type, not an actual Object type. Remember that!
	//the & ampersand symbol signify that we are passing the actual address of the paddle's
	//with and height
	SDL_QueryTexture(paddle1->texture, NULL, NULL, &paddle1->w, &paddle1->h);
	SDL_QueryTexture(paddle2->texture, NULL, NULL, &paddle2->w, &paddle2->h);
}

//handle the logic, player and bullets too
static void logic(void)
{
	updatePlayer();
	
	updateBall();
}

//handle all player's actions: movements with restriction
static void updatePlayer(void)
{
	//player speed set to 0
	paddle1->dx = paddle1->dy = 0;

	//if the key are pressed - registered in the keyboard array
	if (app.keyboard[SDL_SCANCODE_UP])
	{
		paddle1->dy = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		paddle1->dy = PLAYER_SPEED;
	}
	
	paddle1->x += paddle1->dx;
	paddle1->y += paddle1->dy;

}


//Handle initiation of ball: create it
static void initBall(void)
{
	
	ball = malloc(sizeof(Object));
	memset(ball, 0, sizeof(Object));
	stage.ball = ball;

    //set ball parameters
	ball->dx = BALL_SPEED;
	ball->dy = BALL_SPEED;
	ball->health = 1;
	ball->texture = loadTexture("gfx/ball.png");
	SDL_QueryTexture(ball->texture, NULL, NULL, &ball->w, &ball->h);
	
    //initial bullet location: where it spawns
	//position: middle of screen
	ball->x = SCREEN_WIDTH / 2;
	ball->y = SCREEN_HEIGHT / 2;
}

//handle ball logic: curerently only handles bounces
static void updateBall(void)
{
	//move it according to its velocity
	ball->x += ball->dx;
	ball->y += ball->dy;
	
	//if it reaches the end of the screen
	if (checkCollision(ball, paddle1))
	{
		ball->dx = -ball->dx;
	} 
	else if (ball->x + ball->w >= SCREEN_WIDTH) {
		ball->dx = -ball->dx;
	}
	else if (ball->x <= 0) {
		printMessage("You lose!");
	}
	if ((ball->y + ball->h > SCREEN_HEIGHT) || (ball->y < 0))
	{
		ball->dy = -ball->dy;
	}
}

//draw function used to fill the function pointer of App. But why? I have no idea!
static void draw(void)
{
	drawPaddles();
	
	drawBall();
}

//blit the player onto the renderer at its position
static void drawPaddles(void)
{
	blit(paddle1->texture, paddle1->x, paddle1->y);
	//blit(paddle2->texture, paddle2->x, paddle2->y);
}

//blit the bullets onto the renderer using their position
static void drawBall(void)
{
	blit(ball->texture, ball->x, ball->y);
}