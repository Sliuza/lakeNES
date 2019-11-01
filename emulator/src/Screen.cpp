#include "../include/Screen.hpp"
#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>
#include <stdio.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitset>
#include <cstdint>



const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 256;
SDL_Window* window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface* screenSurface = nullptr;
SDL_Rect rect;
SDL_Event Events;

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
    // SDL_Delay( 600 );
}


// void Screen::sendToDisplay(){
// 	int value = (rand() % 10) + 1;

// 	// screenSurface captura a surface atual de window
// 	screenSurface = SDL_GetWindowSurface( window );

// 	// de acordo com o valor gerado gera um fundo de uma cor diferente - se value < 5 = laranja, caso contrario, preto
// 	if(value < 5)
// 		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xff, 0xa5, 0 ) );
// 	else 
// 		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 0, 0 ) );

	
// 	// screenSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, rmask, gmask, bmask, amask);
	
// 	//Update the surface - efetivamente reproduz a surface de window atualiuzada
// 	SDL_UpdateWindowSurface( window );

// 	//Wait 600 ms
// 	SDL_Delay( 600 );
// }


// void Screen::sendToDisplay(uint8_t tblPattern[2][4096], uint8_t tblName[2][1024], uint8_t oam_table[64][4]){
// 	//translate

	
// if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
// 		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
// }
// 	else{
// 		//Create window
// 		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

// 		//cria a janela e um renderer ja associado a ela
// 		// SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

// 		//cria um render somente e o atribui a uma janela - a ultima flag sinaliza que ele acompanhara a velocidade do hardware
		

// 		if( window == NULL )
// 		{
// 			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
// 		}
// 		return;
// 	}
// 	return;
// }



//TODO como eu acho que deveria ser um racunho do SendDisplay

void Screen::sendToDisplay(uint8_t tblPattern[2][4096], uint8_t tblName[2][1024], uint8_t oam_table[64][4]){

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
		

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		
				//Get window surface
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
		
		// DISPLAY BACKGROUND
		uint8_t sprite1[8];
		uint8_t sprite2[8];
		int i = 0, j = 0;
		int color = 0;
		for(int b = 0; b < 1024; b++){
			uint8_t background = tblName[0][b];

		    //sprite1  --> linha + coluna
			
			
			for(i = 0; i < 8; i++){
				sprite1[i] = tblPattern[0][(background /16)*256 + ((background %16)*16) + (i)];
				sprite2[i] = tblPattern[0][(background /16)*256 + ((background %16)*16) + (i) + 8];
			}
			int* pixels = (int*) screenSurface->pixels;
			
			
			for(i = 0; i < 8; i++){
				for(j= 7; j >= 0 ; j--){
					
					color = (int) ((sprite1[i] & 0x01) + (sprite2[i] & 0x01)*2);
					
					//nossa paleta de cores em hex
					switch(color){
						case 0:
							color = 0x000001;
							break;
						case 1:
							color = 0xF8F8F8;
							break;
						case 2:
							color = 0xF85898;
							break;
						case 3:
							color = 0xE40058;
							break;
					}

					// offset para o pixel -> i, j e b. 
					// (b / 32) --> nos da a LINHA do TILE.   
					// (b % 32) --> nos da a COLUNA do TILE.
					pixels[(i*256 + j)+((b/32)*2048) + ((b%32)*8)] = color;
					sprite1[i] >>= 1;
					sprite2[i] >>= 1; 
				}
			}
			
			SDL_UpdateWindowSurface(window);
		}

		// DISPLAY OAM
		SDL_Surface* oamSurface;
		oamSurface = SDL_GetWindowSurface(window);
		int k = 0, y_oam = 0, x_oam = 0;
		for(k = 0; k < 64; k++){
			//printf("PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP %d \n ", oam_table[k][1]);

			for(i = 0; i < 8; i++){
				sprite1[i] = tblPattern[0][(oam_table[k][1] /16)*256 + ((oam_table[k][1] %16)*16) + (i)];
				sprite2[i] = tblPattern[0][(oam_table[k][1] /16)*256 + ((oam_table[k][1] %16)*16) + (i) + 8];
			}
			int* pixels = (int*) oamSurface->pixels;
			
			int color = 0;
			if(oam_table[k][2] & (0x01 << 7)){
				
				for(i = 0; i < 8; i++){
					for(j= 7; j >= 0 ; j--){
						int invert = 7-i;
						color = (int) ((sprite1[invert] & 0x01) + (sprite2[invert] & 0x01)*2);
						
						//nossa paleta de cores em hex
						switch(color){
							case 0:
								color = 0x000001;
								break;
							case 1:
								color = 0xF8F8F8;
								break;
							case 2:
								color = 0xF85898;
								break;
							case 3:
								color = 0xE40058;
								break;
						}

						// offset para o pixel
						// y_oam --> nos da a LINHA do TILE.   
						// x_oam --> nos da a COLUNA do TILE.
						y_oam = oam_table[k][0];
						x_oam = oam_table[k][3];
						pixels[(i*256 + j)+(y_oam*256 + x_oam)] = color;
						//pixels[(i*256 + j)+((b/32)*2048) + ((b%32)*8)] = color;
						sprite1[invert] >>= 1;
						sprite2[invert] >>= 1; 
					}
				}
			}
			else{
				for(i = 0; i < 8; i++){
					for(j= 7; j >= 0 ; j--){
						
						color = (int) ((sprite1[i] & 0x01) + (sprite2[i] & 0x01)*2);
						
						//nossa paleta de cores em hex
						switch(color){
							case 0:
								color = 0x000001;
								break;
							case 1:
								color = 0xF8F8F8;
								break;
							case 2:
								color = 0xF85898;
								break;
							case 3:
								color = 0xE40058;
								break;
						}

						if(oam_table[k][2] & (0x03) == 0x03){
							color = 0x000001;
						}

						// offset para o pixel
						// y_oam --> nos da a LINHA do TILE.   
						// x_oam --> nos da a COLUNA do TILE.
						y_oam = oam_table[k][0];
						x_oam = oam_table[k][3];
						pixels[(i*256 + j)+(y_oam*256 + x_oam)] = color;
						//pixels[(i*256 + j)+((b/32)*2048) + ((b%32)*8)] = color;
						sprite1[i] >>= 1;
						sprite2[i] >>= 1; 
					}
				}
			}
		}

        SDL_Delay( 7000 );
		SDL_BlitSurface(oamSurface, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);

		
	}
}



void Screen::startDisplay(){


		
			//Fill the surface white
			// SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 0, 0 ) );
			
			// //Update the surface
			// SDL_UpdateWindowSurface( window );

			// //Wait 600 ms
			// //SDL_Delay( 2 );
		
	}
		


void Screen::endDisplay(){
	//Destroy window
	SDL_DestroyWindow( window );

	// //Quit SDL subsystems
	// SDL_Quit();
}