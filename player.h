#ifndef PLAYER_H
#define PLAYER_H

#include "koord.h"

typedef struct Pozlista {   /* ketiranyu lancolt lista a jatekosok lepeseinek tarolasahoz, ebbol szamoljuk az o lepes vektorukat is, ezert ket 0-val kell inicializalni jatek inditasakor! */
    koord_t koord;
    struct Pozlista *next;
    struct Pozlista *prev;
} pozlista_t;

typedef struct Jatekos {
    pozlista_t poziciok;
    int player_red;
    int player_green;
    int player_blue;
    int allapot; /* 0 = nem hasznalt jatekos 1 = jatszik, 2 = kiesett, 3 = korbeert */
    char *nev;
} jatekos_t;


pozlista_t* get_player_lastpos (jatekos_t *player);
void add_koord_to_player (jatekos_t *player, koord_t *koord);
void reset_koords_of_player (jatekos_t *player);

#endif
