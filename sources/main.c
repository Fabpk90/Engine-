#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    TTF_Font *police = NULL;
    SDL_Color couleurNoir = {255, 255 ,255};
    SDL_Color couleurBlanche = {0,0,0};

    int continuer = 1;
    SDL_Event event;

    SDL_Surface *ecran = NULL, *ecrantitre = NULL,*texte = NULL, *icone = NULL;
    SDL_Rect positionObjet;
//placement du texte
    positionObjet.x=0;
    positionObjet.y=0;

    icone = IMG_Load("bear.ico");


    int choix;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    police = TTF_OpenFont ("Garamond.ttf",32);
    texte = TTF_RenderText_Blended(police, "®Santoro", couleurNoir);

    SDL_WM_SetIcon(icone,NULL);

    ecran = SDL_SetVideoMode(1280, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Menu", NULL);


    ecrantitre = IMG_Load("data/Tile/ecrantitre.png");


    SDL_BlitSurface(ecrantitre, NULL, ecran, &positionObjet);
    //placement image
    positionObjet.x=1150;
    positionObjet.y=660;

    SDL_BlitSurface(texte, NULL, ecran, &positionObjet);

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // Veut arrêter le jeu
                continuer = 0;
                break;
            case SDLK_KP1: // Demande à jouer
                jeu(ecran);
                break;
            case SDLK_KP2: // Demande l'éditeur de niveaux
                editeur(ecran);
                break;
            }
            break;
        }
    }
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
