#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "constantes.h"
#include "jeu.h"
#include "Map.h"

void jeu(SDL_Surface *ecran)
{
    TTF_Font *police = NULL;

    int continuer = 1,i,n;

    int Map[HAUTEUR][LARGEUR] = {0};
    char NomMap[NOMMAP] ;
    char Test[NOMMAP]="Foret";

    SDL_Color couleurNoir = {255, 255 ,255};
    // tous ce qui concerne le tile
    SDL_Surface  *herbe = NULL, *perso = NULL, *herbe1 = NULL,*Tile = NULL;
    // perso
    SDL_Surface *PersoUP = NULL, *PersoDOWN = NULL, *PersoLEFT = NULL, *PersoRIGHT = NULL;
    // extras de la map
    SDL_Surface *texte = NULL, *MapName = NULL;
    SDL_Rect positionObjet,positionPerso,positionNom,positionNomMap;

    herbe = IMG_Load("data/Tile/Herbe.png");
    herbe1 =  IMG_Load("data/Tile/Herbe1.png");
    Tile = IMG_Load("data/Tile/Rock.png");

    PersoUP = IMG_Load("data/Perso/mario_haut.gif");
    PersoDOWN = IMG_Load("data/Perso/mario_bas.gif");
    PersoLEFT = IMG_Load("data/Perso/mario_gauche.gif");
    PersoRIGHT = IMG_Load("data/Perso/mario_droite.gif");

    chargerMap(Map,NomMap);

    police = TTF_OpenFont ("Garamond.ttf",22);
    texte = TTF_RenderText_Blended(police, "Test", couleurNoir);
    MapName = TTF_RenderText_Blended(police, NomMap, couleurNoir);

    SDL_WM_SetCaption("Jeu", NULL);


    SDL_EnableKeyRepeat(150 , 150);
    SDL_WM_SetCaption("Jeu", NULL);
    // map
    positionObjet.x = 0;
    positionObjet.y = 0;
    //perso
    positionPerso.x = 640;
    positionPerso.y = 360;
    //nom perso
    positionNom.x = 630;
    positionNom.y = 330;
    //Nom de la map
    positionNomMap.x=590;
    positionNomMap.y=20;
    SDL_Event event;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    perso = PersoDOWN;

    for(i=0; i==HAUTEUR; i++)
    {
        for(n=0; n==LARGEUR; n++)
        {
            switch(Map[i][n])
            {
            case 0:
                SDL_BlitSurface(herbe, NULL, ecran, &positionObjet);
                break;

            case 1:
                SDL_BlitSurface(herbe1, NULL, ecran, &positionObjet);
                break;

            case 2:
                SDL_BlitSurface(Tile, NULL, ecran, &positionObjet);
                break;

            }
            positionObjet.x+=32;
        }
        positionObjet.x=0;
        positionObjet.y+= 32;
    }
    positionObjet.x=0;
    positionObjet.y=0;

    SDL_BlitSurface(perso, NULL, ecran, &positionPerso);
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

            case SDLK_RIGHT:
                if(positionPerso.x + 32 < 1280)
                {
                    positionPerso.x+=32;
                    positionNom.x+=32;
                    perso = PersoRIGHT;
                }
                break;

            case SDLK_LEFT:
                if(positionPerso.x - 32  >= 0)
                {
                    positionPerso.x-=32;
                    positionNom.x-=32;
                    perso = PersoLEFT;
                }
                break;

            case SDLK_DOWN:
                positionPerso.y+=32;
                positionNom.y+=32;
                perso = PersoDOWN;
                break;

            case SDLK_UP:
                positionPerso.y-=32;
                positionNom.y-=32;
                perso = PersoUP;
                break;
            }
            break;

        }

        for(i=0; i!=HAUTEUR; i++)
        {
            for(n=0; n!=LARGEUR; n++)
            {
                switch(Map[i][n])
                {
                case 0:
                    SDL_BlitSurface(herbe, NULL, ecran, &positionObjet);
                    break;

                case 1:
                    SDL_BlitSurface(herbe1, NULL, ecran, &positionObjet);
                    break;

                case 2:
                    SDL_BlitSurface(Tile, NULL, ecran, &positionObjet);
                    break;

                }
                positionObjet.x+=32;
            }
            positionObjet.x=0;
            positionObjet.y+= 32;
        }
        SDL_BlitSurface(perso, NULL, ecran, &positionPerso);
        SDL_BlitSurface(texte, NULL, ecran, &positionNom);
        SDL_BlitSurface(MapName, NULL, ecran, &positionNomMap);
        SDL_Flip(ecran);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        positionObjet.x=0;
        positionObjet.y=0;
    }
}

