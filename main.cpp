#include "CommonFunction.h"
#include "BaseObject.h"
#include "Ball.h"
#include "Launcher.h"
#include "Flapper.h"
#include "FlapperCollision.h"
#include "Bump.h"
#include "TextObject.h"
#include "Menu_game.h"

BaseObject g_background;
TTF_Font* font_time = NULL;

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

            if(TTF_Init()==-1)
            {
                success=false;
            }
            font_time=TTF_OpenFont("font//dlxfont.ttf",15);
            if(font_time==NULL)
            {
                success=true;
            }
            if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
                success=false;
    }
    return success;

}

bool loadBackground()
{
    bool ret = g_background.LoadImg("image//test1.png", g_screen);
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

    bool notQuit = false;
    bool isPlayAgain = false;
    while (!notQuit)
    {
        MenuGame g_menu;
        if (!isPlayAgain)
        {
            g_menu.Menu_game(g_screen,g_window);
        }

    /** Load Component */

        Ball* ball = NULL;
        ball = new Ball;
        ball->LoadImg("image//ball_true.png", g_screen);

        Flapper* left_flapper = NULL;
        left_flapper = new Flapper;
        left_flapper->LoadImg("image//Flapper_le.png", g_screen);
        left_flapper->setPos(FLAPPER_LEFT_X_POS-52.5,FLAPPER_LEFT_Y_POS-16.5);

        Flapper* right_flapper = NULL;
        right_flapper = new Flapper;
        right_flapper->LoadImg("image//Flapper_ri.png", g_screen);
        right_flapper->setPos(FLAPPER_RIGHT_X_POS-56.5, FLAPPER_RIGHT_Y_POS-16.5);

        FlapperCollision* left = NULL;
        left = new FlapperCollision;
        left->SetPos(FLAPPER_LEFT_X_POS, FLAPPER_LEFT_Y_POS);

        FlapperCollision* right = NULL;
        right = new FlapperCollision;
        right->SetPos(FLAPPER_RIGHT_X_POS, FLAPPER_RIGHT_Y_POS);

        Launcher* launcher = NULL;
        launcher = new Launcher;
        launcher->LoadImg("image//Launcher1.png", g_screen);
        launcher->setPos(500, 340);

        Bump left_triangle, right_triangle;
        left_triangle.LoadImg("image//Triangle_le.png", g_screen);
        right_triangle.LoadImg("image//Triangle_ri.png", g_screen);
        left_triangle.setPos(LEFT_TRIANGLE_X_POS, LEFT_TRIANGLE_Y_POS);
        right_triangle.setPos(RIGHT_TRIANGLE_X_POS, RIGHT_TRIANGLE_Y_POS);

        Bump circle_100, circle_50, circle_25;
        circle_100.LoadImg("image//Circle_100.png", g_screen);
        circle_50.LoadImg("image//Circle_50.png", g_screen);
        circle_25.LoadImg("image//Circle_25.png", g_screen);
        circle_100.setPos(CIRCLE_100_X_POS, CIRCLE_100_Y_POS);
        circle_50.setPos(CIRCLE_50_X_POS, CIRCLE_50_Y_POS);
        circle_25.setPos(CIRCLE_25_X_POS, CIRCLE_25_Y_POS);

        Bump goc_tren, chan_ngang, chan_ngang_1, thanh_doc;
        goc_tren.LoadImg("image//goc_tren.png", g_screen);
        chan_ngang.LoadImg("image//chan_ngang.png", g_screen);
        chan_ngang_1.LoadImg("image//thanh_chan_2.png", g_screen);
        thanh_doc.LoadImg("image//thanh_doc.png", g_screen);
        goc_tren.setPos(400, 0);
        chan_ngang.setPos(0, 420);
        chan_ngang_1.setPos(500, 200);
        thanh_doc.setPos(450, 200);


        bool is_quit= false;
        while(!is_quit)
        {
            while(SDL_PollEvent(&g_event)!= 0)
            {
                if (g_event.type== SDL_QUIT)
                {
                    is_quit= true;
                }

                left_flapper->HandleInputAction(g_event, g_screen);
                right_flapper->HandleInputAction(g_event, g_screen);
                ball->HandleInputAction(g_event, g_screen);
                left->HandleInputAction(g_event, g_screen);
                right->HandleInputAction(g_event, g_screen);

            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);
            left_triangle.Show(g_screen);
            right_triangle.Show(g_screen);

            circle_100.Show(g_screen);
            circle_50.Show(g_screen);
            circle_25.Show(g_screen);

            thanh_doc.Show(g_screen);
            goc_tren.Show(g_screen);
            chan_ngang.Show(g_screen);

            if (ball->isBallOutOfLauncher())
            {
                chan_ngang_1.Show(g_screen);
            }

            launcher->Show(g_screen, ball);

            ball->CheckCollision();
            ball->Show(g_screen);
            ball->isRan();
            if (ball->flag)
            {
                ball->RunBall();
            }
            TextObject text_score("Score: ");
            text_score.str_+=std::to_string(ball->score);
            text_score.renderTexture(text_score.GetText(25, g_screen), g_screen, 20, 20);
            text_score.DestroyText();

            left->CheckAndHandleFlapperCollision(ball, left_flapper, right_flapper);
            right->CheckAndHandleFlapperCollision(ball, left_flapper, right_flapper);

            left_flapper->Show_l(g_screen);
            right_flapper->Show_r(g_screen);
            left->DrawFlapper_l(g_screen);
            right->DrawFlapper_r(g_screen);

            SDL_RenderPresent(g_screen);

            if (ball->isGameOver())
            {
                is_quit= true;
                delete ball;
                delete left, right;
                delete left_flapper, right_flapper;
                delete launcher;
                g_menu.SaveHighScore(ball->score);
                if (g_menu.Play_again(g_screen,g_window,ball->score))
                {
                    isPlayAgain= true;
                }
                else
                {
                    isPlayAgain= false;
                }
            }
        }

    }

    return 0;
}
