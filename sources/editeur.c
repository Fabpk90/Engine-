#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "editeur.h"
#include "constantes.h"
#include "Map.h"
typedef enum Tile Tile;
enum Tile
{
    HERBE = 0 , HERBE1 = 1, ROCK = 2, ARBRE = 3
};

void editeur(SDL_Surface *ecran)
{
    TTF_Font *police = NULL;

    int continuer = 1,i,n,posx,posy;
    int Map[HAUTEUR][LARGEUR] = {0};
    char NomMap[NOMMAP];

    SDL_Color couleurNoir = {0, 0 ,0};
    SDL_Surface  *herbe = NULL, *perso = NULL, *herbe1 = NULL,*rock = NULL,*tree = NULL,*Mouse = NULL, *texte = NULL;//Mouse = l'objet a poser
    SDL_Rect positionObjet,positionPerso,positionObjetTile,positionTexte;

    Tile superTile = HERBE1;

    herbe = IMG_Load("data/Tile/Herbe.png");
    herbe1 =  IMG_Load("data/Tile/Herbe1.png");
    rock = IMG_Load("data/Tile/Rock.png");
    perso = IMG_Load("data/Tile/A.png");
    tree = IMG_Load("data/Tile/tree.png");

    Mouse = herbe1; //Tile de base pour la souris

    SDL_WM_SetCaption("Editeur", NULL);

    chargerMap(Map,NomMap);

    // texte map
    police = TTF_OpenFont ("Garamond.ttf",32);
    texte = TTF_RenderText_Blended(police, "Map Saved", couleurNoir);
    positionTexte.x=1050;
    positionTexte.y=660;


    SDL_EnableKeyRepeat(150 , 150);
    SDL_WM_SetCaption("Jeu", NULL);

    // map
    positionObjet.x = 0;
    positionObjet.y = 0;

    //perso
    positionPerso.x=640;
    positionPerso.y=360;


    SDL_Event event;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    // premiere boucle pour la map

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
                SDL_BlitSurface(rock, NULL, ecran, &positionObjet);
                break;

            case 3:
                SDL_BlitSurface(tree, NULL, ecran, &positionObjet);
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
                if(positionPerso.x + 32 <= 720)
                    positionPerso.x+=32;
                break;

            case SDLK_LEFT:
                if(positionPerso.x + 32 > 0)
                    positionPerso.x-=32;
                break;

            case SDLK_DOWN:
                positionPerso.y+=32;
                break;

            case SDLK_UP:
                positionPerso.y-=32;
                break;

            case SDLK_w:
                SauvegarderMap(Map);
                texte = TTF_RenderText_Blended(police, "Map Saved", couleurNoir);
                break;

            case SDLK_KP1:
                superTile = HERBE1;
                Mouse = herbe1;
                break;

            case SDLK_KP2:
                superTile = ROCK;
                Mouse = rock ;
                break;

            }
            break;

        case SDL_MOUSEMOTION:
            positionObjetTile.x = event.motion.x;
            positionObjetTile.y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
                posx = event.button.x / 32;
                posy = event.button.y / 32;
                Map[posy][posx] = superTile;
                texte = TTF_RenderText_Blended(police, "Map Not Saved", couleurNoir);
                break;

            case SDL_BUTTON_RIGHT:
                posx = event.button.x / 32;
                posy = event.button.y / 32;
                Map[posy][posx] = 0;
                texte = TTF_RenderText_Blended(police, "Map Not Saved", couleurNoir);
                break;
            }
            break;
        }

    //Blittage de la map dans la boucle
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
                    SDL_BlitSurface(rock, NULL, ecran, &positionObjet);
                    break;

                case 3:
                    SDL_BlitSurface(tree, NULL, ecran, &positionObjet);
                    break;
                }
                positionObjet.x+=32;
            }
            positionObjet.x=0;
            positionObjet.y+= 32;
        }
        SDL_BlitSurface(perso, NULL, ecran, &positionPerso);
        SDL_BlitSurface(Mouse, NULL, ecran, &positionObjetTile);
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
        SDL_Flip(ecran);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        positionObjet.x=0;
        positionObjet.y=0;
    }
}
