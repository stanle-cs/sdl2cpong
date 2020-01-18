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
static void drawScores();
static void resetStage();

static SDL_bool checkCollision(Object *collider, Object *collided);
static Object *paddle1, *paddle2, *ball;
static int score1, score2;

//check if two objects collided
SDL_bool checkCollision(Object *firstObject, Object *secondObject) {
	int ax1 = firstObject->x;
	int ax2 = firstObject->x + firstObject->w;
 	int ay1 = firstObject->y;
	int ay2 = firstObject->y + firstObject->h;

	int bx1 = secondObject->x;
	int bx2 = secondObject->x + secondObject->w;
	int by1 = secondObject->y;
	int by2 = secondObject->y + secondObject->h;

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

	//init scores
	score1 = 0;
	score2 = 0;
	
}

//reset the stage to start again
static void resetStage() {
	paddle1->x = 0;
	paddle1->y = (SCREEN_HEIGHT - paddle1->h) / 2;
	paddle2->x = SCREEN_WIDTH - 10;
	paddle2->y = (SCREEN_HEIGHT - paddle2->h) / 2;
	ball->x = (SCREEN_WIDTH - ball->w) / 2;
	ball->y = (SCREEN_HEIGHT - ball->h) / 2;

	//this block of code is copied from the initBall procedure.
	//not sure how to make it work without a global variable.
	//people says that global variables are bad, are they?
	int VAL_COUNT = 4;
	int dx = rand() % VAL_COUNT , dy = rand() % VAL_COUNT;
	float speedVals [4] = {1, -1, 2, -2};
	ball->dx = speedVals[dx]*BALL_SPEED;
	ball->dy = speedVals[dy]*BALL_SPEED;
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

	
	paddle1->texture = loadTexture("gfx/player.png");
	paddle2->texture = loadTexture("gfx/player.png");

    //here we use -> because player is a pointer type, not an actual Object type. Remember that!
	//the & ampersand symbol signify that we are passing the actual address of the paddle's
	//with and height
	SDL_QueryTexture(paddle1->texture, NULL, NULL, &paddle1->w, &paddle1->h);
	paddle1->x = 0;
	paddle1->y = (SCREEN_HEIGHT - paddle1->h) / 2;

	SDL_QueryTexture(paddle2->texture, NULL, NULL, &paddle2->w, &paddle2->h);
	paddle2->x = SCREEN_WIDTH - 10;
	paddle2->y = (SCREEN_HEIGHT - paddle2->h) / 2;
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
	paddle2->dx = paddle2->dy = 0;

	//handle paddle1
	if (app.keyboard[SDL_SCANCODE_UP]) {
		paddle1->dy = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_DOWN]) {
		paddle1->dy = PLAYER_SPEED;
	}
	
	paddle1->x += paddle1->dx;
	paddle1->y += paddle1->dy;

	if (paddle1->y < 0) {
		paddle1->y = 0;
	} 
	else if (paddle1->y + paddle1->h > SCREEN_HEIGHT) {
		paddle1->y = SCREEN_HEIGHT - paddle1->h;
	}


	//handles paddle2
	if (app.keyboard[SDL_SCANCODE_W]) {
		paddle2->dy = -PLAYER_SPEED;
	}
	
	if (app.keyboard[SDL_SCANCODE_S]) {
		paddle2->dy = PLAYER_SPEED;
	}
	
	paddle2->x += paddle2->dx;
	paddle2->y += paddle2->dy;

	if (paddle2->y < 0) {
		paddle2->y = 0;
	} 
	else if (paddle2->y + paddle2->h > SCREEN_HEIGHT) {
		paddle2->y = SCREEN_HEIGHT - paddle2->h;
	}

}


//Handle initiation of ball: create it
static void initBall(void)
{
	
	ball = malloc(sizeof(Object));
	memset(ball, 0, sizeof(Object));
	stage.ball = ball;
    //set ball parameters
	srand(time(NULL));
	int VAL_COUNT = 4;
	int dx = rand() % VAL_COUNT , dy = rand() % VAL_COUNT;
	float speedVals [4] = {1, -1, 2, -2};


	ball->dx = speedVals[dx]*BALL_SPEED;
	ball->dy = speedVals[dy]*BALL_SPEED;

	//ball never die!
	ball->health = 1;
	ball->texture = loadTexture("gfx/ball.png");
	SDL_QueryTexture(ball->texture, NULL, NULL, &ball->w, &ball->h);
	
	//position: middle of screen
	ball->x = (SCREEN_WIDTH - ball->w) / 2;
	ball->y = (SCREEN_HEIGHT - ball->h) / 2;
}

//handle ball logic: curerently only handles bounces
static void updateBall(void) {
	//move it according to its velocity
	ball->x += ball->dx;
	ball->y += ball->dy;
	
	//if it reaches the end of the screen
	if (checkCollision(ball, paddle1) || checkCollision(ball, paddle2)) {
		ball->dx = -ball->dx;
	} 
	else if (ball->x >= SCREEN_WIDTH) {
		score1++;
		resetStage();
	}
	else if (ball->x <= 0) {
		score2++;
		resetStage();
	}
	if ((ball->y + ball->h > SCREEN_HEIGHT) || (ball->y < 0)) {
		ball->dy = -ball->dy;
	}
}

//draw function used to fill the function pointer of App. But why put it here? I have no idea!
static void draw(void) {
	drawPaddles();
	drawBall();
	drawScores();
}

//blit the player onto the renderer at its position
static void drawPaddles(void) {
	blit(paddle1->texture, paddle1->x, paddle1->y);
	blit(paddle2->texture, paddle2->x, paddle2->y);
}

//blit the bullets onto the renderer using their position
static void drawBall(void) {
	blit(ball->texture, ball->x, ball->y);
}

static void drawScores() {
	char strScore1[10];
	char strScore2[10]; 
	snprintf(strScore1, 10, "%d", score1);
	snprintf(strScore2, 10, "%d", score2);
	printMessage(strScore1, 25, 25, 25);
	printMessage(strScore2, 25, SCREEN_WIDTH - 25, 25);
}