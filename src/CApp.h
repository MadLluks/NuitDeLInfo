#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
class CApp {
    private:
        bool Running;
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        SDL_Texture* gTexture;
        SDL_Texture* gTexture2;
 
    public:
        CApp();
 
        int OnExecute();
 
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
 
        void OnRender();
 
        void OnCleanup();

        SDL_Texture* loadTexture(std::string path);

        bool loadMedia();
};
 
#endif
