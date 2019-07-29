#include <SDL2/SDL.h>
#include <iostream>

int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

SDL_Window* window;
SDL_Renderer* renderer;

bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();

void Render();
void RunGame();

#define snakeSize 10
int snakeDir = 0; //comeca apontando para a direita
SDL_Rect snakePos[snakeSize];


//compile com
//g++ example1.cpp -o example1 `sdl2-config --cflags --libs`

using namespace std;

int main( int argc, char* args[] )
{
	if ( !InitEverything() ) 
		return -1;


	for(int i=0; i<snakeSize; i++){
		snakePos[i].x = (snakeSize -i)*20;
		snakePos[i].y = 20;
		snakePos[i].w = 20;
		snakePos[i].h = 20;
	}

	RunGame();
}

void drawSnake(){

	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// desenha a cobrinha
	for(int i=0; i< snakeSize; i++){

		cout << "drawing " << snakePos[i].x << " " << snakePos[i].y <<endl;
		SDL_RenderFillRect( renderer, &snakePos[i] );
	}

	cout << "finished drawing" << endl;
}

void Render()
{
	// Change color to green
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
	// Clear the window and make it all green
	SDL_RenderClear( renderer );


	drawSnake();


	// Render the changes above
	SDL_RenderPresent( renderer);


}
bool InitEverything()
{
	if ( !InitSDL() )
		return false;

	if ( !CreateWindow() )
		return false;

	if ( !CreateRenderer() )
		return false;

	SetupRenderer();

	return true;
}
bool InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
bool CreateWindow()
{
	window = SDL_CreateWindow( "Server", posX, posY, sizeX, sizeY, 0 );

	if ( window == NULL )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}

	return true;
}
bool CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( renderer == NULL )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}

	return true;
}
void SetupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, sizeX, sizeY );

	// Set color of renderer to green
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
}
void RunGame()
{
	bool loop = true;

	while ( loop )
	{
		SDL_Event event;

		/*necessário para evitar a tela congelada*/
		while ( SDL_PollEvent( &event ) )
		{
			if ( event.type == SDL_QUIT )
				loop = false;
		}

		/*calcula uma direcao aleatoria*/
		int dir = rand()%4;

		switch(dir){
			case 0: //vai para a direita
				{
					if(snakeDir == 1) //nao pode ir para direita se direcao corrente for 1
						break;
					for(int i=snakeSize-1; i>=1; i--){
						snakePos[i].x = snakePos[i-1].x;
						snakePos[i].y = snakePos[i-1].y;
					}
					snakePos[0].x+=20;
					snakeDir = 0;
					if(snakePos[0].x >= sizeX - 20)
						snakePos[0].x = sizeX - 20;
					if(snakePos[0].x < 0)
						snakePos[0].x = 0;
					if(snakePos[0].y >= sizeY - 20)
						snakePos[0].y = sizeY - 20;
					if(snakePos[0].y < 0)
						snakePos[0].y = 0;


					break;
				}
		}
		Render();

		// Add a 16msec delay to make our game run at ~60 fps
		SDL_Delay( 500 );
	}
}
