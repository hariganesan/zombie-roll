// Hari Ganesan 7/22/13
// zombie-roll: old GL rendering functions

#include "Render.hpp"

void MyWindow::renderGL() {
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
