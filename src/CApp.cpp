#include "CApp.h"

CApp::CApp() {
    Running = true;
}

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
 
    if((gWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN)) == NULL) {
        return false;
    }
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
    	return false;
    }
 
    return true;
}

SDL_Texture* CApp::loadTexture(std::string path){
	SDL_Texture* res = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface == NULL){
	} else {
		res = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(res == NULL){
		}
		SDL_FreeSurface(loadedSurface);
	}
	return res;
}

bool CApp::loadMedia() {
	gTexture = loadTexture("test.jpg");
	if( gTexture == NULL ) {
		return false;
	}
	return true;
}

void CApp::OnCleanup() {
	SDL_DestroyTexture(gTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
    SDL_Quit();
}

void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }
 
    loadMedia();
    SDL_Event Event;
 
    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }
 
    OnCleanup();
 
    return 0;
}

int main(int argc, char** argv) {
    CApp theApp;

    return theApp.OnExecute();
}
