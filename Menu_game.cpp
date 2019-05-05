#include"Menu_game.h"

MenuGame::MenuGame()
{
    ;
}

MenuGame::~MenuGame()
{
    ;
}

void MenuGame::open_high_score(SDL_Renderer* ren){
    SDL_Texture *table_high_score = LoadPNG("image//hihi.png", ren);
    renderTexture(table_high_score, ren, 200, 100, 400, 400);
    std::ifstream high_score("high score.txt");
    std::vector <TextObject> score;
    while(!high_score.eof()){
        std::string a;
        high_score >> a;
        TextObject b(a);
        score.push_back(b);
    }
    for(int i=0; i<score.size() & i<10; i++){
        BaseObject::renderTexture(score[i].GetText(20, ren), ren, SCREEN_WIDTH/2-10 , 200+25*i);
    }
    high_score.close();

    SDL_RenderPresent(ren);
    waitUntilKeyPressed();
}

void MenuGame::Menu_game(SDL_Renderer* ren, SDL_Window* window){
    SDL_Texture* menu_screen=LoadPNG("image//blankgame.png", ren);
    SDL_Texture* choose_start = LoadPNG("image//New_game.png", ren);
    SDL_Texture* choose_high_score = LoadPNG("image//High_score.png", ren);
    SDL_Texture* choose_quit = LoadPNG("image//Quit.png", ren);
    if (menu_screen== nullptr || choose_start==nullptr || choose_high_score==nullptr ||
         choose_quit==nullptr)
        {
        SDL_DestroyTexture(menu_screen);
        SDL_DestroyTexture(choose_start);
        SDL_DestroyTexture(choose_high_score);
        SDL_DestroyTexture(choose_quit);

        }


    renderTexture(menu_screen,ren,0,0);
    while(!playing)
    {
        SDL_RenderPresent(ren);

        SDL_Delay(10);

            if ( SDL_WaitEvent(&m_event) == 0) continue;

           if (m_event.type == SDL_QUIT)
               BaseObject::Destroy(menu_screen,window,ren);

            if(m_event.type == SDL_MOUSEMOTION)
            {
                x = m_event.motion.x;
                y = m_event.motion.y;


             if(left<=x && x<=right && y_play<=y && y<= y_play+high)
                {
            y=y_play;
            renderTexture(choose_start, ren, 0, 0);
                }

        else if(left<=x && x<=right && y_hs<=y && y<= y_hs+high)
            {
            y=y_hs;
            renderTexture(choose_high_score, ren, 0, 0);
            }
        else if(left<=x && x<=right && y_quit<=y && y<= y_quit+high)
            {
            y=y_quit;
            renderTexture(choose_quit, ren, 0, 0);
            }

        else
            {
            x=left;
            y = 0;
            renderTexture(menu_screen, ren,0, 0);
            }

        }

            else if(m_event.type== SDL_MOUSEBUTTONDOWN)
            {
                x = m_event.motion.x;
                y = m_event.motion.y;
            if(m_event.button.button== SDL_BUTTON_LEFT or m_event.button.button== SDL_BUTTON_RIGHT )
            {
                if(left<=x && x<=right && y_play<=y && y<= y_play+high)
                    {
                            playing = true;
                    }

                else if(left<=x && x<=right && y_hs<=y && y<=y_hs+high)
                    {
                            open_high_score(ren);
                    }


                else if(left<=x && x<=right && y_quit<=y && y<= y_quit+high)
                    {
                    BaseObject::Destroy(menu_screen,window,ren);
                    }
                }
            }
    }
}

bool MenuGame::Play_again(SDL_Renderer* ren, SDL_Window* window, int score)
{

    SDL_Texture* try_again= LoadPNG("image//e_try",ren);
    SDL_Texture* e_background= LoadPNG("image//e_background",ren);
    SDL_Texture* e_quit= LoadPNG("image//e_quit",ren);

    TextObject YourScore("Your Score: ");
    YourScore.str_ += std::to_string(score);
    SDL_Texture* your_text = YourScore.GetText(30,ren);

    BaseObject::renderTexture(e_background,ren,0,0);
    int x,y;
    while(true)
    {
        BaseObject::renderTexture(your_text, ren, SCREEN_WIDTH/2 , SCREEN_HEIGHT/2);
        SDL_RenderPresent(ren);
        if (SDL_WaitEvent(&m_event) == 0) continue;

        if (m_event.type == SDL_QUIT)
            return false;
//            Try again l�:  - 421
//Quit l� 303 - 421
//W:129
//H:83
        else if(m_event.type == SDL_MOUSEMOTION){
            x = m_event.motion.x;
            y = m_event.motion.y;
            if(116<=x && x <=116+129 && 421<=y && y<= 421+83)
                renderTexture(try_again, ren, 0, 0);
            else if(303<=x && x <=303+129 && 421<=y && y<= 421+83)
                renderTexture(e_quit, ren, 0, 0);
            else
                renderTexture(e_background,ren, 0, 0);
        }
        else if(m_event.type== SDL_MOUSEBUTTONDOWN)
            if(m_event.button.button == SDL_BUTTON_LEFT){
                if(116<=x && x <=116+129 && 421<=y && y<= 421+83)
                    return true;
                else if(303<=x && x <=303+129 && 421<=y && y<= 421+83)
                    return false;
            }
    }

}
