// ============================================================================
// [Include Section]
// ============================================================================
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Element.hpp"
#include <iostream>
#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>



// ============================================================================
// [SdlApplication]
// ============================================================================
#define APPTITLE "SDL Template Program"
#define JSMN_STRICT true
// SdlApplication is nothing more than thin wrapper to SDL library. You need
// just to instantiate it and call run() to enter the SDL event loop.
struct SdlApplication
{
	SdlApplication();
	~SdlApplication();
	
	// Application state (just convenience instead of 0, 1, ...).
	enum APP_STATE
	{
		APP_OK = 0,
		APP_FAILED = 1
	};
	
	// Initialize application, called by run(), don't call manually.
	int init(int width, int height);
	
	// Destroy application, called by destructor, don't call manually.
	void destroy();
    void createMain();
    Element * main = NULL;
	// Run application, called by your code.
	int run(int width, int height);
	
	// Called to process SDL event.
	void onEvent(SDL_Event* ev, Element mainElement);
	
	// Called to render content into buffer.
	void Render(Element mainElement);
	
	// Whether the application is in event loop.
	bool _running;
	SDL_Window *win;
	SDL_Renderer *renderer;
};

SdlApplication::SdlApplication() :
_running(false)
{
   
}

SdlApplication::~SdlApplication()
{
	destroy();
}

static inline void *realloc_it(void *ptrmem, size_t size) {
    void *p = realloc(ptrmem, size);
    if (!p)  {
        free (ptrmem);
        fprintf(stderr, "realloc(): errno=%d\n", errno);
    }
    return p;
}


static int dump(const char *js, jsmntok_t *t, size_t count, int indent) {
    int i, j, k;
    if (count == 0) {
        return 0;
    }
    if (t->type == JSMN_PRIMITIVE) {
        printf("%.*s", t->end - t->start, js+t->start);
        return 1;
    }
    if (t->type == JSMN_UNDEFINED) {
        printf("undefined type");
    }
    if (t->type == JSMN_STRING) {
        printf("'%.*s'", t->end - t->start, js+t->start);
        return 1;
    }
    if (t->type == JSMN_OBJECT) {
        printf("\n");
        j = 0;
        for (i = 0; i < t->size; i++) {
            for (k = 0; k < indent; k++) printf("  ");
            j += dump(js, t+1+j, count-j, indent+1);
            printf(": ");
            j += dump(js, t+1+j, count-j, indent+1);
            printf("\n");
        }
        return j+1;
    }
    if (t->type == JSMN_ARRAY) {
        j = 0;
        printf("\n");
        for (i = 0; i < t->size; i++) {
            for (k = 0; k < indent-1; k++) printf("  ");
            printf("   - ");
            j += dump(js, t+1+j, count-j, indent+1);
            printf("\n");
        }
        return j+1;
    }
    return 0;
}


static int domain() {
    int r;
    int eof_expected = 0;
    char somebuffer[100] = "{\"test\":2}\0";
    
    char *js =somebuffer;
    size_t jslen = 11;
    char buf[BUFSIZ];
    
    jsmn_parser p;
    jsmntok_t *tok;
    size_t tokcount = 10;
    
    /* Prepare parser */
    jsmn_init(&p);
    
    /* Allocate some tokens as a start */

    tok = (jsmntok_t*) malloc(sizeof(*tok) * tokcount);
    if (tok == NULL) {
        fprintf(stderr, "malloc(): errno=%d\n", errno);
        return 3;
    }
    

    jsmn_parse(&p, js, jslen, tok, tokcount);
      
    dump(js, tok, p.toknext, 0);
    
    return EXIT_SUCCESS;
}


void SdlApplication::createMain() {
    
}

int SdlApplication::init(int width, int height)
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
    
    if (TTF_Init() < 0) {
        // Error handling code
    }
    

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    int Buffers, Samples;
    SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &Buffers );
    SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &Samples );
    cout << "buf = " << Buffers << ", samples = " << Samples << ".";
	
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
	win = SDL_CreateWindow(APPTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,   SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    domain();
	// Success.
	return APP_OK;
}

void SdlApplication::destroy()
{
	if (win)
	{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
}

int SdlApplication::run(int width, int height)
{
	// Initialize application.
	int state = init(width, height);
	if (state != APP_OK) return state;
	
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;
  
    Element mainElement = new Element(NULL);
    mainElement.width = 800;
    mainElement.height = 600;
    mainElement.heightType = pixel;
    mainElement.widthType = pixel;
    mainElement.backgroundColor = {  0x00, 0x90, 0xC0, 0x55 };
    mainElement.name = "Main";
    mainElement.setSpace(32);
    
    Element blueBox = new Element(mainElement);
    blueBox.setDistance(32);
    blueBox.setSpace(32);
    blueBox.backgroundColor = {20, 80, 180, 255};
    blueBox.widthType = pixel;
    blueBox.width = 500;
    blueBox.flowType = horizontal;
    blueBox.heightType = pixel;
    blueBox.height = 500;
    blueBox.name = "Blue Box";
    mainElement.subelements.push_back(&blueBox);

    Element redBox  =  new Element(&blueBox);
    redBox.setSpace(32);
    redBox.setDistance(32);
    redBox.width = 40;
    redBox.widthType = pixel;
    redBox.height = 40;
    redBox.heightType = pixel;
    redBox.backgroundColor = { 120, 30, 30, 255 };
    redBox.flowType = horizontal;
    redBox.name = "Red Box";
    blueBox.subelements.push_back(&redBox);
    
    Element greenBox  =  new Element(&blueBox);
    greenBox.setSpace(32);
    greenBox.setDistance(32);
    greenBox.width = 80;
    greenBox.widthType = percent;
    greenBox.height = 10;
    greenBox.heightType = pixel;
    greenBox.backgroundColor = {0, 140, 50, 255};
    greenBox.flowType = horizontal;
    greenBox.name = "Green Box";
    blueBox.subelements.push_back(&greenBox);
    
    Element greenBox2  =  new Element(&blueBox);
    greenBox2.setSpace(32);
    greenBox2.setDistance(32);
    greenBox2.width = 45;
    greenBox2.widthType = pixel;
    greenBox2.height = 45;
    greenBox2.heightType = pixel;
    greenBox2.backgroundColor = {150, 120, 50, 255};
    greenBox2.flowType = horizontal;
    greenBox2.name = "Green Box 2";
    blueBox.subelements.push_back(&greenBox2);
    
    Element greenBox3  =  new Element(&blueBox);
    greenBox3.setSpace(32);
    greenBox3.setDistance(32);
    greenBox3.width = 45;
    greenBox3.widthType = pixel;
    greenBox3.height = 45;
    greenBox3.heightType = pixel;
    greenBox3.backgroundColor = {150, 120, 50, 255};
    greenBox3.flowType = horizontal;
    greenBox3.name = "Green Box 3";
    blueBox.subelements.push_back(&greenBox3);

    mainElement.render(0, 0);
    
	while (SDL_WaitEvent(&ev))
	{
		onEvent(&ev, mainElement);
		Render(mainElement);
		
		if (_running == false)
		{
			break;
		}
	}
	
	return APP_OK;
}

void SdlApplication::onEvent(SDL_Event* ev, Element mainElement)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			_running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if (ev->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
		}
        break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            Element *element = mainElement.findElement(x, y);
            if (element != NULL) {
                    cout << "Mouse down" << x << " " << y << element->name;
                element->backgroundColor = {0x00, 0x00, 0xFF, 0XFF};
            }
            
        break;
	}
}



void SdlApplication::Render(Element mainElement)
{
	SDL_Rect r;
	int w,h;
	SDL_GetWindowSize(win, &w, &h);
	
	r.w = 200;
	r.h = 200;
	r.x = w/2-(r.w/2);
	r.y = h/2-(r.h/2);
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0, 0xff);
	SDL_RenderFillRect(renderer, &r);
    mainElement.paint(renderer);
    char msg[20] = "Hoi joel";
    char * txt = msg;
    
    mainElement.drawText(renderer,txt,50, 50, 15, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}


// ============================================================================
// [Entry-Point]
// ============================================================================

int main(int argc, char* argv[])
{
	SdlApplication app;
	return app.run(640, 480);
}
