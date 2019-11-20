#include "../include/Screen.hpp"
#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>
#include <stdio.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <bitset>
#include <cstdint>



const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;

SDL_Renderer *renderer = nullptr;

SDL_Rect rect;
SDL_Event Events;

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
	

	// esse trecho renderiza um retangulo, cujas medidas foram setadas previamente, em uma posi;'ao aleatoria da tela (seguindo uma logica da implementacao)'
	SDL_RenderPresent(renderer);
	rect.x = rand() % (SCREEN_WIDTH - 10);
	rect.y = rand() % (SCREEN_HEIGHT - 10);
	SDL_RenderDrawRect(renderer,&rect);

	//efetiva a renderizacao ("fz aparecer na tela" o que foi atribuido ao renderer)
    SDL_RenderPresent(renderer);

}



void Screen::createWindow(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else{
		this->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		this->surface = SDL_GetWindowSurface(this->window);
		SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00));
	}
	
}




//TODO como eu acho que deveria ser um racunho do SendDisplay

void Screen::sendToDisplay(uint8_t tblPattern[2][4096], uint8_t tblName[2][1024], uint8_t oam_table[64][4]){


	// DISPLAY BACKGROUND
	uint8_t sprite1[8];
	uint8_t sprite2[8];
	int i = 0, j = 0;
	int color = 0;
	for(int b = 0; b < 944; b++){
		uint8_t background = tblName[0][b];
		
	    //sprite1  --> linha + coluna
		
		
		for(i = 0; i < 8; i++){
			sprite1[i] = tblPattern[0][(background /16)*256 + ((background %16)*16) + (i)];
			sprite2[i] = tblPattern[0][(background /16)*256 + ((background %16)*16) + (i) + 8];
		}
		int* pixels = (int*) this->surface->pixels;
		
		
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
				if(b > 32 && b < 960)
					pixels[(i*256 + j)+(((b/32) - 1)*2048) + ((b%32)*8)] = color;
				sprite1[i] >>= 1;
				sprite2[i] >>= 1; 
			}
		}
		
		// SDL_UpdateWindowSurface(window);
	}

	// DISPLAY OAM
	SDL_Surface* oamSurface;
	oamSurface = SDL_GetWindowSurface(this->window);
	
	int k = 0, y_oam = 0, x_oam = 0, invert = 0;
	for(k = 0; k < 64; k++){
		//printf("PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP %d \n ", oam_table[k][1]);

		for(i = 0; i < 8; i++){
			sprite1[i] = tblPattern[0][(oam_table[k][1] /16)*256 + ((oam_table[k][1] %16)*16) + (i)];
			sprite2[i] = tblPattern[0][(oam_table[k][1] /16)*256 + ((oam_table[k][1] %16)*16) + (i) + 8];
		}
		int* pixels = (int*) oamSurface->pixels;
		
		int color = 0;
		//if(oam_table[k][2] & (0x01 << 7)){
			
			for(i = 0; i < 8; i++){
				for(j= 7; j >= 0 ; j--){
					invert = i;

					if(oam_table[k][2] & (0x01 << 7))
						invert = 7 - i;

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
                    if(oam_table[k][2] & 0x03 == 3){
                        color = 0x000001;
                    }
					// offset para o pixel
					y_oam = oam_table[k][0];
					x_oam = oam_table[k][3];
					// printf(" Y_OAM: %d ------ X_OAM: %d\n", y_oam, x_oam);
					if(x_oam < 256 && y_oam >= 8 && y_oam < 232)
						pixels[(i*256 + j)+((y_oam - 8)*256 + x_oam)] = color;
					sprite1[invert] >>= 1;
					sprite2[invert] >>= 1; 
				}
			}
		}

	SDL_BlitSurface(oamSurface, NULL, this->surface, NULL);
	SDL_UpdateWindowSurface(this->window);

		
	
}


void Screen::endDisplay(){

	//Destroy window
	SDL_DestroyWindow( this->window );

	//Quit SDL subsystems
	SDL_Quit();
}


uint8_t Screen::readControl1(){
	SDL_Event e;
	counter2 = 0;
	int pointer = counter1 % 8;
	counter1++;
	while(SDL_PollEvent(&e) != 0){
		if( e.type == SDL_QUIT )
	      {
	       endDisplay();
	      }
	}
	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	switch(pointer){
		case 0:
			return keys[SDL_SCANCODE_E];
			break;

		case 1:
			return keys[SDL_SCANCODE_R];
			break;

		case 2:
			return keys[SDL_SCANCODE_LCTRL];
			break;

		case 3:
			return keys[SDL_SCANCODE_KP_SPACE];
			break;
			
		case 4:
			return keys[SDL_SCANCODE_W];
			break;
	
		case 5:
			return keys [SDL_SCANCODE_S];
			break;

		case 6:
			return keys[SDL_SCANCODE_A];
			break;

		case 7:
			return keys[SDL_SCANCODE_D];
			break;
		default:
			return 0;
	}
}

uint8_t Screen::readControl2(){
	SDL_Event e;
	counter1 = 0;
	int pointer = counter2 % 8;
	counter2++;
	while(SDL_PollEvent(&e) != 0){
		if( e.type == SDL_QUIT )
	      {
	       endDisplay();
	      }
	}
	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	switch(pointer){
		case 0:
			return keys[SDL_SCANCODE_KP_PLUS];
			break;

		case 1:
			return keys[SDL_SCANCODE_KP_MINUS];
			break;

		case 2:
			return keys[SDL_SCANCODE_HOME];
			break;

		case 3:
			return keys[SDL_SCANCODE_PAGEDOWN];
			break;
			
		case 4:
			return keys[SDL_SCANCODE_KP_8];
			break;
	
		case 5:
			return keys [SDL_SCANCODE_KP_2];
			break;

		case 6:
			return keys[SDL_SCANCODE_KP_4];
			break;

		case 7:
			return keys[SDL_SCANCODE_KP_6];
			break;
		default:
			return 0;
	}
}
