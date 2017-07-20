#include "game.h"
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include "SDL_image.h"
#include "config.h"
#include "koord.h"
#include "player.h"
#include "map.h"
#include "utility.h"
#include "gfx.h"

int count_pozlist (jatek_t *game, int hanyadik) {
    int result = 0;
    pozlista_t *iter;
    iter = &(game->jatekosok[hanyadik].poziciok);
    while (iter->next != NULL) {
        iter = iter->next;
        result ++;
    }
    return result-1; /*2 ures lepessel fel van toltve mindig indulaskor, de egyet meg nem szamoltunk meg*/
}

int remaining_player_number (jatek_t *game) {
    int x, number;
    number = 0;
    for (x=0; x<4; x++) {
        if (game->jatekosok[x].allapot == 1) number++;
    }
    return number;
}

void set_valid_moves (jatek_t *game) { /* TODO check, hogy nem lehet masik jatekosra ralepni, nem esz nelkul mindent validda tenni! */
    koord_t temp;
    pozlista_t *last_pos;
    pozlista_t *prev_pos;

    last_pos = get_player_lastpos(&(game->jatekosok[game->kovetkezik-1])); /* -1 mert a jatekosok 1-4ig vannak sorszamozva, de a tombben 0-3ig kell szamoni :( TODO csunya igy */
    if (last_pos->prev != NULL) prev_pos = last_pos->prev; else prev_pos = last_pos; /*ha csak 1 koord volt a jatekosban*/

    temp = sub_koords(&(last_pos->koord),&(prev_pos->koord));
    game->validmoves->C =  add_koords(&(last_pos->koord), &temp);
    game->validmoves->C_valid=1;

    temp.x=1; temp.y=0;
    game->validmoves->E = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->E_valid=1;
    temp.x=0; temp.y=-1;
    game->validmoves->N = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->N_valid=1;
    temp.x=1; temp.y=-1;
    game->validmoves->NE = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->NE_valid=1;
    temp.x=-1; temp.y=-1;
    game->validmoves->NW = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->NW_valid=1;
    temp.x=0; temp.y=1;
    game->validmoves->S = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->S_valid=1;
    temp.x=1; temp.y=1;
    game->validmoves->SE = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->SE_valid=1;
    temp.x=-1; temp.y=1;
    game->validmoves->SW = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->SW_valid=1;
    temp.x=-1; temp.y=0;
    game->validmoves->W = add_koords(&(game->validmoves->C),&(temp));
    game->validmoves->W_valid=1;

}

void do_last_move(jatek_t *game) {
    pozlista_t *last_pos;
    pozlista_t *prev_pos;
    koord_t screenkord_last;
    koord_t screenkord_prev;
    koord_t aktualisan_vizsgalt;
    int vizsgalat_lepesszam;
    int i;
    double changex_permove, changey_permove; /* a koordinatak szamitasahoz*/

    last_pos = get_player_lastpos(&(game->jatekosok[game->kovetkezik-1]));
    if (last_pos->prev != NULL) prev_pos = last_pos->prev; else prev_pos = last_pos;

    screenkord_last = get_screenpos_of_koord(&(last_pos->koord));
    screenkord_prev = get_screenpos_of_koord(&(prev_pos->koord));

    vizsgalat_lepesszam = getMax(abs(screenkord_last.x-screenkord_prev.x), abs(screenkord_last.y-screenkord_prev.y)) +1; /*ennyi keppontot kell atnezni, plussz egy azert mert az indulo pontot is megnezzuk...*/
    changex_permove = (0.0+screenkord_last.x-screenkord_prev.x)/getMax((vizsgalat_lepesszam -1),1); /* 0-val nem osztunk */
    changey_permove = (0.0+screenkord_last.y-screenkord_prev.y)/getMax((vizsgalat_lepesszam -1),1); /* 0-val nem osztunk */
    for (i=0; i<vizsgalat_lepesszam; i++) {
        aktualisan_vizsgalt.x = round(screenkord_prev.x + changex_permove*i);
        aktualisan_vizsgalt.y = round(screenkord_prev.y + changey_permove*i);
        if (((char*)(game->palya->palyakep->pixels))[get_arraynumber_of_screenkoord(&(aktualisan_vizsgalt))] == game->palya->palya_color) {
            game->jatekosok[game->kovetkezik -1].allapot = 2; break;
        }
        if (((char*)(game->palya->palyakep->pixels))[get_arraynumber_of_screenkoord(&(aktualisan_vizsgalt))] == game->palya->start_color) {
            game->jatekosok[game->kovetkezik -1].allapot = 2; break;
        }
        if (((char*)(game->palya->palyakep->pixels))[get_arraynumber_of_screenkoord(&(aktualisan_vizsgalt))] == game->palya->finish_color) {
            game->jatekosok[game->kovetkezik -1].allapot = 3; break;
        }
    }
}

void set_next_active_player (jatek_t *game) {
    int eddig_aktiv;
    int x;
    eddig_aktiv = game->kovetkezik; /* ez egy int 1-4 */
    for (x = eddig_aktiv; x<10 ; x++) { /*TODO, innen kiirtani a magikus 10-est. most arra valo, hogy mindenkire biztosan legalbb egyszer ralepjunk*/
        if (game->jatekosok[x%4].allapot == 1) {game->kovetkezik = (x%4)+1; return; }
    }
    game->allapot = 2;
    Draw_end_menu(game);
}

void lep(jatek_t *game, koord_t *destination){
    add_koord_to_player(&(game->jatekosok[game->kovetkezik-1]), destination); /*TODO az a kovetkezik-1 a jatekos sorszama es a tombben levo helye miatt van, javitani */ /*itt betesszuk a pozlistba a valasztasat */
    do_last_move(game);     /*meglepjuk az utolso mozgasat, majd az a fv kiejti ha falnak ment vagy gyoz ha celon ment at*/
    set_next_active_player(game); /*beallitjuk a kovetkezo aktiv jatekost lepesre. ha nincsen akkor majd az a fv a jatek allapotat befejezettre teszi */
    set_valid_moves(game);
}

