#include "../include/Screen.hpp"
#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Rect rect;

// Uint32 rmask, gmask, bmask, amask;

//TALVEZ POSSAM SER DESCARTADOS

// #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    // rmask = 0xff000000;
    // gmask = 0x00ff0000;
    // bmask = 0x0000ff00;
    // amask = 0x000000ff;
// #else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
// #endif

void Screen::drawPixel(){
	//seta a cor do renderer, tutoriais sempre realizam esse procedimento atraves de duas escritas (deve se assemelhar com os registradores da PPU)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	//seta largura e altura do retangulo
	rect.w = 10;
	rect.h = 10;
	

	// O loop abaixo desenha um ponto a cada pixel(x,y) sinalizado - y e incrementado a cada iteracao
	// for (int i = 0; i < SCREEN_WIDTH; ++i){
 //        SDL_RenderDrawPoint(renderer, 0, i);
	// }

	// esse trecho renderiza um retangulo, cujas medidas foram setadas previamente, em uma posi;'ao aleatoria da tela (seguindo uma logica da implementacao)'
	SDL_RenderPresent(renderer);
	rect.x = rand() % (SCREEN_WIDTH - 10);
	rect.y = rand() % (SCREEN_HEIGHT - 10);
	SDL_RenderDrawRect(renderer,&rect);

	//desenha um ponto (um pixel) em uma posicao aleatoria da tela 
	// SDL_RenderDrawPoint(renderer, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);

	//efetiva a renderizacao ("fz aparecer na tela" o que foi atribuido ao renderer)
    SDL_RenderPresent(renderer);

    //atrasa o tick da do frame (os fps) - medida em ms
    SDL_Delay( 600 );
}


void Screen::sendToDisplay(){
	int value = (rand() % 10) + 1;

	// screenSurface captura a surface atual de window
	screenSurface = SDL_GetWindowSurface( window );

	// de acordo com o valor gerado gera um fundo de uma cor diferente - se value < 5 = laranja, caso contrario, preto
	if(value < 5)
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xff, 0xa5, 0 ) );
	else 
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) );

	
	// screenSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);
	
	//Update the surface - efetivamente reproduz a surface de window atualiuzada
	SDL_UpdateWindowSurface( window );

	//Wait 600 ms
	SDL_Delay( 600 );
}

void Screen::startDisplay(){

		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		//cria a janela e um renderer ja associado a ela
		// SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

		//cria um render somente e o atribui a uma janela - a ultima flag sinaliza que ele acompanhara a velocidade do hardware
		renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else{
				//Get window surface
			screenSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);
			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 0, 0 ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );

			//Wait 600 ms
			SDL_Delay( 600 );
		}
	}
		
}

void Screen::endDisplay(){
	//Destroy window
	SDL_DestroyWindow( window );

	// //Quit SDL subsystems
	// SDL_Quit();
}