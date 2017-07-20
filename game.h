#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"

typedef struct CurrentValidMoves {
    koord_t NW,N,NE,W,C,E,SW,S,SE;
    int NW_valid,N_valid,NE_valid,W_valid,C_valid,E_valid,SW_valid,S_valid,SE_valid;
} CurrentValidMoves;

typedef struct Jatek {
    jatekos_t jatekosok[4];
    palya_t *palya;
    SDL_Surface *surface;
    CurrentValidMoves *validmoves;
    int allapot; /* 0 = fomenu, 1 = jatszunk, 2 = gameover kiirva */
    int kovetkezik;
} jatek_t;


int count_pozlist (jatek_t *game, int hanyadik);
int remaining_player_number (jatek_t *game);
void set_valid_moves (jatek_t *game); /* TODO check, hogy nem lehet masik jatekosra ralepni, nem esz nelkul mindent validda tenni! */
void do_last_move(jatek_t *game);
void set_next_active_player (jatek_t *game);
void lep(jatek_t *game, koord_t *destination);

#endif
