// Hari Ganesan 7/22/13
// zombie-roll: rendering sprites

#include "Render.hpp"

SDL_Surface *MyWindow::loadImage(string filename) {
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	if (!(loadedImage = IMG_Load(filename.c_str()))) {
		cerr << "unable to load image " << filename << endl;
		return NULL;
	}

	if (!(optimizedImage = SDL_DisplayFormat(loadedImage))) {
		cerr << "unable to optimize image " << filename << endl;
		SDL_FreeSurface(loadedImage);
		return NULL;
	}

	SDL_FreeSurface(loadedImage); // free old surface
	// set color key
	SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, 
									SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));

	return optimizedImage;
}

void MyWindow::applySurface(int x, int y, SDL_Surface* source, 
														SDL_Surface* destination, SDL_Rect* clip) {
	SDL_Rect offset; // holds offsets

	// get offsets
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset); // blit surface
}

/*
int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    std::cout << "init'd" << std::endl;
    
    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Clip range for the top left
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = 100;
    clip[ 0 ].h = 100;

    //Clip range for the top right
    clip[ 1 ].x = 100;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = 100;
    clip[ 1 ].h = 100;

    //Clip range for the bottom left
    clip[ 2 ].x = 0;
    clip[ 2 ].y = 100;
    clip[ 2 ].w = 100;
    clip[ 2 ].h = 100;

    //Clip range for the bottom right
    clip[ 3 ].x = 100;
    clip[ 3 ].y = 100;
    clip[ 3 ].w = 100;
    clip[ 3 ].h = 100;

    //Fill the screen white
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

    //Apply the sprites to the screen
    apply_surface( 0, 0, dots, screen, &clip[ 0 ] );
    apply_surface( 540, 0, dots, screen, &clip[ 1 ] );
    apply_surface( 0, 380, dots, screen, &clip[ 2 ] );
    apply_surface( 540, 380, dots, screen, &clip[ 3 ] );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }
    
*/