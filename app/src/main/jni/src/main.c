#include "SDL.h"
#include "stdio.h"
#include "log.h"


int main(int argc, char *argv[]) {
    LOGD("test SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        LOGD("SDL_Init Error: ");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL){
        LOGD("SDL_CreateWindow Error: ");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        LOGD("SDL_CreateRenderer Error: ");
        SDL_Quit();
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("/sdcard/z_native.bmp");
    if (bmp == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        LOGD("SDL_LoadBMP Error: ");
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        LOGD("SDL_CreateTextureFromSurface Error: ");
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 3; ++i){
        //First clear the renderer
        SDL_RenderClear(ren);
        //Draw the texture
        SDL_RenderCopy(ren, tex, NULL, NULL);
        //Update the screen
        SDL_RenderPresent(ren);
        //Take a quick break after all that hard work
        SDL_Delay(1000);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}