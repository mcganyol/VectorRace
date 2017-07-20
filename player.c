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


pozlista_t* get_player_lastpos (jatekos_t *player) {
    pozlista_t *iter;
    iter = &(player->poziciok);
    while (iter->next != NULL) {
        iter = iter->next;
    }
    return iter;
}

void add_koord_to_player (jatekos_t *player, koord_t *koord) {
    pozlista_t *temp;
    pozlista_t *iter;
    temp = (pozlista_t *)malloc(sizeof(pozlista_t));
    temp->koord = *koord;

    iter = get_player_lastpos(player);
    iter->next = temp;
    temp->prev = iter;
    temp->next = NULL;
}

void reset_koords_of_player (jatekos_t *player){
    pozlista_t *temp;
    pozlista_t *iter;
    iter = get_player_lastpos(player);
    while (iter->prev != NULL) {
        temp = iter;
        iter = iter->prev;
        free(temp);
        iter->next = NULL;
    }

}

