#include "CommonFunction.h"
#include "BaseObject.h"
#include "Ball.h"
#include "Launcher.h"
#include "Flapper.h"



BaseObject g_background;

bool initData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret< 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Pinball 6.9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window== NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen== NULL)
            success= false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags= IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success= false;
        }
    }
    return success;

}

bool loadBackground()
{
    bool ret = g_background.LoadImg("image//hihi.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window= NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (initData()== false)
        return -1;

    if (loadBackground()== false)
        return -1;

    Ball ball;
    ball.LoadImg("image//ball.png", g_screen);

    Flapper left_flapper;
    left_flapper.LoadImg("image//Flapper_l.png", g_screen);
    left_flapper.setPos(SCREEN_WIDTH/2-280,SCREEN_HEIGHT/2+120);

    Flapper right_flapper;
    right_flapper.LoadImg("image//Flapper_r.png", g_screen);
    right_flapper.setPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+120);

    Launcher launcher;


    bool is_quit= false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event)!= 0)
        {
            if (g_event.type== SDL_QUIT)
            {
                is_quit= true;
            }

            left_flapper.HandleInputAction(g_event, g_screen);
            right_flapper.HandleInputAction(g_event, g_screen);
            ball.HandleInputAction(g_event, g_screen);

        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        ball.CheckCollision();
        ball.Show(g_screen);
        ball.isRan();
        if ( ball.flag)
        {
            ball.RunBall();
        }


        left_flapper.Show_l(g_screen);
        right_flapper.Show_r(g_screen);

        SDL_RenderPresent(g_screen);

    }

    close();
    return 0;
}
