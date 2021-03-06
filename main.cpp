// Copyright 2005 by Anthony Liekens anthony@liekens.net

#include "SDL2_gfxPrimitives.h"
#include "timer.h"
#include "SDL.h"
//#include "SDL_ttf.h"
#include <math.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>

#define NLEDS 300
int positions[NLEDS][2] = {{153,86},{149,94},{153,100},{157,105},{159,111},{159,117},{156,122},{151,126},{145,126},{139,126},{133,123},{131,117},{132,110},{134,105},{138,99},{140,90},{132,87},{125,87},{118,88},{115,95},{119,101},{122,107},{124,113},{123,119},{119,124},{114,126},{108,126},{102,124},{97,121},{95,115},{96,109},{99,103},{103,98},{106,90},{100,85},{94,82},{87,80},{80,76},{73,73},{66,71},{58,71},{51,74},{45,76},{38,76},{31,74},{26,70},{23,62},{16,65},{9,67},{3,66},{0,62},{1,57},{8,55},{15,53},{20,49},{27,49},{32,54},{36,60},{40,66},{47,65},{54,61},{52,53},{48,47},{44,40},{38,34},{29,31},{22,31},{15,30},{9,26},{6,20},{11,18},{19,19},{27,19},{35,19},{42,20},{49,25},{52,32},{56,39},{64,43},{72,42},{74,36},{70,29},{69,21},{66,13},{57,13},{49,11},{42,6},{43,1},{51,0},{59,0},{67,1},{74,4},{80,10},{80,17},{82,26},{90,32},{98,31},{105,29},{113,27},{121,27},{128,26},{136,26},{144,28},{151,29},{158,32},{166,33},{174,28},{176,19},{177,11},{182,6},{190,2},{198,1},{206,1},{214,2},{215,7},{209,11},{201,13},{193,14},{189,20},{187,28},{183,35},{181,41},{188,44},{197,42},{203,36},{206,28},{212,22},{218,21},{226,20},{234,21},{242,20},{249,20},{249,26},{244,31},{238,33},{230,33},{222,33},{214,39},{209,46},{205,52},{200,58},{204,64},{211,66},{219,66},{219,59},{224,54},{230,50},{236,51},{242,55},{249,57},{255,59},{254,64},{249,68},{243,67},{237,65},{230,65},{227,72},{221,76},{214,77},{208,76},{201,74},{195,72},{187,72},{180,74},{173,77},{166,80},{159,83},{157,76},{164,73},{171,71},{177,67},{183,63},{186,58},{182,52},{176,49},{169,46},{163,43},{156,40},{149,38},{141,36},{135,35},{128,35},{121,35},{114,36},{108,38},{101,40},{93,43},{86,46},{79,48},{73,52},{69,59},{77,67},{83,70},{90,73},{96,76},{103,78},{110,80},{118,81},{125,82},{132,81},{140,80},{148,79},{145,104},{152,107},{155,113},{152,120},{145,123},{140,121},{136,116},{138,108},{145,113},{140,110},{140,115},{144,118},{149,115},{149,110},{144,109},{109,104},{116,107},{119,114},{115,121},{109,123},{103,120},{100,115},{102,108},{109,113},{105,111},{105,115},{109,118},{113,115},{113,112},{109,108},{74,58},{79,54},{86,51},{94,48},{101,45},{109,44},{118,43},{124,42},{133,42},{141,43},{149,45},{158,47},{164,49},{171,51},{178,54},{183,58},{177,63},{171,67},{164,70},{157,72},{149,73},{141,75},{135,75},{127,75},{119,74},{111,74},{103,72},{96,71},{88,68},{81,64},{79,59},{85,55},{92,54},{100,51},{107,51},{115,50},{121,50},{130,49},{139,51},{146,51},{156,52},{163,53},{170,57},{179,58},{171,62},{165,64},{156,66},{148,67},{140,68},{132,68},{124,68},{116,67},{108,67},{100,66},{93,63},{88,59},{94,58},{101,58},{110,58},{116,58},{123,58},{128,58},{134,59},{140,58},{147,58},{154,59},{161,59},{166,59}};

int x( int i ) {
  return positions[ i ][ 0 ];
}

int y( int i ) {
  return 127 - positions[ i ][ 1 ];
}

Uint32 FPStimer, FPScounter;
double FPS;
Timer timer;

uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a ) {
  return ((uint32_t)r << 24) | ((uint32_t)g <<  16) | ((uint32_t)b <<  8) | a;
}

int main(int argc, char** argv) {

	/* Init SDL */
	if( SDL_Init( SDL_INIT_TIMER | SDL_INIT_VIDEO ) < 0 ) {
		cerr << "Couldn't initialize SDL: " << SDL_GetError() << endl;
		exit( 1 );
	}
	timer.start();
	atexit( SDL_Quit );
	
	srand( time( NULL) );
	
	/* Initialize the display */

	SDL_Window *sdlWindow = SDL_CreateWindow("My Game Window", // SDL2
	                          SDL_WINDOWPOS_CENTERED,
	                          SDL_WINDOWPOS_CENTERED,
	                          256, 128,
	                          SDL_WINDOW_OPENGL);
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	bool quit = false;

	// Main loop: loop forever.
	while( !quit ) {
	
		// render black
	
		SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
		SDL_RenderClear(sdlRenderer);
		for( int i = 0; i < NLEDS; i++ ) {
			pixelColor( sdlRenderer, x(i), y(i), color( ( i * 148 ) % 256, ( i * 97 ) % 256, ( i * 67 ) % 256, 255 ) );
		}
		SDL_RenderPresent(sdlRenderer);
		
		// game rendering code here

		if( !timer.isPaused() ) {

			// update the universe
		
			// let players update their states
		
		}
		
		// Poll for events, and handle the ones we care about.
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
		
			switch (event.type) {
			
				case SDL_KEYDOWN:
				break;
				case SDL_KEYUP:
					if( event.key.keysym.sym == SDLK_p ) {
						timer.pause();
					}
					// If escape is pressed, return (and thus, quit)
					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
				break;
				case SDL_QUIT:
					quit = true;
				
			}
			
		}
		
		// Keep shut for some time, not to use too much CPU
		
		// SDL_Delay( 20 );
		
	}
	
	return 0;
	
}
