#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "Map.h"
void chargerMap(int *Map[][LARGEUR], char *NomMap)
{
    int i,n,InfoMap;
    FILE *map = NULL;

    map = fopen("map/map.jeu","r+");

    for(i=0; i!=HAUTEUR; i++)
    {
        for(n=0; n!=LARGEUR; n++)
        {
            InfoMap = fgetc(map);
            switch(InfoMap)
            {
            case '0':
                Map[i][n] = 0;
                break;

            case '1':
                Map[i][n] = 1;
                break;

            case '2':
                Map[i][n] = 2;
                break;
            }
        }
    }
    fgetc(map);
    fgets(NomMap, NOMMAP,map);
    fclose(map);
}

void SauvegarderMap(int *Map[][LARGEUR])
{
    int i,n;
    FILE *map = NULL;

    map = fopen("map/map.jeu","r+");

    for(i=0; i!=HAUTEUR; i++)
    {
        for(n=0; n!=LARGEUR; n++)
        {
            fprintf(map,"%d",Map[i][n]);
        }
    }
    fclose(map);
}
