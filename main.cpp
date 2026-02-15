#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "scr/bullet.h"
#include "scr/player.h"
#include "scr/renderer.h"
#include "scr/asteroid.h"
#include "scr/menu.h"
#include "scr/game.h"


bool RunningGame =  true;

int screen_W = 850;
int screen_H = 950;
bool died = false;
bool Respawn = false;
bool colide = false;

SDL_Color color = { 255, 255, 255 };
SDL_Color color2 = { 255, 255, 255 };
SDL_Color color3 = { 255, 255, 0 };
TTF_Font *font;

void playerMoveCor(){
    if(playerMoveDown) {
        playerCor.y += speed;
    }
    if(playerMoveUp) {
        playerCor.y -= speed;
    }
    if(playerMoveLeft) {
        playerCor.x -= speed;
    }
    if(playerMoveRight) {
        playerCor.x += speed;
    }

    if(playerCor.x < 0) {
        playerCor.x += speed;
    }
    if(playerCor.y < 0) {
        playerCor.y += speed;
    }
    if(playerCor.y > (screen_H - playerCor.h)) {
        playerCor.y -= speed;
    }
    if(playerCor.x > (screen_W - playerCor.w)) {
        playerCor.x -= speed;
    }
}


int main(int argc, char const *argv[])
{

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    
	SDL_Window * window = SDL_CreateWindow("Space Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_W, screen_H, 0);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0); //SDL_RENDERER_ACCELERATED

    // INIT SDL2_image under .png
    IMG_Init(IMG_INIT_PNG);

    TTF_Init();
    font = TTF_OpenFont("assets/ttf/Arial.ttf", 96);
    TTFLoad(font, color, renderer);
    TTFPrepare(renderer);

	std::cout << "Main thread Init" << std::endl;

    Uint32 time = SDL_GetTicks();

	Uint32 startTime = SDL_GetTicks();
    float frameCount = 0;
    
    int fps = 60;
	int desiredDelta = 1000 / fps;

    RendererInit(screen_H, screen_W, renderer);
    PlayerInit(screen_H, screen_W);
    AsteroidInit();
    MenuInit(screen_H, screen_W);
    BulletInit();

    MenuLoadTTF(font, color2, color3);
    MenuPrepare(renderer);

    MenuLoop(window, font, renderer);
    if (quit)
    {
        CleanRendererTextures();
        CleanRendererSurfaces();
        TTF_CloseFont(font);

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        Mix_Quit();
        exit(0);
    }

	while(RunningGame) {

		int startLoop = SDL_GetTicks();

        frameCount++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - startTime >= 1000) { // 1000 ms = 1 sec
            std::cout << "\n";
            fps = frameCount;
            frameCount = 0;
            startTime = currentTime;
            std::cout << "FPS: " << fps << "\n";
            std::cout << "Difficulty: " << difficulty << "\n"; 
            if(!died){
                playerUpdate();
            }

            std::cout << "Draw Calls: " << drawCalls << "\n";
            std::cout << "bullet Count: " << bullets.size() << "\n";
        }
        //FPS counter
        drawCalls = 0;

        Uint32 nowTime = SDL_GetTicks();
        if (nowTime - time >= difficulty){
            NewAsteroid(screen_W - 100);
            time = nowTime;
        }


        playerMoveCor();
        playerBorderColide(screen_H, screen_W);

        AsteroidMove();
        BulletMove();

        AsteroidUpdate(screen_H, screen_W);
        BulletUpdate(screen_H,screen_W);

        AsteroidBulletCollide();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        RendererDrawBg(renderer);
        DrawPlayer(renderer, playerIMG);
        RendererDrawAsteroid(asteroids, renderer);
        TTFUpdate(renderer, font, color);
        TTFRenderSpecial(renderer);
        RenderMissile(renderer, bullets);

        if(PlayerColideAsteroidCheck(asteroids,playerCor) or died){
            died = true;
            TTFRenderDied(renderer);
            playerReset();
        } else{
            PlayerShoots();
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

		SDL_Event Event;
        while (SDL_PollEvent(&Event)){

            if (!died) {
                PlayerMove(Event);
            }



            Respawn = PlayerRespawn(Event);

            if(Respawn) {
                AsteroidReset();
                BulletClearBullet();
                PlayerInit(screen_H, screen_W);
                Respawn = false;
                died = false;
                colide = false;
            }

            PlayerShootKeyPress(Event);

            if (Event.type == SDL_QUIT) {
                CleanRendererTextures();
                CleanRendererSurfaces();
                MenuCleanUp();
                TTF_CloseFont(font);

		    	IMG_Quit();
		    	SDL_DestroyRenderer(renderer);
		    	SDL_DestroyWindow(window);
		    	TTF_Quit();
		    	SDL_Quit();
                Mix_Quit();
		    	exit(0);
            }
        }
        int delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
    }
    return 0;
}