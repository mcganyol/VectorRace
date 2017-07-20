#ifndef GFX_H
#define GFX_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include "SDL_image.h"
#include "config.h"
#include "koord.h"
#include "game.h"
#include "player.h"
#include "map.h"
#include "utility.h"
#include "gfx.h"

void clrscr (SDL_Surface *screen);
void Draw_on_surface (SDL_Surface *destsrf, SDL_Surface *fromsrf);
void Draw_main_menu (SDL_Surface *screen);
void Draw_end_menu (jatek_t *game);
void Draw_info_pane (SDL_Surface *screen, char *line1, char *line2); /*writes two lines to right-left info pane*/
void Draw_checkered_paper_effect (SDL_Surface *screen, int distance);
void Draw_valid_moves (jatek_t *game);
void Draw_move (koord_t *from, koord_t *to, jatek_t *game, int playernumber); /*ezek meg jatekkoordinatak at kell forditani screen koordinataba! */
void Draw_player_pos (koord_t *koord, jatek_t *game, int playernumber);
void Draw_all_players_moves (jatek_t *game);
void Draw_refresh_gamescreen (jatek_t *game);

#endif
