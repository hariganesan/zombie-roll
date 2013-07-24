// Hari Ganesan 5/13/13
// zombie-roll: Window control

#include "Window.hpp"

void MyWindow::Init() {
	// initialize window properties
	if (!(screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 
																	SDL_SWSURFACE))) {
		cerr << "unable to set up window" << endl;	
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Zombie Roll", NULL);

	// preload assets (testing)
	for (unsigned int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
		spriteSheets[i] = NULL;
	}

	spriteSheets[0] = loadImage("assets/images/test/1.png");

	// initialize random number generator
	srand(time(NULL));

	// initialize game state
	isRunning = true;
	moved = false;
	initKeys();
	//toggleMusic();

	// open font
	if (!(font12 = TTF_OpenFont("assets/fonts/chintzy.ttf", 12))) {
		cerr << "unable to open font" << endl;
		exit(EXIT_FAILURE);
	}

	g = new Game("Hari", D_FIELD);
	g->currentArea = new Area(.1);

	// test image
	spriteSheets[0] = loadImage("../../Desktop/dots.png");
	//pushDots();

	// debugging
}

void MyWindow::Destroy() {
	Game *tmpG = g;
	g = NULL;
	delete tmpG;

	TTF_CloseFont(font12);

	// free assets
	for (unsigned int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
		if (spriteSheets[i]) {
			SDL_Surface *tmpS = spriteSheets[i];
			spriteSheets[i] = NULL;
			SDL_FreeSurface(tmpS);
		}
	}
}

void MyWindow::run() {
	while (isRunning) {

		// EVENTS

		while (SDL_PollEvent(&event)) {
			handleEvent(event);
		}

		// LOGIC

		performLogic();

		// RENDERING

		renderSDL();
	}
}

void MyWindow::initKeys() {
	keys.right = false;
	keys.left = false;
	keys.up = false;
	keys.down = false;
}

void MyWindow::printStatus() {
	if (!g) {
		cerr << "no game attached to window" << endl;
		return;
	}

	cout << "------------" << endl;
	cout << "game running" << endl;
	cout << g->partyCount << " party members" << endl;
	
	for (vector<PartyMember>::const_iterator iter = g->party.begin(); 
			 iter != g->party.end(); iter++) {
		iter->printStatus();
	}

	if (g->b) {
		cout << "state: battle" << endl;
		cout << g->b->enemies.size() << " enemies" << endl;
		
		for (vector<Enemy>::const_iterator iter = g->b->enemies.begin(); 
				 iter != g->b->enemies.end(); iter++) {
			iter->printStatus();
		}

	} else {
		cout << "state: field" << endl;
	}

	cout << "------------" << endl;
}
