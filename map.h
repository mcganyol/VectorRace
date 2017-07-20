#ifndef MAP_H
#define MAP_H
#include "koord.h"
#include <SDL.h>

typedef struct Palya {  /* ez maga a betoltott gif a bajt tombje */
    SDL_Surface *palyakep, *rajzolando_palyakep; /* a rajzolandorol levesszuk a start-ot es a starting colorokat */
    koord_t p1start;
    koord_t p2start;
    koord_t p3start;
    koord_t p4start;
    char palya_color,start_color,finish_color,p1start_color,p2start_color,p3start_color,p4start_color,metadata_color,transparent_color;
} palya_t;

typedef struct Palyalista { /*ketiranyu lancolt lista */
    char name[20+1];
    struct Palyalista *next;
    struct Palyalista *prev;
} palyalista_t;

void init_map (char *a, palya_t *palya);       /* betolti a palya kepet, beteszi a palyaba a megjelenitendo surface-t is, es a jatekosok kezdohelyet is */
void build_maplist(palyalista_t **palyalista);  /* atvett lib, hogy a palyak listajat sikeruljon kiolvasni. a palyak listajat felepitem, egy duplan lancolt korlistaba */

#endif
