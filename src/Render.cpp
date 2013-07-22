// Hari Ganesan 5/13/13
// zombie-roll: rendering

#include "Render.hpp"

//void MyWindow::~MyWindow() {
//	TTF_CloseFont(font);
//}

using std::cin;					using std::cout;
using std::cerr;				using std::endl;
using std::string;

void MyWindow::Init() {
	// initialize game state
	isRunning = true;
	moved = false;
	initKeys();
	
	g = new Game("Hari", D_FIELD);
	g->currentArea = new Area(.1);

	// preload assets (testing)
	//std::string img1(pngpath);
	g->spriteSheets[0] = SDL_GL_LoadPNG("assets/images/test/1.png");
}

void MyWindow::Destroy() {
	Game *tmp = g;
	g = NULL;
	delete tmp;

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
				glClearColor(1, 1, 1, 1); //white background
			}
		} else if (g->display == D_BATTLE) {

		}

		// RENDERING

		render();
	}
}

void MyWindow::initKeys() {
	keys.right = false;
	keys.left = false;
	keys.up = false;
	keys.down = false;
}

void MyWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // set matrix
	//SDL_Color TEXT_WHITE = {200, 200, 200};
	//SDL_Color TEXT_BLACK = {20, 20, 20};
	//SDL_Color TEXT_RED = {150, 0, 0};
	//SDL_Rect location;

	////////////////
	// BEGIN DRAWING
	////////////////

	if (g->display == D_FIELD) {
		// draw stuff
		glColor3ub(255, 255, 255);
		glBegin(GL_QUADS);
		glVertex2f(g->mc->x, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y+F_BOX_DIM);
		glVertex2f(g->mc->x, g->mc->y+F_BOX_DIM);
		glEnd();
	} else if (g->display == DT_FIELD_BATTLE) {
		// figure out coordinates
		g->mc->x = g->mc->orig_x + 5*g->timer*cos(g->timer);
		g->mc->y = g->mc->orig_y + 5*g->timer*sin(g->timer);
		g->timer++;

		// draw stuff
		glColor3ub(240, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(g->mc->x, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y+F_BOX_DIM);
		glVertex2f(g->mc->x, g->mc->y+F_BOX_DIM);
		glEnd();

		// fade to black
		glClearColor(0, 0, FIELD_COLOR - FIELD_COLOR*g->timer/TT_FIELD_BATTLE, 0);

	} else if (g->display == D_BATTLE) {
		//render sample images
		SDL_GL_RenderPNG(g->spriteSheets[0], 100, 100, 200, 100);
	}

	////////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(1000/SDL_FRAME_RATE); // frame rate 30ms
	return;
	
}

GLuint MyWindow::SDL_GL_LoadPNG(const char *f) {
	SDL_Surface *image = IMG_Load(f);
  if (image == NULL) {
    return -1;
  }
  SDL_DisplayFormatAlpha(image);
  //unsigned object(0);
  GLuint object;
  glGenTextures(1, &object);
  glBindTexture(GL_TEXTURE_2D, object);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  SDL_FreeSurface(image);

  return object;
}

void MyWindow::SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w) {
  // render front 
  glBindTexture( GL_TEXTURE_2D, object );
  glColor3f(1,1,1);
  glEnable( GL_TEXTURE_2D );

  // transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glBegin( GL_QUADS );

  glTexCoord2i( 0, 0 );
  glVertex3f( x, y, 0 );

  glTexCoord2i( 1, 0 );
  glVertex3f( x+w, y, 0 );

  glTexCoord2i( 1, 1 );
  glVertex3f( x+w, y+h, 0 );

  glTexCoord2i( 0, 1 );
  glVertex3f( x, y+h, 0 );

  glEnd();
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
