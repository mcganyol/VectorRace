/*DA14D8 Prog1 NHF*/
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

/* ----------------------------------------------------------------- */

int main(int argc, char *argv[]) {

    SDL_Event event;
    SDL_Surface *screen;
    palya_t palya;
    int quit;
    char temp[15];
    CurrentValidMoves validmoves;
    palyalista_t *palyalista = NULL;
    jatek_t game;

    game.allapot = 0;
    game.palya = &(palya);
    game.validmoves = &(validmoves);
    game.jatekosok[0].nev = "Player 1";
    game.jatekosok[1].nev = "Player 2";
    game.jatekosok[2].nev = "Player 3";
    game.jatekosok[3].nev = "Player 4";
    game.jatekosok[0].poziciok.prev=NULL;
    game.jatekosok[0].poziciok.next=NULL;
    game.jatekosok[1].poziciok.prev=NULL;
    game.jatekosok[1].poziciok.next=NULL;
    game.jatekosok[2].poziciok.prev=NULL;
    game.jatekosok[2].poziciok.next=NULL;
    game.jatekosok[3].poziciok.prev=NULL;
    game.jatekosok[3].poziciok.next=NULL;
    game.jatekosok[0].player_red = 0;
    game.jatekosok[1].player_red = 0;
    game.jatekosok[2].player_red = 255;
    game.jatekosok[3].player_red = 100;
    game.jatekosok[0].player_green = 180;
    game.jatekosok[1].player_green = 0;
    game.jatekosok[2].player_green = 0;
    game.jatekosok[3].player_green = 100;
    game.jatekosok[0].player_blue = 0;
    game.jatekosok[1].player_blue = 255;
    game.jatekosok[2].player_blue = 0;
    game.jatekosok[3].player_blue = 100;

    build_maplist(&palyalista);

    #ifdef __WIN32__
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif /*for debug purposes*/

    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode(resx, resy, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Vector race", "Vector race");
    game.surface = screen;
    init_map(palyalista->name,&palya);
    game.jatekosok[0].allapot = 1;
    game.jatekosok[1].allapot = 0;
    game.jatekosok[2].allapot = 0;
    game.jatekosok[3].allapot = 0;

    clrscr(screen);
    Draw_on_surface (screen, palya.palyakep);
    Draw_checkered_paper_effect(screen,racsmeret);
    Draw_main_menu(screen);
    sprintf(temp, "%d player",remaining_player_number(&game));
    Draw_info_pane(screen, temp,palyalista->name);
    SDL_Flip(screen);

    quit = 0;
    while (!quit) {
        SDL_WaitEvent(&event);

            switch (game.allapot) {
            case 0: /*we are in the main menu*/
                switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            quit = 1;
                        }
                        if (event.key.keysym.sym == SDLK_1) {
                            game.jatekosok[0].allapot = 1;
                            game.jatekosok[1].allapot = 0;
                            game.jatekosok[2].allapot = 0;
                            game.jatekosok[3].allapot = 0;
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_2) {
                            game.jatekosok[0].allapot = 1;
                            game.jatekosok[1].allapot = 1;
                            game.jatekosok[2].allapot = 0;
                            game.jatekosok[3].allapot = 0;
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_3) {
                            game.jatekosok[0].allapot = 1;
                            game.jatekosok[1].allapot = 1;
                            game.jatekosok[2].allapot = 1;
                            game.jatekosok[3].allapot = 0;
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_4) {
                            game.jatekosok[0].allapot = 1;
                            game.jatekosok[1].allapot = 1;
                            game.jatekosok[2].allapot = 1;
                            game.jatekosok[3].allapot = 1;
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_RIGHT) {
                            palyalista = palyalista->next;
                            init_map(palyalista->name,&palya);
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_LEFT) {
                            palyalista = palyalista->prev;
                            init_map(palyalista->name,&palya);
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }

                        if (event.key.keysym.sym == SDLK_DOWN) {
                            if (racsmeret>5) {  /* esszeru hatarokon belul */
                            racsmeret --;
                            init_map(palyalista->name,&palya); /* a valtozott racsmeret miatt a startpoziciok valtoznak ujra kell inicializalni a mapot :( */
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                            }
                        }

                        if (event.key.keysym.sym == SDLK_UP) {
                            if (racsmeret<20) { /* esszeru hatarokon belul */
                            racsmeret ++;
                            init_map(palyalista->name,&palya); /* a valtozott racsmeret miatt a startpoziciok valtoznak ujra kell inicializalni a mapot :( */
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                            }
                        }

                        if (event.key.keysym.sym == SDLK_RETURN) {
                            game.allapot = 1;
                            game.kovetkezik = 1; /*TODO lehetne random hogy ki kezd, meg a sorrendjuk, de egyenlore 1-tol novelgetjuk*/
                            game.jatekosok[0].poziciok.koord = palya.p1start;
                            game.jatekosok[1].poziciok.koord = palya.p2start;
                            game.jatekosok[2].poziciok.koord = palya.p3start;
                            game.jatekosok[3].poziciok.koord = palya.p4start; /* set starting position for everyone */
                            add_koord_to_player(&(game.jatekosok[0]),&(palya.p1start));
                            add_koord_to_player(&(game.jatekosok[1]),&(palya.p2start));
                            add_koord_to_player(&(game.jatekosok[2]),&(palya.p3start));
                            add_koord_to_player(&(game.jatekosok[3]),&(palya.p4start)); /* set first move to start position too, to make it easier to determine the first move vector! */
                            set_valid_moves(&game);
                            Draw_refresh_gamescreen(&game);

                        }
                    break;

                    case SDL_QUIT:
                        quit = 1;
                    break;
                }
            break;
            case 1: /* the game is running*/
                switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            game.allapot = 2;
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            Draw_info_pane(screen,game.jatekosok[game.kovetkezik-1].nev,palyalista->name);
                            SDL_Flip(screen);
                        }
                        if (event.key.keysym.sym == SDLK_KP1) {
                            if (validmoves.SW_valid != 0) {
                                lep(&game,&(validmoves.SW));
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP2) {
                            if (validmoves.S_valid != 0) {
                                lep(&game,&validmoves.S);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP3) {
                            if (validmoves.SE_valid != 0) {
                                lep(&game,&validmoves.SE);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP4) {
                            if (validmoves.W_valid != 0) {
                                lep(&game,&validmoves.W);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP5) {
                            if (validmoves.C_valid != 0) {
                                lep(&game,&validmoves.C);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP6) {
                            if (validmoves.E_valid != 0) {
                                lep(&game,&validmoves.E);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP7) {
                            if (validmoves.NW_valid != 0) {
                                lep(&game,&validmoves.NW);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP8) {
                            if (validmoves.N_valid != 0) {
                                lep(&game,&validmoves.N);
                                Draw_refresh_gamescreen(&game);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_KP9) {
                            if (validmoves.NE_valid != 0) {
                                lep(&game,&validmoves.NE);
                                Draw_refresh_gamescreen(&game);
                            }
                        }

                }
            break;


            case 2: /* the game here is over */
                switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            quit = 1;
                        }

                        if (event.key.keysym.sym == SDLK_RETURN) {
                            game.allapot = 0;
                            game.jatekosok[0].allapot = 1;
                            game.jatekosok[1].allapot = 0;
                            game.jatekosok[2].allapot = 0;
                            game.jatekosok[3].allapot = 0;
                            reset_koords_of_player(&(game.jatekosok[0]));
                            reset_koords_of_player(&(game.jatekosok[1]));
                            reset_koords_of_player(&(game.jatekosok[2]));
                            reset_koords_of_player(&(game.jatekosok[3]));
                            /*end results*/
                            clrscr(screen);
                            Draw_on_surface (screen, palya.palyakep);
                            Draw_checkered_paper_effect(screen,racsmeret);
                            Draw_main_menu(screen);
                            sprintf(temp, "%d player",remaining_player_number(&game));
                            Draw_info_pane(screen, temp,palyalista->name);
                            SDL_Flip(screen);
                        }
                    break;
                }
            break;

            }

    }

    SDL_Quit();

    return 0;
}
