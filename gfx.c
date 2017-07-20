#include "gfx.h"

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

void clrscr (SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, 0xFAFAFA);
}

void Draw_on_surface (SDL_Surface *destsrf, SDL_Surface *fromsrf) {
    SDL_Rect src, dest;
    src.x = 0;
    src.y = 0;
    src.w = fromsrf->w;
    src.h = fromsrf->h;
    dest.x = 0;
    dest.y = 0;
    dest.w = destsrf->w;
    dest.h = destsrf->h;
    SDL_BlitSurface(fromsrf, &src, destsrf, &dest);
}

void Draw_main_menu (SDL_Surface *screen) {
    SDL_Rect *background;
    background = (SDL_Rect*) malloc(sizeof(SDL_Rect));
    if (background == NULL) { exit(9); }
    background->h = 20 * (6+1); /*pixel * kiirando elemszam + 1 ures hely*/
    background->w = 200; /* leghosszabb menu elem is beleferjen*/
    background->x = screen->w /2 - background->w /2;
    background->y = screen->h /2 - background->h /2;
    SDL_FillRect(screen, background, 0xE2E2E2);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 -60, "Welcome to Vector race!", 0, 0, 0, 255);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 -20, "Enter: start game", 0, 0, 0, 255);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 +00, "1-4: number of players", 0, 0, 0, 255);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 +20, "left/right: select map", 0, 0, 0, 255);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 +40, "up/down: grid density", 0, 0, 0, 255);
    stringRGBA(screen, screen->w/2 - background->w/2 +5, screen->h/2 +60, "Esc: quit", 0, 0, 0, 255);
    rectangleRGBA(screen,screen->w/2 - background->w/2,screen->h/2 - background->h/2,screen->w/2 + background->w/2, screen->h/2 + background->h/2, 0, 0, 0, 255);
    free(background);
}

void Draw_end_menu (jatek_t *game) {
    SDL_Rect *background;
    char temp2[60];
    char *temp;
    int tempint;
    background = (SDL_Rect*) malloc(sizeof(SDL_Rect));
    if (background == NULL) { exit(9); }
    background->h = 150;
    background->w = 200;
    background->x = game->surface->w /2 - background->w /2;
    background->y = game->surface->h /2 - background->h /2;
    SDL_FillRect(game->surface, background, 0xE2E2E2);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 -60, "The game is over!", 0, 0, 0, 255);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 +40, "Enter: main menu", 0, 0, 0, 255);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 +60, "Esc: quit", 0, 0, 0, 255);
    tempint = count_pozlist(game,0);
    temp = (char*)malloc(sizeof(char)*51);
    if (temp == NULL) { exit(9); }
    temp = game->jatekosok[0].nev;
    if (game->jatekosok[0].allapot == 0) sprintf(temp2, "%s did not play", temp);
    if (game->jatekosok[0].allapot == 2) sprintf(temp2, "%s died in %d moves", temp, tempint);
    if (game->jatekosok[0].allapot == 3) sprintf(temp2, "%s won in %d moves", temp, tempint);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 -40, temp2, game->jatekosok[0].player_red, game->jatekosok[0].player_green, game->jatekosok[0].player_blue, 255);
    temp = game->jatekosok[1].nev;
    tempint = count_pozlist(game,1);
    if (game->jatekosok[1].allapot == 0) sprintf(temp2, "%s did not play", temp);
    if (game->jatekosok[1].allapot == 2) sprintf(temp2, "%s died in %d moves", temp, tempint);
    if (game->jatekosok[1].allapot == 3) sprintf(temp2, "%s won in %d moves", temp, tempint);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 -20, temp2, game->jatekosok[1].player_red, game->jatekosok[1].player_green, game->jatekosok[1].player_blue, 255);
    temp = game->jatekosok[2].nev;
    tempint = count_pozlist(game,2);
    if (game->jatekosok[2].allapot == 0) sprintf(temp2, "%s did not play", temp);
    if (game->jatekosok[2].allapot == 2) sprintf(temp2, "%s died in %d moves", temp, tempint);
    if (game->jatekosok[2].allapot == 3) sprintf(temp2, "%s won in %d moves", temp, tempint);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 +0, temp2, game->jatekosok[2].player_red, game->jatekosok[2].player_green, game->jatekosok[2].player_blue, 255);
    temp = game->jatekosok[3].nev;
    tempint = count_pozlist(game,3);
    if (game->jatekosok[3].allapot == 0) sprintf(temp2, "%s did not play", temp);
    if (game->jatekosok[3].allapot == 2) sprintf(temp2, "%s died in %d moves", temp, tempint);
    if (game->jatekosok[3].allapot == 3) sprintf(temp2, "%s won in %d moves", temp, tempint);
    stringRGBA(game->surface, game->surface->w/2 - background->w/2 +5, game->surface->h/2 +20, temp2, game->jatekosok[3].player_red, game->jatekosok[3].player_green, game->jatekosok[3].player_blue, 255);

    free(temp);
    rectangleRGBA(game->surface,game->surface->w/2 - background->w/2,game->surface->h/2 - background->h/2,game->surface->w/2 + background->w/2, game->surface->h/2 + background->h/2, 0, 0, 0, 255);
    free(background);
}

void Draw_info_pane (SDL_Surface *screen, char *line1, char *line2) { /*writes two lines to right-left info pane*/
    SDL_Rect *background;
    background = (SDL_Rect*) malloc(sizeof(SDL_Rect));
    if (background == NULL) { exit(9); }
    background->h = 45;
    background->w = 100;
    background->x = screen->w - background->w;
    background->y = screen->h - background->h;
    SDL_FillRect(screen, background, 0xE2E2E2);
    rectangleRGBA(screen,screen->w-100, screen->h-45,screen->w, screen->h, 0, 0, 0, 255);
    stringRGBA(screen, screen->w -90, screen->h -40, line1, 0, 0, 0, 255);
    stringRGBA(screen, screen->w -90, screen->h -20, line2, 0, 0, 0, 255);
    free(background);
}

void Draw_checkered_paper_effect (SDL_Surface *screen, int distance) {
    int i;
        for (i = 0; i<= screen->w; i+=distance) {
            lineRGBA(screen, i, 0, i, screen->h, 40, 40, 250, 35);
        }
        for (i = 0; i<= screen->h; i+=distance) {
            lineRGBA(screen, 0, i, screen->w, i, 40, 40, 250, 35);
        }
}

void Draw_valid_moves (jatek_t *game) {
    if (game->validmoves->C_valid != 0) filledCircleRGBA(game->surface,game->validmoves->C.x * racsmeret,game->validmoves->C.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->N_valid != 0) filledCircleRGBA(game->surface,game->validmoves->N.x * racsmeret,game->validmoves->N.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->W_valid != 0) filledCircleRGBA(game->surface,game->validmoves->W.x * racsmeret,game->validmoves->W.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->E_valid != 0) filledCircleRGBA(game->surface,game->validmoves->E.x * racsmeret,game->validmoves->E.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->S_valid != 0) filledCircleRGBA(game->surface,game->validmoves->S.x * racsmeret,game->validmoves->S.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->NE_valid != 0) filledCircleRGBA(game->surface,game->validmoves->NE.x * racsmeret,game->validmoves->NE.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->NW_valid != 0) filledCircleRGBA(game->surface,game->validmoves->NW.x * racsmeret,game->validmoves->NW.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->SE_valid != 0) filledCircleRGBA(game->surface,game->validmoves->SE.x * racsmeret,game->validmoves->SE.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
    if (game->validmoves->SW_valid != 0) filledCircleRGBA(game->surface,game->validmoves->SW.x * racsmeret,game->validmoves->SW.y * racsmeret,racsmeret/4,game->jatekosok[game->kovetkezik-1].player_red,game->jatekosok[game->kovetkezik-1].player_green,game->jatekosok[game->kovetkezik-1].player_blue,255);
}

void Draw_move (koord_t *from, koord_t *to, jatek_t *game, int playernumber) { /*ezek meg jatekkoordinatak at kell forditani screen koordinataba! */
    lineRGBA(game->surface, from->x * racsmeret, from->y * racsmeret, to->x * racsmeret, to->y * racsmeret, game->jatekosok[playernumber].player_red, game->jatekosok[playernumber].player_green, game->jatekosok[playernumber].player_blue,255);
}

void Draw_player_pos (koord_t *koord, jatek_t *game, int playernumber) {
    filledCircleRGBA(game->surface,koord->x * racsmeret, koord->y * racsmeret, racsmeret/5, game->jatekosok[playernumber].player_red, game->jatekosok[playernumber].player_green, game->jatekosok[playernumber].player_blue, 255);
}

void Draw_all_players_moves (jatek_t *game) {
    int jatekosszam;
    pozlista_t *iter,*prev;
    for (jatekosszam = 0; jatekosszam<4; jatekosszam++){ /*kulso ciklus jatekosonkent megyunk vegig*/
        prev = &(game->jatekosok[jatekosszam].poziciok);
        iter = &(game->jatekosok[jatekosszam].poziciok); /*mindket mutatot a jatekosban levo pozlistara allitjuk, az biztos letezik*/
            while (iter->next != NULL) {
                iter = iter->next;
                Draw_move(&(iter->koord), &(prev->koord), game, jatekosszam);
                Draw_player_pos(&(iter->koord), game, jatekosszam);
                prev = iter;

            }
    }
}

void Draw_refresh_gamescreen (jatek_t *game) {
    clrscr(game->surface);
    Draw_on_surface (game->surface, game->palya->rajzolando_palyakep);
    Draw_checkered_paper_effect(game->surface,racsmeret);
    Draw_info_pane(game->surface,game->jatekosok[game->kovetkezik-1].nev,"");
    Draw_all_players_moves(game);
    Draw_valid_moves(game);
    if (game->allapot == 2) Draw_end_menu(game);
    SDL_Flip(game->surface);
}

