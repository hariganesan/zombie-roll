// Hari Ganesan 5/13/13
// zombie-roll: rendering

#include "Render.hpp"

//void MyWindow::~MyWindow() {
//	TTF_CloseFont(font);
//}

void MyWindow::Init() {
	screen = NULL; // main window

	// initialize window properties
	if (!(screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 
																	SDL_SWSURFACE))) {
		cerr << "unable to set up window" << endl;	
		exit(1);
	}

	SDL_WM_SetCaption("Zombie Roll", NULL);

	// preload assets (testing)
	for (int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
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

	g = new Game("Hari", D_FIELD);
	g->currentArea = new Area(.1);
}

void MyWindow::Destroy() {
	Game *tmpG = g;
	g = NULL;
	delete tmpG;

	// free assets
	for (int i = 0; i < MAX_SPRITE_SHEET_COUNT; i++) {
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
		//if (cin >> buffer)
		//	printStatus();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
				 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
				isRunning = false;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p) {
				printStatus();
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
				toggleMusic();
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
				keys.left = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
				keys.down = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
				keys.right = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
				keys.up = true;
			}
		}

		// LOGIC

		if (g->display == D_FIELD) {
			moved = false;
			if (keys.left) {
				if (g->mc->moveLeft()) {
					moved = true;
				}
				keys.left = false;
			} else if (keys.down) {
				if (g->mc->moveDown()) {
					moved = true;
				}
				keys.down = false;
			} else if (keys.right) {
				if (g->mc->moveRight()) {
					moved = true;
				}
				keys.right = false;
			} else if (keys.up) {
				if (g->mc->moveUp()) {
					moved = true;
				}
				keys.up = false;
			}

			// battle!
			if (moved && rand() % 100 < g->currentArea->battlePercent*100) {
				g->createBattle();
				g->display = DT_FIELD_BATTLE;
			}
		} else if (g->display == DT_FIELD_BATTLE) {
			if (g->timer > TT_FIELD_BATTLE) {
				g->timer = 0;
				g->display = D_BATTLE;
				//glClearColor(1, 1, 1, 1); //white background TODO: change to SDL
			}
		} else if (g->display == D_BATTLE) {

		}

		// RENDERING

		//renderGL();
	}
}

void MyWindow::initKeys() {
	keys.right = false;
	keys.left = false;
	keys.up = false;
	keys.down = false;
}

void MyWindow::toggleMusic() {
	if (music == NULL) {
		music = Mix_LoadMUS("assets/music/senomar.mid");

		// play infinite times
		Mix_PlayMusic(music, -1);
	} else {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
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
		cout << g->b->enemyCount << " enemies" << endl;
		
		for (vector<Enemy>::const_iterator iter = g->b->enemies.begin(); 
				 iter != g->b->enemies.end(); iter++) {
			iter->printStatus();
		}

	} else {
		cout << "state: field" << endl;
	}

	cout << "------------" << endl;
}
