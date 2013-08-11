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

	// preload assets
	for (unsigned int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
		spriteSheets[i] = NULL;
	}

	for (unsigned int i = 0; i < MAX_BUTTON_COUNT; i++) {
		buttons[i] = NULL;
		buttonsPressed[i] = false;
	}

	for (unsigned int i = 0; i < MAX_MESSAGE_COUNT; i++) {
		messages[i] = NULL;
	}

	// initialize random number generator
	srand(time(NULL));

	// initialize game state
	isRunning = true;
	moved = false;
	messageOnScreen = NULL;
	initKeys();
	//toggleMusic();

	// open font
	if (!(font24 = TTF_OpenFont("assets/fonts/chintzy.ttf", 24))) {
		cerr << "unable to open font" << endl;
		exit(EXIT_FAILURE);
	}

	g = new Game("Hari", D_FIELD);
	g->currentArea = new Area(BATTLE_PERCENT_DEF);

	// test image
	spriteSheets[0] = loadImage("../../Desktop/dots.png");
	SDL_Surface *buttonSheet1 = loadImage("../../Desktop/button.png");
	SDL_Surface *buttonSheet2 = loadImage("../../Desktop/button.png");
	// TODO: resize buttons?
	buttons[0] = new Button(buttonSheet1, screen, WINDOW_WIDTH/2, 10, 320, 240);
	buttons[1] = new Button(buttonSheet2, screen, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 320, 240);

	messages[0] = TTF_RenderText_Solid(font24, "Attack", SDL_BLACK);

	// debugging
	cout << "window loaded" << endl;
}

void MyWindow::Destroy() {
	Game *tmpG = g;
	g = NULL;
	delete tmpG;

	// free messages
	for (unsigned int i = 0; i < MAX_MESSAGE_COUNT; i++) {
		if (messages[i]) {
			SDL_Surface *tmpS = messages[i];
			messages[i] = NULL;
			SDL_FreeSurface(tmpS);
		}
	}

	// free buttons and button sheets
	for (unsigned int i = 0; i < MAX_BUTTON_COUNT; i++) {
		if (buttons[i]) {
			Button *tmpB = buttons[i];
			buttons[i] = NULL;
			delete tmpB;
		}
	}

	// free spritesheets
	for (unsigned int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
		if (spriteSheets[i]) {
			SDL_Surface *tmpS = spriteSheets[i];
			spriteSheets[i] = NULL;
			SDL_FreeSurface(tmpS);
		}
	}

	TTF_CloseFont(font24);
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
	cout << g->party.size() << " party members" << endl;
	
	for (vector<PartyMember>::const_iterator iter = g->party.begin(); 
			 iter != g->party.end(); iter++) {
		iter->printStatus();
	}

	if (g->b) {
		cout << "state: battle" << endl;
		cout << g->b->enemies.size() << " enemies" << endl;
		cout << "activeFC: " << g->b->activeFC->getID() << endl;
		cout << "bmenu items: " << g->b->battleMenu.size() << endl;
		
		for (vector<Enemy>::const_iterator iter = g->b->enemies.begin(); 
				 iter != g->b->enemies.end(); iter++) {
			iter->printStatus();
		}

	} else {
		cout << "state: field" << endl;
	}

	cout << "------------" << endl;
}
